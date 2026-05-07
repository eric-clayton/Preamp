#include "digipot.h"
#include "parameters.h"
#include "mcc_generated_files/spi/spi1.h"
#include "mcc_generated_files\system\pins.h"

// MCP4262 - dual wiper (volatile only)
#define MCP4262_W0  (0 << 4)   // 0x00
#define MCP4262_W1  (1 << 4)   // 0x10

// MCP4232 - same address map as MCP4262
#define MCP4232_W0  (0 << 4)   // 0x00 - P0W - Right sub level
#define MCP4232_W1  (1 << 4)   // 0x10 - P1W - Left sub level

// MCP4351 - quad wiper (volatile only)
#define MCP4351_W0  (0 << 4)   // 0x00
#define MCP4351_W1  (1 << 4)   // 0x10
#define MCP4351_W2  (6 << 4)   // 0x60
#define MCP4351_W3  (7 << 4)   // 0x70

static inline void LFACS_SetLow(void)  { IO_LFACS_SetLow();  }
static inline void LFACS_SetHigh(void) { IO_LFACS_SetHigh(); }
static inline void LFBCS_SetLow(void)  { IO_LFBCS_SetLow();  }
static inline void LFBCS_SetHigh(void) { IO_LFBCS_SetHigh(); }

static inline void HFACS_SetLow(void)  { IO_HFACS_SetLow();  }
static inline void HFACS_SetHigh(void) { IO_HFACS_SetHigh(); }
static inline void HFBCS_SetLow(void)  { IO_HFBCS_SetLow();  }
static inline void HFBCS_SetHigh(void) { IO_HFBCS_SetHigh(); }

static inline void VOLCS_SetLow(void)  { IO_VOLCS_SetLow();  }
static inline void VOLCS_SetHigh(void) { IO_VOLCS_SetHigh(); }

static inline void SLCS_SetLow(void)  { IO_SLCS_SetLow();  }
static inline void SLCS_SetHigh(void) { IO_SLCS_SetHigh(); }

static const DigiPot_t lfRightPot = {LFACS_SetLow,  LFACS_SetHigh};
static const DigiPot_t lfLeftPot  = {LFBCS_SetLow,  LFBCS_SetHigh};
static const DigiPot_t hfRightPot = {HFACS_SetLow,  HFACS_SetHigh};
static const DigiPot_t hfLeftPot  = {HFBCS_SetLow,  HFBCS_SetHigh};
static const DigiPot_t volPot     = {VOLCS_SetLow,  VOLCS_SetHigh};
static const DigiPot_t subLevelPot = {SLCS_SetLow, SLCS_SetHigh};

void WriteWiper(const DigiPot_t *pot, uint8_t wiperAddr, uint8_t value) {
    uint8_t txBuffer[2];
    txBuffer[0] = wiperAddr | 0x00;
    txBuffer[1] = value;

    SPI1_Host.Open(SPI1_DEFAULT);
    pot->csLow();
    SPI1_Host.BufferWrite(txBuffer, 2);
    pot->csHigh();
    SPI1_Host.Close();
}
void UpdateVolumeWipers(void) {
    int16_t baseVol = volumeKnob.value;
    int16_t bal = balanceKnob.value; // 0 to 254, center is 127

    int16_t leftVol = baseVol;
    int16_t rightVol = baseVol;

    // Apply Balance Logic (Attenuate the opposite channel)
    if (bal < 127) {
        // Panning Left: Reduce Right channel
        rightVol -= (127 - bal); 
    } else if (bal > 127) {
        // Panning Right: Reduce Left channel
        leftVol -= (bal - 127);
    }
    // Clamp values to valid 0-254 range
    if (leftVol < 0) leftVol = 0;
    if (rightVol < 0) rightVol = 0;
    if (leftVol > 254) leftVol = 254;
    if (rightVol > 254) rightVol = 254;

    // Apply Inverse Log Taper (Linear to Audio taper)
    // uint8_t finalLeft = audioTaper[leftVol];
    // uint8_t finalRight = audioTaper[rightVol];
    uint8_t finalLeft = (uint8_t)leftVol;   // Remove this once lookup table is ready
    uint8_t finalRight = (uint8_t)rightVol; // Remove this once lookup table is ready
    WriteWiper(&volPot, MCP4262_W0, finalRight);
    WriteWiper(&volPot, MCP4262_W1, finalLeft);
}

void UpdateLFBoostWipers()
{
    WriteWiper(&lfRightPot, MCP4351_W3, lfBoostKnob.value);
    WriteWiper(&lfLeftPot, MCP4351_W3, lfBoostKnob.value);
}
void UpdateLFFrequencyWipers()
{
    WriteWiper(&lfRightPot, MCP4351_W0, frequencyKnobLow.value);
    WriteWiper(&lfLeftPot, MCP4351_W0, frequencyKnobLow.value);
    WriteWiper(&lfRightPot, MCP4351_W1, frequencyKnobLow.value);
    WriteWiper(&lfLeftPot, MCP4351_W1, frequencyKnobLow.value);
}
void UpdateLFQWipers()
{
    WriteWiper(&lfRightPot, MCP4351_W2, QKnobLow.value);
    WriteWiper(&lfLeftPot, MCP4351_W2, QKnobLow.value);
}
void UpdateHFBoostWipers()
{
    WriteWiper(&hfRightPot, MCP4351_W3, hfBoostKnob.value);
    WriteWiper(&hfLeftPot, MCP4351_W3, hfBoostKnob.value);
}
void UpdateHFFrequencyWipers()
{
    WriteWiper(&hfRightPot, MCP4351_W0, frequencyKnobHigh.value);
    WriteWiper(&hfLeftPot, MCP4351_W0, frequencyKnobHigh.value);
    WriteWiper(&hfRightPot, MCP4351_W1, frequencyKnobHigh.value);
    WriteWiper(&hfLeftPot, MCP4351_W1, frequencyKnobHigh.value);
}
void UpdateHFQWipers()
{
    WriteWiper(&hfRightPot, MCP4351_W2, QKnobHigh.value);
    WriteWiper(&hfLeftPot, MCP4351_W2, QKnobHigh.value);
}

void UpdateSubLevelWipers(void) {
    WriteWiper(&subLevelPot, MCP4232_W0, subLevelRightKnob.value);
    WriteWiper(&subLevelPot, MCP4232_W1, subLevelLeftKnob.value);
}