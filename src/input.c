#include "input.h"
#include "ui_manager.h"
#include "buttons.h"
#include "display.h"
#include "mute.h"
#include "audio_control.h"
#include "power.h"
#include "storage.h"
#include "tone.h"
#include "systick.h"
#include "digipot.h"
#include <stddef.h>

// --- State Variables ---
InputState inputOne = {&inputOneOnKnob, &inputOneOffKnob, 0, 0, IsInputOneOn, ToggleInputOnePower};
InputState inputTwo = {&inputTwoOnKnob, &inputTwoOffKnob, 0, 0, IsInputTwoOn, ToggleInputTwoPower};
InputState inputThree = {&inputThreeOnKnob, &inputThreeOffKnob, 0, 0, IsInputThreeOn, ToggleInputThreePower};
InputState inputBt = {&inputBtOnKnob, &inputBtOffKnob, 0, 0, IsInputBtOn, ToggleInputBtPower};

InputState *inputs[] = { [INPUT_ONE] = &inputOne, [INPUT_TWO] = &inputTwo, [INPUT_THREE] = &inputThree, [INPUT_BT] = &inputBt };

InputType currentInputType = INPUT_NONE;
bool isAnyInputInPowerDelay = false;

// --- UI Layouts ---
static const UI_Layout inputLayouts[] = {
    [INPUT_ONE]   = { .params = {&inputOneOnKnob, &inputOneOffKnob, NULL, NULL, NULL, &inputOneGainKnob}, .blinkLed = LED_INPUT_ONE },
    [INPUT_TWO]   = { .params = {&inputTwoOnKnob, &inputTwoOffKnob, NULL, NULL, NULL, &inputTwoGainKnob}, .blinkLed = LED_INPUT_TWO },
    [INPUT_THREE] = { .params = {&inputThreeOnKnob, &inputThreeOffKnob, NULL, NULL, NULL, &inputThreeGainKnob}, .blinkLed = LED_INPUT_THREE },
    [INPUT_BT]    = { .params = {&inputBtOnKnob, &inputBtOffKnob, NULL, NULL, NULL, &inputBtGainKnob}, .blinkLed = LED_INPUT_BT }
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

static void ShowInputSubSettings(ButtonType button)
{
    if (Button_GetExclusive() == BUTTON_NONE)
        Display_SubSettingsEnter();
    Button_SetExclusive(button);
    UI_Manager_ApplyLayout(&inputLayouts[ButtonToInput(button)]);
    Display_SubSettingsRefreshLEDs();
}

static void ExitSubSettings(void)
{
    Button_ClearExclusive();
    UI_Manager_Reset();
    Display_SubSettingsExit();
}

LEDType MapInputTypeToLedType(InputType input) {
    const LEDType leds[] = { LED_INPUT_ONE, LED_INPUT_TWO, LED_INPUT_THREE, LED_INPUT_BT };
    return leds[input];
}

// --- Subscription Handler ---
void Input_ButtonHandler(ButtonType button, ButtonEvent event) {
    InputType type = ButtonToInput(button);

    if (event == BUTTON_EVENT_SHORT_PRESS) {
        if (Button_GetExclusive() != BUTTON_NONE) {
            if (Button_GetExclusive() == button)
                ExitSubSettings();
            else
                ShowInputSubSettings(button);
            return;
        }
        InputSwitch(type);
        Display_SetInputLED(MapInputTypeToLedType(currentInputType));
        Display_SetToneLED(isToneOn);
    } 
    else if (event == BUTTON_EVENT_LONG_PRESS) {
        if (Button_GetExclusive() == button) {
            ExitSubSettings();
        } else {
            ShowInputSubSettings(button);
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
    if (currentInputType == inputType)
        return;
    Mute_Engage(); 
    currentInputType = inputType;
    Storage_MarkDirty();
    switch(inputType) {
        case INPUT_ONE:   
            SetInputState(0, 0); 
            UpdateInputGainWipers();
            break;
        case INPUT_TWO:   
            SetInputState(0, 1); 
            UpdateInputGainWipers();
            break;
        case INPUT_THREE: 
            SetInputState(1, 0);
            UpdateInputGainWipers();
            break;
        case INPUT_BT:    
            SetInputState(1, 1);
            UpdateInputGainWipers();
            break;
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
        inputs[i]->powerOffStartTime = SysTick_Now();
        inputs[i]->powerOnStartTime = SysTick_Now();
    }
}

void HandleInputSwitchPower() {
    if (!isAnyInputInPowerDelay) return;
    
    isAnyInputInPowerDelay = false;
    for (uint8_t i = 0; i < 4; i++) {
        if (inputs[i]->powerOffDelay->value != 254 && inputs[currentInputType] != inputs[i] && inputs[i]->IsOn()) {
             uint32_t requiredDelay = ((uint32_t)inputs[i]->powerOffDelay->value * 99000) / 254;
             if ((SysTick_Now() - inputs[i]->powerOffStartTime) >= requiredDelay) {
                 inputs[i]->TogglePower();
             } else {
                 isAnyInputInPowerDelay = true;
             }
        }
        if (inputs[currentInputType] == inputs[i]) {
            if(!inputs[i]->IsOn()) {
                isAnyInputInPowerDelay = true;
                uint32_t requiredDelay = ((uint32_t)inputs[i]->powerOnDelay->value * 30000) / 254;
                if ((SysTick_Now() - inputs[i]->powerOnStartTime) >= requiredDelay) {
                    inputs[i]->TogglePower();
                    Mute_ScheduleRelease();
                }
            }
        }
    }
}

InputType GetInputType(void) { return currentInputType; }