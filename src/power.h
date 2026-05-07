#ifndef POWER_H
#define POWER_H

#include <stdbool.h>

extern bool lastButtonState;
bool IsInputOneOn(void);
bool IsInputTwoOn(void);
bool IsInputThreeOn(void);
bool IsInputBtOn(void);
void ToggleInputOnePower(void);
void ToggleInputTwoPower(void);
void ToggleInputThreePower(void);
void ToggleInputBtPower(void);
void Power_HandleSleepWake(void);

#endif