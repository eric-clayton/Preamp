// systick.c
#include "systick.h"

volatile uint32_t systemTicks = 0;

void SysTick_Callback(void) {
    systemTicks++;
}