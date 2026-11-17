#ifndef BALANCE_H
#define BALANCE_H
#include <stdint.h>

#define BALANCE_DISPLAY_MAX 99
#define BAL_CENTER_CLICKS 4
#define BAL_MIN     (-(BALANCE_DISPLAY_MAX + BAL_CENTER_CLICKS))
#define BAL_MAX     (BALANCE_DISPLAY_MAX + BAL_CENTER_CLICKS)
#define BAL_START   0

static inline int16_t Balance_Offset(int16_t value)
{
    if (value < -BAL_CENTER_CLICKS)
        return (int16_t)(value + BAL_CENTER_CLICKS);
    if (value > BAL_CENTER_CLICKS)
        return (int16_t)(value - BAL_CENTER_CLICKS);
    return 0;
}

#endif