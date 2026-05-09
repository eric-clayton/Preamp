#ifndef TONE_H
#define TONE_H
#include <stdint.h>

void InitializeTone(uint8_t tone);
uint8_t GetToneValue(void);
void ToggleTone(void);  

#endif