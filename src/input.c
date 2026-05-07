#include "input.h"
#include "power.h"
#include "systick.h"
#include "mute.h"
#include "mcc_generated_files\system\pins.h"

InputState inputOne = {&inputOneOnKnob, &inputOneOffKnob, 0, 0, IsInputOneOn, ToggleInputOnePower};
InputState inputTwo = {&inputTwoOnKnob, &inputTwoOffKnob, 0, 0, IsInputTwoOn, ToggleInputTwoPower};
InputState inputThree = {&inputThreeOnKnob, &inputThreeOffKnob, 0, 0, IsInputThreeOn, ToggleInputThreePower};
InputState inputBt = {&inputBtOnKnob, &inputBtOffKnob, 0, 0, IsInputBtOn, ToggleInputBtPower};
InputState *inputs[] = {&inputOne, &inputTwo, &inputThree, &inputBt};
InputState *currentInput = &inputOne;
bool isAnyInputInPowerDelay = false;

void HandleInputSwitchPower()
{
    if (!isAnyInputInPowerDelay)
    { 
        return;
    }
    isAnyInputInPowerDelay = false;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (inputs[i]->powerOffDelay->value != 0 && currentInput != inputs[i] && inputs[i]->IsOn())
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
        if (currentInput == inputs[i])
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
void InputSwitch(ButtonType button)
{   
    isAnyInputInPowerDelay = true;
    Mute_Engage();
    
    switch(button)
    {
        case INPUT_ONE_BUTTON:
            IO_ISA_PORT = 0;
            IO_ISB_PORT = 0;
            currentInput = &inputOne;
            break;  
            
        case INPUT_TWO_BUTTON:
            IO_ISA_PORT = 1;
            IO_ISB_PORT = 0;
            currentInput = &inputTwo;
            break; 
            
        case INPUT_THREE_BUTTON:
            IO_ISA_PORT = 0;
            IO_ISB_PORT = 1;
            currentInput = &inputThree; 
            break;
            
        case INPUT_BT_BUTTON:
            IO_ISA_PORT = 1;
            IO_ISB_PORT = 1;
            currentInput = &inputBt;
            break;                        
            
        default:
            return;
    }
    
    // Reset all delay timers to start counting from THIS moment
    for(uint8_t i = 0; i < 4; i++) {
        inputs[i]->powerOffStartTime = systemTicks;
        inputs[i]->powerOnStartTime = systemTicks;
    }
}
