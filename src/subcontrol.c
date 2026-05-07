// subcontrol.c
#include "subcontrol.h"
#include "parameters.h"
#include "mcc_generated_files/system/pins.h"

void UpdateSubEnable(void) {
    int16_t state = Parameter_Interpolate(&subPhaseKnob);
    // 0 = disabled, 1 = phase 0, 2 = phase 180
    // set IO_SUBEN and IO_PHASE pins accordingly
    IO_SUBEN_SetLow();   // default disable

    switch(state) {
        case 0:
            IO_SUBEN_SetLow();
            break;
        case 1:
            IO_SUBEN_SetHigh();
            IO_PHASE_SetLow();
            break;
        case 2:
            IO_SUBEN_SetHigh();
            IO_PHASE_SetHigh();
            break;
    }
}

void UpdateSubEQ(void) {
    int16_t eq = Parameter_Interpolate(&subEqKnob);
    if (eq == 0)
        IO_LFEQ_SetLow();
    else
        IO_LFEQ_SetHigh();
}