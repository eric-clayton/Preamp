#ifndef DIGIPOT_H
#define DIGIPOT_H

#include <stdint.h>
#include "cs_device.h"

// True digital potentiometers: variable-resistance devices addressed by
// wiper address + value over SPI. Each WriteWiper call targets exactly one
// wiper and does not affect others. This file does NOT cover the 74HC595
// or ADG1414 chains -- those are full-word shift registers, see
// shift_register.h.

#define W0  (0 << 4)   // 0x00

void DigiPot_Init(void);
void WriteWiper(const CS_Device_t *pot, uint8_t wiperAddr, uint8_t value);

void UpdateVolumeWipers(void);
void UpdateLFBoostWipers(void);
void UpdateLFFrequencyWipers(void);
void UpdateLFQWipers(void);
void UpdateHFBoostWipers(void);
void UpdateHFFrequencyWipers(void);
void UpdateHFQWipers(void);
void UpdateSubLevelWipers(void);
void UpdateOutputWipers(void);
void UpdateInputOneGainWipers(void);
void UpdateInputTwoGainWipers(void);
void UpdateInputThreeGainWipers(void);
void UpdateInputBtGainWipers(void);

#endif
