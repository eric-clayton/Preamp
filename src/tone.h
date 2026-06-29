#ifndef TONE_H
#define TONE_H
#include <stdint.h>

uint8_t isToneOn = 0;
void Tone_Init(void);
void Tone_LoadSettings(uint8_t tone);
uint8_t GetToneValue(void);
void ToggleTone(void);  

#endif