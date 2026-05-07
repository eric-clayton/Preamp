// systick.h
#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

extern volatile uint32_t systemTicks;

void SysTick_Callback(void);   // registered with TMR0 in main.c

#endif