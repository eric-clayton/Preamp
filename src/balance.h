#ifndef BALANCE_H
#define BALANCE_H
#include <stdint.h>

#define BAL_HOLD    4                          // 5 ticks to leave center either way
#define BAL_MIN     0
#define BAL_MAX     254
#define BAL_MID     127
#define BAL_C_LO    (BAL_MID - BAL_HOLD)       // first tick of the hold (123)
#define BAL_C_HI    (BAL_MID + BAL_HOLD)       // last tick of the hold  (131)
#define BAL_START   BAL_MID
#define BAL_SPAN    (BAL_MID - BAL_HOLD)       // ticks from the hold to either end stop (123)

static inline int16_t Balance_Offset(int16_t pos)
{
    if (pos < BAL_C_LO) return (int16_t)(pos - BAL_C_LO);   // -123..-1
    if (pos > BAL_C_HI) return (int16_t)(pos - BAL_C_HI);   //   1..123
    return 0;
}
#endif