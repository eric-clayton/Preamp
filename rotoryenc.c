#include <xc.h>
#include "rotoryenc.h"


// Adjust this based on your MCC settings. 
// If 1 tick = 64us, then 800 counts = ~51ms threshold.
#define FAST_THRESHOLD 10

#define DEBOUNCE_COOLDOWN 20

// A transition is only valid if it moves from one state to an adjacent valid state.
int8_t rot_states[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
bool ROTARYENC_Process(Encoder_t *knob, uint8_t RCA, uint8_t RCB, volatile uint32_t *systemTicks) 
{
    uint32_t timeDelta = *systemTicks - knob->lastChangeTime;
    
    // Combine pins into a 2-bit state
    uint8_t currentState = (RCA << 1) | RCB;
    // Shift previous state and combine with new
    uint8_t index = (knob->lastState << 2) | currentState;

    int8_t direction = rot_states[index];
    if (direction != 0) { // Hardware Debounce

        // --- THE ACCELERATION FIX ---
        // Only accelerate if moving in the SAME direction as the last pulse
        bool fastTurn = (direction == knob->lastDirection && timeDelta < FAST_THRESHOLD);
        // Apply to your Volume or Balance
        int stepSize = fastTurn ? knob->fastStep : knob->slowStep;

        int16_t newValue = knob->value + (direction * stepSize);
        // Enforce Boundaries (Clamping)
        if (newValue > knob->maxValue) {
            knob->value = knob->maxValue;
        } else if (newValue < 0) {
            knob->value = 0;
        } else {
            knob->value = (uint8_t)newValue;
        }

        // Update trackers
        knob->lastDirection = direction;
        knob->lastState = currentState;
        knob->lastChangeTime = *systemTicks;
        return true;
    }
    return false;  
}
