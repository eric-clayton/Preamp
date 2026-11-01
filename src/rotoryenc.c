#include <xc.h>
#include "rotoryenc.h"
#include "mcc_generated_files/system/pins.h"

// Adjust this based on your MCC settings. 
// If 1 tick = 64us, then 800 counts = ~51ms threshold.
#define FAST_THRESHOLD 10

static RCValues ReadKnobOne()   { return (RCValues){LFA_PORT,  LFB_PORT};  }
static RCValues ReadKnobTwo()   { return (RCValues){FREQA_PORT,FREQB_PORT};}
static RCValues ReadKnobThree() { return (RCValues){QA_PORT,  QB_PORT};  }
static RCValues ReadKnobFour()  { return (RCValues){HFA_PORT,  HFB_PORT};  }
static RCValues ReadKnobFive()  { return (RCValues){BALA_PORT, BALB_PORT}; }
static RCValues ReadKnobSix()   { return (RCValues){VOLA_PORT, VOLB_PORT}; }

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
// Reads one knob. Returns -1, 0 or +1; *fast is set when the turn is fast.
int8_t ROTARYENC_Read(PhysicalKnob_t *hw, uint32_t systemTicks, bool *fast)
{
    uint32_t timeDelta = systemTicks - hw->lastChangeTime;
    RCValues rcValues  = hw->ReadHardware();
    uint8_t currentState = (uint8_t)((rcValues.RCA << 1) | rcValues.RCB);
    uint8_t index        = (uint8_t)((hw->lastState << 2) | currentState);
    int8_t  direction    = rot_states[index];

    if (direction == 0) return 0;

    *fast = (direction == hw->lastDirection && timeDelta < FAST_THRESHOLD);

    hw->lastDirection  = direction;
    hw->lastState      = currentState;
    hw->lastChangeTime = systemTicks;
    return direction;
}
