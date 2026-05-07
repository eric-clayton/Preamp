#include <xc.h>
#include "rotoryenc.h"
#include "mcc_generated_files/system/pins.h"

// Adjust this based on your MCC settings. 
// If 1 tick = 64us, then 800 counts = ~51ms threshold.
#define FAST_THRESHOLD 10

static RCValues ReadKnobOne()   { return (RCValues){IO_LFA_PORT,  IO_LFB_PORT};  }
static RCValues ReadKnobTwo()   { return (RCValues){IO_FREQA_PORT,IO_FREQB_PORT};}
static RCValues ReadKnobThree() { return (RCValues){IO_RQA_PORT,  IO_RQB_PORT};  }
static RCValues ReadKnobFour()  { return (RCValues){IO_HFA_PORT,  IO_HFB_PORT};  }
static RCValues ReadKnobFive()  { return (RCValues){IO_BALA_PORT, IO_BALB_PORT}; }
static RCValues ReadKnobSix()   { return (RCValues){IO_VOLA_PORT, IO_VOLB_PORT}; }

PhysicalKnob_t physicalKnobs[KNOB_COUNT] = {
    {ReadKnobOne,   0, 0, 0},
    {ReadKnobTwo,   0, 0, 0},
    {ReadKnobThree, 0, 0, 0},
    {ReadKnobFour,  0, 0, 0},
    {ReadKnobFive,  0, 0, 0},
    {ReadKnobSix,   0, 0, 0},
};

void ROTARYENC_Initialize(void) {
    for (uint8_t i = 0; i < KNOB_COUNT; i++) {
        ROTARYENC_UpdateLastState(&physicalKnobs[i]);
    }
}
void ROTARYENC_UpdateLastState(PhysicalKnob_t *hw)
{
    RCValues rcValues = hw->ReadHardware(); 
    
    uint8_t currentState = (uint8_t)(rcValues.RCA << 1) | rcValues.RCB;
    hw->lastState = currentState;
}
// A transition is only valid if it moves from one state to an adjacent valid state.
int8_t rot_states[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
bool ROTARYENC_Process(PhysicalKnob_t *hw, Parameter_t *param, uint32_t systemTicks) 
{
    if (param == NULL) return false; // Safety check if knob is "unmapped"

    uint32_t timeDelta = systemTicks - hw->lastChangeTime;
    
    // We pass the hardware ID to get the pins
    RCValues rcValues = hw->ReadHardware(); 
    
    uint8_t currentState = (uint8_t)((rcValues.RCA << 1) | rcValues.RCB);
    uint8_t index = (uint8_t)((hw->lastState << 2) | currentState);
    int8_t direction = rot_states[index];

    if (direction != 0) {
        // Acceleration logic stays with the Physical Hardware
        bool fastTurn = (direction == hw->lastDirection && timeDelta < FAST_THRESHOLD);
        int stepSize = fastTurn ? param->fastStep : param->slowStep;

        int16_t newValue = param->value + (direction * stepSize);

        // Clamping logic applies to the Parameter
        if (newValue > param->maxValue) {
            param->value = param->isLooping ? 0 : param->maxValue;
        } else if (newValue < 0) {
            param->value = param->isLooping ? param->maxValue : 0;
        } else {
            param->value = (uint8_t)newValue;
        }

        // Update Physical trackers
        hw->lastDirection = direction;
        hw->lastState = currentState;
        hw->lastChangeTime = systemTicks;

        return true;
    }
    return false;  
}
