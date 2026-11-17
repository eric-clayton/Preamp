#include "tone.h"
#include "display.h"
#include "buttons.h"
#include "storage.h"
#include "ui_manager.h"
#include "audio_control.h"
#include "input.h"
#include "mcc_generated_files\system\pins.h"

uint8_t isToneOn = 0;

// The Tone module simply defines what it needs, it doesn't "command" the mode
const UI_Layout toneSubModeLayout = {
    .params = { &subLevelKnob, &subEqKnob, &subPhaseKnob, NULL, NULL, &subOuputKnob },
    .blinkLed = LED_TONE
};

static void ShowToneSubSettings(void)
{
    if (Button_GetExclusive() == BUTTON_NONE)
        Display_SubSettingsEnter();
    Button_SetExclusive(BUTTON_TONE);
    UI_Manager_ApplyLayout(&toneSubModeLayout);
    Display_SubSettingsRefreshLEDs();
}

static void ExitSubSettings(void)
{
    Button_ClearExclusive();
    UI_Manager_Reset();
    Display_SubSettingsExit();
}

void Tone_ButtonHandler(ButtonType button, ButtonEvent event) {
    if (event == BUTTON_EVENT_LONG_PRESS) {
        if (Button_GetExclusive() == BUTTON_TONE) {
            ExitSubSettings();
        } else {
            ShowToneSubSettings();
        }
    }
    if (event == BUTTON_EVENT_SHORT_PRESS) {
        if (Button_GetExclusive() != BUTTON_NONE) {
            if (Button_GetExclusive() == BUTTON_TONE)
                ExitSubSettings();
            else
                ShowToneSubSettings();
        } else {
            ToggleTone();
            Storage_MarkDirty();
        }
    }
}

void Tone_Init(void) {
    Button_Subscribe(BUTTON_TONE, Tone_ButtonHandler);
}

// Apply the "State" - Call this whenever data is retrieved from storage
void Tone_LoadSettings(uint8_t tone) {
    isToneOn = tone;
    AudioControl_SetTone(isToneOn);
    Display_SetToneLED(isToneOn);
}
uint8_t GetToneValue(void)
{
    return isToneOn; 
}
void ToggleTone(void)
{
    isToneOn = isToneOn ? 0 : 1;
    Storage_MarkDirty();
    AudioControl_SetTone(isToneOn);
    Display_SetToneLED(isToneOn);
}  