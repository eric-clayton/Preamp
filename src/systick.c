// systick.c
#include "systick.h"

volatile uint32_t systemTicks = 0;

uint32_t SysTick_Now(void)
{
    uint32_t ticks;
    do {
        ticks = systemTicks;
    } while (ticks != systemTicks);
    return ticks;
}

void SysTick_Callback(void) {
    systemTicks++;
}