#include "buttons.h"
#include "as1115.h"
#include "systick.h"
#include "input.h"
#include "tone.h"
#include "mode.h"
#include "storage.h"
#include "display.h"

#define LONG_PRESS_MS 1500  // Duration for a "Long Press"
#define BLINK_INTERVAL 250

ButtonType activeButton = BUTTON_NONE;
ButtonState_t longPressState = {false, false, false, 0, 0};
volatile bool buttonEventPending = false;

SystemMode MapButtonTypeToSystemMode(ButtonType button)
{
    switch(button)
    {
        case BUTTON_TONE:
            return MODE_SUB;
        case BUTTON_INPUT_ONE:
            return MODE_INPUT_ONE_POWER;
        case BUTTON_INPUT_TWO:
            return  MODE_INPUT_TWO_POWER;
        case BUTTON_INPUT_THREE:
            return  MODE_INPUT_THREE_POWER;
        case BUTTON_INPUT_BT:
            return MODE_INPUT_BT_POWER;
        case BUTTON_NONE:
            return MODE_FREQ_LOW;
    }
        
}
LEDType MapButtonTypeToLedType(ButtonType button)
{
    switch(button)
    {
        case BUTTON_TONE:
            return LED_TONE;
        case BUTTON_INPUT_ONE:
            return LED_INPUT_ONE;
        case BUTTON_INPUT_TWO:
            return LED_INPUT_TWO;
        case BUTTON_INPUT_THREE:
            return LED_INPUT_TWO;
        case BUTTON_INPUT_BT:
            return LED_INPUT_BT;
        case BUTTON_NONE:
            return LED_NONE;
    }
        
}
void HandleButtonPressed(){
    buttonEventPending = true;
}

void UpdateButton() {
    
    if (!buttonEventPending) {
        return;
    }
    uint8_t readData[2];
    AS1115_ReadKeys(readData); 
   
    uint8_t pA = ~readData[0];
    uint8_t pB = ~readData[1];

    // 1. Always see what is physically happening right now
    ButtonType physicalButton = BUTTON_NONE;
    if (pA & (1 << 6))      physicalButton = BUTTON_TONE;
    else if (pB & (1 << 6)) physicalButton = BUTTON_INPUT_ONE;
    else if (pA & (1 << 4)) physicalButton = BUTTON_INPUT_TWO;
    else if (pA & (1 << 5)) physicalButton = BUTTON_INPUT_THREE;
    else if (pB & (1 << 5)) physicalButton = BUTTON_INPUT_BT;

    // 2. Handle the "Physical" press/release events
    if (physicalButton != BUTTON_NONE) {
        // If this is a FRESH touch (finger just hit the button)
        if (!longPressState.isCurrentlyPressed) {
            
            if (longPressState.isSubMode) {
                // --- SUB MODE LOGIC ---
                // We only care if the finger matches the already active button
                // This allows the long-press timer to restart for exiting Sub Mode
                if (physicalButton == activeButton) {
                    longPressState.isCurrentlyPressed = true;
                    longPressState.pressStartTime = systemTicks;
                    longPressState.longPressInitialized = false;
                }
            }
            else {
                // --- NORMAL MODE LOGIC ---
                // Only allow a press to register if no other button is currently "Active"
                if (activeButton == BUTTON_NONE) {
                    longPressState.isCurrentlyPressed = true;
                    longPressState.pressStartTime = systemTicks;
                    longPressState.longPressInitialized = false;

                    activeButton = physicalButton;
                    if (physicalButton == BUTTON_TONE)
                    {
                        ToggleTone();
                    }
                    else
                        InputSwitch((uint8_t)physicalButton);
                    Storage_MarkDirty();
                }
            }
        }
    }
    else {
        // FINGER RELEASED
        longPressState.isCurrentlyPressed = false;
        
        // Only clear the UI owner if we aren't in sub-mode
        if (!longPressState.isSubMode) {
            activeButton = BUTTON_NONE;
        }
    }
    buttonEventPending = false;
}

void HandleLongPress()
{
    if (longPressState.isCurrentlyPressed && !longPressState.longPressInitialized) {
        if ((systemTicks - longPressState.pressStartTime) >= LONG_PRESS_MS) {
            
            longPressState.isSubMode = !longPressState.isSubMode; 
            longPressState.longPressInitialized = true;        

            if (!longPressState.isSubMode) {
                // --- Entering NORMAL MODE ---
                Display_SetBlinkBitIndex(LED_NONE);
                if (activeButton == BUTTON_TONE)
                {
                    Display_SetToneLED(GetToneValue());
                }
                else
                {
                    Display_SetInputLED(MapInputTypeToLedType(GetInputType()));
                }
                InitializeNormalMode();
            }
            else {
                // --- ENTERING SUB MODE ---
                Display_SetBlinkBitIndex(MapButtonTypeToLedType(activeButton));
                InitializeSubSettingModes(MapButtonTypeToSystemMode(activeButton));
            }
        }
    }
}

void HandleLEDBlink()
{
    if (longPressState.isSubMode) {
        if (systemTicks - longPressState.lastBlinkTime >= BLINK_INTERVAL) {
            // Blink ONLY the LED of the button that owns this sub-menu
            Display_BlinkLED();
            longPressState.lastBlinkTime = systemTicks;
        }
    }
}