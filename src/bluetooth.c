#include "bluetooth.h"
#include "buttons.h"
#include "audio_control.h"
#include "display.h"
#include "input.h"
#include "systick.h"
#include "mcc_generated_files/system/pins.h"

#define BT_CONNECTED_CONFIRM_MS 10000u
#define BT_MAX_PATTERN_GAP_MS 10000u
#define BT_PAUSE_MIN_MS  1500u
#define BT_PLAY_HOLD_MS  4000u
#define BT_PLAY_CYCLES_REQUIRED 3u
#define BT_STATE_CONFIRM_MS 500u
#define BT_PATTERN_GRACE_MS 4000u

static BtLinkState btState = BT_DISCONNECTED;
static BtLinkState candidateState = BT_DISCONNECTED;
static uint32_t candidateSince;
static uint32_t patternSince;
static bool patternActive;
static bool lastBled;
static bool haveRise;
static bool playValid;
static bool shortGapSeen;
static uint8_t playCycles;
static uint32_t lastEdgeMs;
static uint32_t lastRiseMs;
static uint32_t playUntilMs;
static InputType lastInputType;

static void ApplyState(BtLinkState state)
{
    if (state == btState)
        return;

    btState = state;
    Display_SetBTStatusLED(state != BT_DISCONNECTED);
}

void ButtonHandler(ButtonType button, ButtonEvent event)
{
    bool pressed;
    if (event == BUTTON_EVENT_PRESSED)
        pressed = true;
    else if (event == BUTTON_EVENT_RELEASED)
        pressed = false;
    else
        return;

    bool commandActive = pressed && GetInputType() == INPUT_BT;

    switch (button) {
        case BUTTON_PREV:
            BluetoothPrev(commandActive);
            Display_ShowBluetoothCommand(DISPLAY_BT_PREV, commandActive);
            break;
        case BUTTON_PAUSE:
            BluetoothPause(commandActive);
            Display_ShowBluetoothCommand(DISPLAY_BT_PAUSE, commandActive);
            break;
        case BUTTON_NEXT:
            BluetoothNext(commandActive);
            Display_ShowBluetoothCommand(DISPLAY_BT_NEXT, commandActive);
            break;
        default:
            break;
    }
}

void Bluetooth_Init()
{
    Button_Subscribe(BUTTON_PREV, ButtonHandler);
    Button_Subscribe(BUTTON_PAUSE, ButtonHandler);
    Button_Subscribe(BUTTON_NEXT, ButtonHandler);

    BluetoothPrev(false);
    BluetoothPause(false);
    BluetoothNext(false);

    lastInputType = GetInputType();
    lastBled = BLED_GetValue() != 0;
    lastEdgeMs = SysTick_Now();
    lastRiseMs = lastEdgeMs;
    patternSince = lastEdgeMs;
    patternActive = false;
    candidateSince = lastEdgeMs;
    candidateState = BT_DISCONNECTED;
    haveRise = false;
    playValid = false;
    shortGapSeen = false;
    playCycles = 0;
    btState = BT_DISCONNECTED;
    Display_SetBTStatusLED(false);
}

void Bluetooth_Update(void)
{
    uint32_t now = SysTick_Now();
    bool bled = BLED_GetValue() != 0;
    InputType inputType = GetInputType();

    if (inputType != lastInputType) {
        if (inputType != INPUT_BT) {
            candidateState = BT_DISCONNECTED;
            candidateSince = now;
            patternActive = false;
            haveRise = false;
            playValid = false;
            shortGapSeen = false;
            playCycles = 0;
            ApplyState(BT_DISCONNECTED);
        } else {
            lastBled = bled;
            lastEdgeMs = now;
            lastRiseMs = now;
            patternSince = now;
            candidateSince = now;
            candidateState = BT_DISCONNECTED;
            patternActive = false;
            haveRise = false;
            playValid = false;
            shortGapSeen = false;
            playCycles = 0;
            ApplyState(BT_DISCONNECTED);
        }
    }
    lastInputType = inputType;
    if (inputType != INPUT_BT)
        return;

    if (bled != lastBled) {
        lastBled = bled;
        lastEdgeMs = now;
        if (!patternActive) {
            patternActive = true;
            patternSince = now;
        }

        if (bled) {
            uint32_t gap = now - lastRiseMs;
            if (haveRise) {
                if (gap > BT_PAUSE_MIN_MS && gap < BT_MAX_PATTERN_GAP_MS) {
                    if (shortGapSeen) {
                        if (playCycles < BT_PLAY_CYCLES_REQUIRED)
                            playCycles++;
                        if (playCycles >= BT_PLAY_CYCLES_REQUIRED) {
                            playValid = true;
                            playUntilMs = now + BT_PLAY_HOLD_MS;
                        }
                    } else {
                        playCycles = 0;
                    }
                    shortGapSeen = false;
                } else if (gap <= BT_PAUSE_MIN_MS) {
                    shortGapSeen = true;
                } else {
                    shortGapSeen = false;
                    playCycles = 0;
                    playValid = false;
                }
            }
            lastRiseMs = now;
            haveRise = true;
        }
    }

    bool steadyHigh = bled && (now - lastEdgeMs) >= BT_CONNECTED_CONFIRM_MS;

    if (steadyHigh) {
        patternActive = false;
        playValid = false;
        shortGapSeen = false;
        playCycles = 0;
    } else if (playValid && (int32_t)(now - playUntilMs) >= 0) {
        playValid = false;
        shortGapSeen = false;
        playCycles = 0;
    }

    BtLinkState observedState;
    if (playValid)
        observedState = BT_PLAYING;
    else if (steadyHigh)
        observedState = BT_CONNECTED;
    else if (patternActive && btState != BT_DISCONNECTED &&
             (now - patternSince) < BT_PATTERN_GRACE_MS)
        observedState = btState;
    else
        observedState = BT_DISCONNECTED;

    if (observedState != candidateState) {
        candidateState = observedState;
        candidateSince = now;
    }

    if (candidateState != btState &&
        (now - candidateSince) >= BT_STATE_CONFIRM_MS)
        ApplyState(candidateState);
}

BtLinkState Bluetooth_GetState(void)
{
    return btState;
}