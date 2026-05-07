// display.h
#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void DisplayBoostCut(int16_t value);
void DisplayVolume(int16_t value);
void DisplayBalance(int16_t value);
void DisplayFreqLow(int16_t value);
void DisplayFreqHigh(int16_t value);
void DisplayQ(int16_t value);
void DisplaySubEnableDisable(int16_t value);
void DisplaySubEQ(int16_t value);
void DisplaySubLevelRight(int16_t value);
void DisplaySubLevelLeft(int16_t value);
void DisplayPowerDelayOn(int16_t value);
void DisplayPowerDelayOff(int16_t value);

void AS1115_DisplayPartition(int16_t number, uint8_t startReg, uint8_t numDigits);
void AS1115_DisplayPartitionDecimal(int16_t number, uint8_t startReg, uint8_t numDigits);
void AS1115_DisplayDataPartition(const uint8_t* data, uint8_t len, uint8_t startReg);

#endif