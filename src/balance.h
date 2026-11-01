#ifndef BALANCE_H
#define BALANCE_H
#include <stdint.h>

#define BAL_HOLD    2                          // ticks held on each side of center
#define BAL_C_LO    127                        // first center tick
#define BAL_C_HI    (BAL_C_LO + 2*BAL_HOLD)    // last center tick (center = 5 ticks wide)
#define BAL_MIN     0
#define BAL_MAX     (254 + 2*BAL_HOLD)
#define BAL_START   (BAL_C_LO + BAL_HOLD)      // knob position at center

// Knob position -> -127..+127, exactly 0 across the whole center hold
static inline int16_t Balance_Offset(int16_t pos)
{
    if (pos < BAL_C_LO) return (int16_t)(pos - BAL_C_LO);
    if (pos > BAL_C_HI) return (int16_t)(pos - BAL_C_HI);
    return 0;
}
#endif