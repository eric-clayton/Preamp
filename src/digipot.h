#ifndef DIGIPOT_H
#define DIGIPOT_H

#include <stdint.h>
#include <stdbool.h>

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
void DV1_Toggle(void);
void DV2_Toggle(void);
void DV3_Toggle(void);
void DVBT_Toggle(void);
void SetInputState(uint8_t ISA, uint8_t ISB);
bool IsInputOneExpanderBitSet(void);
bool IsInputTwoExpanderBitSet(void);
bool IsInputThreeExpanderBitSet(void);
bool IsInputBTExpanderBitSet(void);
#endif