#include "subcontrol.h"
#include "parameters.h"
#include "audio_control.h"
#include <stdbool.h>

// Static tracking to maintain state for "Phase Correct" logic
static bool isSubEqEnabled = false;
static bool isPhase180 = false;

// Forward declaration for the logic helper
void UpdatePhaseCorrect(void);

/**
 * Selects sub EQ enable through the SEQ output.
 */
void UpdateSubEQ(void) {
    int16_t eq = subEqKnob.value / SUB_EQ_STEPS_PER_OPTION;
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
 * Selects sub phase through PHINV and disables the sub output at state zero.
 */
void UpdateSubEnable(void) {
    int16_t state = subPhaseKnob.value / SUB_PHASE_STEPS_PER_OPTION;
    isPhase180 = (state == 2); 
    if(state == 0)
    {
        SetSubEn(false);
    }
    else if (isPhase180) {
        SetSubEn(true);
        SetSubPhase(false);
    } else {
        SetSubEn(true);
        SetSubPhase(true);
    }

    // Changing Phase affects the Phase Correct logic
    UpdatePhaseCorrect();
}

/**
 * Handles Logic Condition 5:
 * Phase correct logic: off when EQ == Phase (180=ena), on when !=
 */
void UpdatePhaseCorrect(void) {
    // Phase correction depends on the selected EQ and phase.
    bool shouldBeCorrect = (isSubEqEnabled != isPhase180);
    
    SetPhaseCorrect(shouldBeCorrect);
}