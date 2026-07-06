#ifndef POWER_H
#define POWER_H

#include <stdbool.h>
#include <stdint.h>

bool IsInputOneOn(void);
bool IsInputTwoOn(void);
bool IsInputThreeOn(void);
bool IsInputBtOn(void);
void ToggleInputOnePower(void);
void ToggleInputTwoPower(void);
void ToggleInputThreePower(void);
void ToggleInputBtPower(void);
void HandleRemotePowerButton(void);
void Power_EnterSleep(void);      // does the actual power-down + SLEEP() + wake sequence
void Power_HandleSleepWake(void); // the runtime polling entry point (unchanged behavior)
void Power_ApplyLoadedState(void);// call once at startup after EEPROM load
uint8_t GetPowerState(void);
void Power_LoadSettings(uint8_t isOn);
void SetPowerState(uint8_t isOn);


#endif