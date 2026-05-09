#include "input.h"
#include "power.h"
#include "systick.h"
#include "mute.h"
#include "mcc_generated_files\system\pins.h"

InputState inputOne = {&inputOneOnKnob, &inputOneOffKnob, 0, 0, IsInputOneOn, ToggleInputOnePower};
InputState inputTwo = {&inputTwoOnKnob, &inputTwoOffKnob, 0, 0, IsInputTwoOn, ToggleInputTwoPower};
InputState inputThree = {&inputThreeOnKnob, &inputThreeOffKnob, 0, 0, IsInputThreeOn, ToggleInputThreePower};
InputState inputBt = {&inputBtOnKnob, &inputBtOffKnob, 0, 0, IsInputBtOn, ToggleInputBtPower};
InputState *inputs[] = {
    [INPUT_ONE] = &inputOne, 
    [INPUT_TWO] = &inputTwo, 
    [INPUT_THREE] = &inputThree, 
    [INPUT_BT] = &inputBt
};
InputType currentInputType = INPUT_ONE;
bool isAnyInputInPowerDelay = false;

LEDType MapInputTypeToLedType(InputType button)
{
    switch(button)
    {
        case INPUT_ONE:
            return LED_INPUT_ONE;
        case INPUT_TWO:
            return LED_INPUT_TWO;
        case INPUT_THREE:
            return LED_INPUT_THREE;
        case INPUT_BT:
            return LED_INPUT_BT;
    }
        
}
void InputSet(InputType inputType)
{
    Mute_Engage(); // Always mute to prevent pops
    currentInputType = inputType;
    switch(inputType) {
        case INPUT_ONE:  IO_ISA_PORT = 0; IO_ISB_PORT = 0;  break;
        case INPUT_TWO:  IO_ISA_PORT = 1; IO_ISB_PORT = 0;  break;
        case INPUT_THREE:  IO_ISA_PORT = 0; IO_ISB_PORT = 1;  break;
        case INPUT_BT:  IO_ISA_PORT = 1; IO_ISB_PORT = 1;  break;
        default: return;
    }
    // Update the LED for the selected input
    Display_SetInputLED(MapInputTypeToLedType(currentInputType));
}

void IntializeInput(InputType inputType)
{
    InputSet(inputType);
    // turn on the input immediately
    inputs[currentInputType]->TogglePower();
}

void HandleInputSwitchPower()
{
    if (!isAnyInputInPowerDelay)
    { 
        return;
    }
    isAnyInputInPowerDelay = false;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (inputs[i]->powerOffDelay->value != 0 && inputs[currentInputType] != inputs[i] && inputs[i]->IsOn())
        {
            uint32_t requiredDelay = ((uint32_t)inputs[i]->powerOffDelay->value * 99000) / 254;
    
            if ((systemTicks - inputs[i]->powerOffStartTime) >= requiredDelay) {
                inputs[i]->TogglePower();
            }
            else
            {
                isAnyInputInPowerDelay = true;
            }
        }
        if (inputs[currentInputType] == inputs[i])
        {
            if(!inputs[i]->IsOn())
            {
                isAnyInputInPowerDelay = true;
                uint32_t requiredDelay = ((uint32_t)inputs[i]->powerOnDelay->value * 30000) / 254;
                    
                if ((systemTicks - inputs[i]->powerOnStartTime) >= requiredDelay) {
                    inputs[i]->TogglePower();
                    Mute_ScheduleRelease();
                }
                else
                {
                    isAnyInputInPowerDelay = true;
                }
            } 
            else
            {
                Mute_ScheduleRelease();
            }
 
        }
    }
}

void InputSwitch(InputType inputType) {   
    InputSet(inputType);
    // --- BUTTON PRESS LOGIC ---
    isAnyInputInPowerDelay = true;
    
    for(uint8_t i = 0; i < 4; i++) {
        inputs[i]->powerOffStartTime = systemTicks;
        inputs[i]->powerOnStartTime = systemTicks;
    }

}

InputType GetInputType(void)
{
    return currentInputType;
}