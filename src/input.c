#include "input.h"
#include "ui_manager.h"
#include "buttons.h"
#include "display.h"
#include "mute.h"
#include "digipot.h"
#include "power.h"
#include "systick.h"
#include <stddef.h>

// --- State Variables ---
InputState inputOne = {&inputOneOnKnob, &inputOneOffKnob, 0, 0, IsInputOneOn, ToggleInputOnePower};
InputState inputTwo = {&inputTwoOnKnob, &inputTwoOffKnob, 0, 0, IsInputTwoOn, ToggleInputTwoPower};
InputState inputThree = {&inputThreeOnKnob, &inputThreeOffKnob, 0, 0, IsInputThreeOn, ToggleInputThreePower};
InputState inputBt = {&inputBtOnKnob, &inputBtOffKnob, 0, 0, IsInputBtOn, ToggleInputBtPower};

InputState *inputs[] = { [INPUT_ONE] = &inputOne, [INPUT_TWO] = &inputTwo, [INPUT_THREE] = &inputThree, [INPUT_BT] = &inputBt };

InputType currentInputType = INPUT_ONE;
bool isAnyInputInPowerDelay = false;

// --- UI Layouts ---
static const UI_Layout inputLayouts[] = {
    [INPUT_ONE]   = { .params = {&inputOneOnKnob, &inputOneOffKnob, NULL, NULL, NULL, NULL}, .blinkLed = LED_INPUT_ONE },
    [INPUT_TWO]   = { .params = {&inputTwoOnKnob, &inputTwoOffKnob, NULL, NULL, NULL, NULL}, .blinkLed = LED_INPUT_TWO },
    [INPUT_THREE] = { .params = {&inputThreeOnKnob, &inputThreeOffKnob, NULL, NULL, NULL, NULL}, .blinkLed = LED_INPUT_THREE },
    [INPUT_BT]    = { .params = {&inputBtOnKnob, &inputBtOffKnob, NULL, NULL, NULL, NULL}, .blinkLed = LED_INPUT_BT }
};

// --- Helpers ---
static InputType ButtonToInput(ButtonType btn) {
    switch(btn) {
        case BUTTON_INPUT_ONE:   return INPUT_ONE;
        case BUTTON_INPUT_TWO:   return INPUT_TWO;
        case BUTTON_INPUT_THREE: return INPUT_THREE;
        case BUTTON_INPUT_BT:    return INPUT_BT;
        default: return INPUT_ONE;
    }
}

LEDType MapInputTypeToLedType(InputType input) {
    const LEDType leds[] = { LED_INPUT_ONE, LED_INPUT_TWO, LED_INPUT_THREE, LED_INPUT_BT };
    return leds[input];
}

// --- Subscription Handler ---
void Input_ButtonHandler(ButtonType button, ButtonEvent event) {
    InputType type = ButtonToInput(button);

    if (event == BUTTON_EVENT_SHORT_PRESS) {
        InputSwitch(type);
    } 
    else if (event == BUTTON_EVENT_LONG_PRESS) {
        if (Button_GetExclusive() == button) {
            // EXIT SUB-MODE
            Button_ClearExclusive();
            UI_Manager_Reset();
            Display_SetInputLED(MapInputTypeToLedType(currentInputType));
        } else {
            // ENTER SUB-MODE
            Button_SetExclusive(button);
            UI_Manager_ApplyLayout((UI_Layout*)&inputLayouts[type]);
        }
    }
}

void Input_Init(void) {
    Button_Subscribe(BUTTON_INPUT_ONE, Input_ButtonHandler);
    Button_Subscribe(BUTTON_INPUT_TWO, Input_ButtonHandler);
    Button_Subscribe(BUTTON_INPUT_THREE, Input_ButtonHandler);
    Button_Subscribe(BUTTON_INPUT_BT, Input_ButtonHandler);
}

// --- Original Logic (Preserved) ---
void InputSet(InputType inputType) {
    Mute_Engage(); 
    currentInputType = inputType;
    switch(inputType) {
        case INPUT_ONE:   SetInputState(0, 0); break;
        case INPUT_TWO:   SetInputState(0, 1); break;
        case INPUT_THREE: SetInputState(1, 0); break;
        case INPUT_BT:    SetInputState(1, 1); break;
        default: return;
    }
    Display_SetInputLED(MapInputTypeToLedType(currentInputType));
}

void Input_LoadSettings(InputType inputType) {
    InputSet(inputType);
    inputs[currentInputType]->TogglePower();
}

void InputSwitch(InputType inputType) {   
    InputSet(inputType);
    isAnyInputInPowerDelay = true;
    for(uint8_t i = 0; i < 4; i++) {
        inputs[i]->powerOffStartTime = systemTicks;
        inputs[i]->powerOnStartTime = systemTicks;
    }
}

void HandleInputSwitchPower() {
    if (!isAnyInputInPowerDelay) return;
    
    isAnyInputInPowerDelay = false;
    for (uint8_t i = 0; i < 4; i++) {
        if (inputs[i]->powerOffDelay->value != 254 && inputs[currentInputType] != inputs[i] && inputs[i]->IsOn()) {
             uint32_t requiredDelay = ((uint32_t)inputs[i]->powerOffDelay->value * 99000) / 254;
             if ((systemTicks - inputs[i]->powerOffStartTime) >= requiredDelay) {
                 inputs[i]->TogglePower();
             } else {
                 isAnyInputInPowerDelay = true;
             }
        }
        if (inputs[currentInputType] == inputs[i]) {
            if(!inputs[i]->IsOn()) {
                isAnyInputInPowerDelay = true;
                uint32_t requiredDelay = ((uint32_t)inputs[i]->powerOnDelay->value * 30000) / 254;
                if ((systemTicks - inputs[i]->powerOnStartTime) >= requiredDelay) {
                    inputs[i]->TogglePower();
                    Mute_ScheduleRelease();
                } else {
                    isAnyInputInPowerDelay = true;
                }
            } else {
                Mute_ScheduleRelease();
            }
        }
    }
}

InputType GetInputType(void) { return currentInputType; }