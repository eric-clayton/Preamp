#ifndef DIGIPOT_H
#define DIGIPOT_H

#include <stdint.h>

typedef void (*CS_SetFunc)(void);

typedef struct {
    CS_SetFunc csLow;
    CS_SetFunc csHigh;
} DigiPot_t;

void WriteWiper(const DigiPot_t *pot, uint8_t wiperAddr, uint8_t value);

void UpdateVolumeWipers(void);
void UpdateLFBoostWipers(void);
void UpdateLFFrequencyWipers(void);
void UpdateLFQWipers(void);
void UpdateHFBoostWipers(void);
void UpdateHFFrequencyWipers(void);
void UpdateHFQWipers(void);
void UpdateSubLevelWipers(void);

#endif