#include "subcontrol.h"
#include "parameters.h"
#include "audio_control.h" // Contains S1_MASK through S8_MASK
#include <stdbool.h>

// Static tracking to maintain state for "Phase Correct" logic
static bool isSubEqEnabled = false;
static bool isPhase180 = false;

// Forward declaration for the logic helper
void UpdatePhaseCorrect(void);

/**
 * Handles Logic Condition 1 & 2:
 * Sub EQ ena: S1on, S2off, S3off, S4on
 * Sub EQ dis: S1off, S2on, S3on, S4off
 */
void UpdateSubEQ(void) {
    int16_t eq = Parameter_Interpolate(&subEqKnob);
    isSubEqEnabled = (eq != 0); 

    if (isSubEqEnabled) {
        SetSubEQ(true);
    } else {
        SetSubEQ(false);
    }
    
    // Changing EQ affects the Phase Correct logic
    UpdatePhaseCorrect();
}

/**
 * Handles Logic Condition 3 & 4:
 * Phase 180: S5off, S6on
 * Phase 0:   S5on, S6off
 */
void UpdateSubEnable(void) {
    int16_t state = Parameter_Interpolate(&subPhaseKnob);
    isPhase180 = (state == 2); 
    if(state == 0)
    {
        SetSubEn(false);
    }
    else if (isPhase180) {
        SetSubEn(true);
        SetSubPhase(true);
    } else {
        SetSubEn(true);
        SetSubPhase(false);
    }

    // Changing Phase affects the Phase Correct logic
    UpdatePhaseCorrect();
}

/**
 * Handles Logic Condition 5:
 * Phase correct logic: off when EQ == Phase (180=ena), on when !=
 */
void UpdatePhaseCorrect(void) {
    // Determine S7 state
    bool shouldBeCorrect = (isSubEqEnabled != isPhase180);
    
    SetPhaseCorrect(shouldBeCorrect);
}