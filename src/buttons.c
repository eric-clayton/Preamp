#include "buttons.h"
#include "as1115.h"
#include "systick.h"
#include "input.h"
#include "mode.h"
#define LONG_PRESS_MS 1500  // Duration for a "Long Press"
#define BLINK_INTERVAL 250

uint8_t lightMap = 0x0;
ButtonType activeButton = NONE;
ButtonState_t longPressState = {false, false, false, 0, 0};
volatile bool buttonEventPending = false;

void HandleButtonPressed(){
    buttonEventPending = true;
}
uint8_t GetDisplayButtonBit(ButtonType button) {
    switch(button) {
        case TONE_BUTTON:        return 0x04;
        case INPUT_ONE_BUTTON:   return 0x40;
        case INPUT_TWO_BUTTON:   return 0x20;
        case INPUT_THREE_BUTTON: return 0x10;
        case INPUT_BT_BUTTON:    return 0x08;
        default:                 return 0x00;
    }
}
void ApplyButtonLightSwitch(ButtonType button) {
    uint8_t bit = GetDisplayButtonBit(button);
    switch(button) {
        case TONE_BUTTON:
            lightMap ^= bit; 
            break;
        case INPUT_ONE_BUTTON:
        case INPUT_TWO_BUTTON:
        case INPUT_THREE_BUTTON:
        case INPUT_BT_BUTTON:
            lightMap = (lightMap & ~0x78) | bit;
            break;
        default:
            return;
    }
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
    uint8_t physicalButton = NONE;
    if (pA & (1 << 6))      physicalButton = TONE_BUTTON;
    else if (pB & (1 << 6)) physicalButton = INPUT_ONE_BUTTON;
    else if (pA & (1 << 4)) physicalButton = INPUT_TWO_BUTTON;
    else if (pA & (1 << 5)) physicalButton = INPUT_THREE_BUTTON;
    else if (pB & (1 << 5)) physicalButton = INPUT_BT_BUTTON;

    // 2. Handle the "Physical" press/release events
    if (physicalButton != NONE) {
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
                if (activeButton == NONE) {
                    longPressState.isCurrentlyPressed = true;
                    longPressState.pressStartTime = systemTicks;
                    longPressState.longPressInitialized = false;

                    activeButton = physicalButton;
                    ApplyButtonLightSwitch(activeButton);
                    if (physicalButton == INPUT_ONE_BUTTON || physicalButton ==  INPUT_TWO_BUTTON || physicalButton ==  INPUT_THREE_BUTTON || physicalButton ==  INPUT_BT_BUTTON)
                        InputSwitch(physicalButton);
                }
            }
        }
    }
    else {
        // FINGER RELEASED
        longPressState.isCurrentlyPressed = false;
        
        // Only clear the UI owner if we aren't in sub-mode
        if (!longPressState.isSubMode) {
            activeButton = NONE;
        }
    }

    AS1115_Write(0x08, lightMap);
    buttonEventPending = false;
}
void HandleLongPress()
{
    if (longPressState.isCurrentlyPressed && !longPressState.longPressInitialized) {
        if ((systemTicks - longPressState.pressStartTime) >= LONG_PRESS_MS) {
            
            longPressState.isSubMode = !longPressState.isSubMode; 
            longPressState.longPressInitialized = true;        

            uint8_t activeBit = GetDisplayButtonBit(activeButton);

            if (!longPressState.isSubMode) {
                // --- EXITING SUB MODE ---
                lightMap |= activeBit; // Ensure the LED stays solid ON when exiting
                AS1115_Write(0x08, lightMap);
                
                InitializeNormalMode();
            }
            else {
                // --- ENTERING SUB MODE ---
                InitializeSubSettingModes(activeButton);
            }
        }
    }
}
void HandleLEDBlink()
{
    if (longPressState.isSubMode) {
        if (systemTicks - longPressState.lastBlinkTime >= BLINK_INTERVAL) {
            // Blink ONLY the LED of the button that owns this sub-menu
            lightMap ^= GetDisplayButtonBit(activeButton); 
            AS1115_Write(0x08, lightMap);
            longPressState.lastBlinkTime = systemTicks;
        }
    }
}