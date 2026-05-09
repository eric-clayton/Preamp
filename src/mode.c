#include <stddef.h>
#include "mode.h"
#include "rotoryenc.h"
#include "systick.h"
#include "storage.h"

#define DISPLAY_TIMEOUT 4000
SystemMode currentSystemMode = MODE_FREQ_LOW; 
Parameter_t* activeDisplay2Encoder = &volumeKnob;
Parameter_t* activeParameters[6] = {&lfBoostKnob, &frequencyKnobLow, &QKnobLow, &hfBoostKnob, &balanceKnob, &volumeKnob};
uint32_t display2Timer = 0;

void UpdateEncoders()
{
    for(uint8_t i = 0; i < 6; i++)
    {
        if(ROTARYENC_Process(&physicalKnobs[i], activeParameters[i], systemTicks))
        {
            Parameter_t* current = activeParameters[i];
            if (current == &lfBoostKnob) {
                SwitchMode(MODE_FREQ_LOW);
            } 
            else if (current == &hfBoostKnob) {
                SwitchMode(MODE_FREQ_HIGH);
            } 
            else if (current == &balanceKnob) {
                activeDisplay2Encoder = current;
                display2Timer = systemTicks;
            } 
            else if (current == &volumeKnob) {
                activeDisplay2Encoder = current;
            }
            current->isDirty = true;
            Parameter_Display(current);
            Parameter_Update(current);
            Storage_MarkDirty();
        }
    }
    if ((currentSystemMode == MODE_FREQ_LOW || currentSystemMode == MODE_FREQ_HIGH) && activeDisplay2Encoder != &volumeKnob) {
        if ((systemTicks - display2Timer) >= DISPLAY_TIMEOUT) {
            Parameter_Display(&volumeKnob);
        }
    }
}
void InitializeNormalMode()
{
    SwitchMode(MODE_FREQ_LOW);
    Parameter_Display(&volumeKnob);
    Parameter_Display(&lfBoostKnob);
    
    activeDisplay2Encoder = &volumeKnob;
}
void InitializeSubSettingModes(SystemMode mode)
{
    SwitchMode(mode);
    switch(mode) {
        case MODE_SUB:
            Parameter_Display(&subPhaseKnob);
            break;
            
        case MODE_INPUT_ONE_POWER:
            Parameter_Display(&inputOneOnKnob);
            break;
            
        case MODE_INPUT_TWO_POWER:
            Parameter_Display(&inputTwoOnKnob);
            break;
            
        case MODE_INPUT_THREE_POWER:
            Parameter_Display(&inputThreeOnKnob);
            break;
            
        case MODE_INPUT_BT_POWER:
            Parameter_Display(&inputBtOnKnob);
            break;
            
        default:
            break;
    }
}
void SwitchMode(SystemMode newMode) {
    if(currentSystemMode == newMode)
        return;

    switch(newMode) {
        case MODE_FREQ_LOW:
            activeParameters[0] = &lfBoostKnob;
            activeParameters[1] = &frequencyKnobLow;
            activeParameters[2] = &QKnobLow;
            activeParameters[3] = &hfBoostKnob;
            activeParameters[4] = &balanceKnob;
            activeParameters[5] = &volumeKnob;
            break;
        case MODE_FREQ_HIGH:
            activeParameters[0] = &lfBoostKnob;
            activeParameters[1] = &frequencyKnobHigh;
            activeParameters[2] = &QKnobHigh;
            activeParameters[3] = &hfBoostKnob;
            activeParameters[4] = &balanceKnob;
            activeParameters[5] = &volumeKnob;
            break;
        case MODE_SUB:
            activeParameters[0] = &subLevelLeftKnob;
            activeParameters[1] = &subEqKnob;
            activeParameters[2] = &subPhaseKnob;
            activeParameters[3] = &subLevelRightKnob;
            activeParameters[4] = NULL;
            activeParameters[5] = NULL;
            break;
        case MODE_INPUT_ONE_POWER:
            activeParameters[0] = &inputOneOnKnob;
            activeParameters[1] = &inputOneOffKnob;
            activeParameters[2] = NULL;
            activeParameters[3] = NULL;
            activeParameters[4] = NULL;
            activeParameters[5] = NULL;
            break;
        case MODE_INPUT_TWO_POWER:
            activeParameters[0] = &inputTwoOnKnob;
            activeParameters[1] = &inputTwoOffKnob;
            activeParameters[2] = NULL;
            activeParameters[3] = NULL;
            activeParameters[4] = NULL;
            activeParameters[5] = NULL;
            break;
        case MODE_INPUT_THREE_POWER:
            activeParameters[0] = &inputThreeOnKnob;
            activeParameters[1] = &inputThreeOffKnob;
            activeParameters[2] = NULL;
            activeParameters[3] = NULL;
            activeParameters[4] = NULL;
            activeParameters[5] = NULL;
            break;
        case MODE_INPUT_BT_POWER:
            activeParameters[0] = &inputBtOnKnob;
            activeParameters[1] = &inputBtOffKnob;
            activeParameters[2] = NULL;
            activeParameters[3] = NULL;
            activeParameters[4] = NULL;
            activeParameters[5] = NULL;
            break;
    }  
    currentSystemMode = newMode;
}