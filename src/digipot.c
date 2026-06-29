#include "digipot.h"
#include "parameters.h"
#include "mcc_generated_files/spi/spi1.h"
#include "mcc_generated_files\system\pins.h"

// 74HC595
#define W0  (0 << 4)   // 0x00
#define W1  (1 << 4)   // 0x10
#define IO_EN_MASK    0x0001
#define DV1_MASK      0x0010
#define DV2_MASK      0x0020
#define DV3_MASK      0x0040
#define SUBEN_MASK    0x0080
#define PP_MASK       0x0100
#define NEXT_MASK    0x0200
#define PREV_MASK    0x0400
#define ISA_MASK     0x0800
#define ISB_MASK     0x1000
#define DVBT_MASK    0x2000
#define TONE_MASK    0x4000

static inline void LFFCSSetLow(void)  { LFFCS_SetLow();  }
static inline void LFFCSSetHigh(void)  { LFFCS_SetHigh();  }
static inline void LFBCCSSetLow(void)  { LFBCCS_SetLow();  }
static inline void LFBCCSSetHigh(void)  { LFBCCS_SetHigh();  }
static inline void LFQCSSetLow(void)  { LFQCS_SetLow();  }
static inline void LFQCSSetHigh(void)  { LFQCS_SetHigh();  }


static inline void HFFCSSetLow(void)  { HFFCS_SetLow();  }
static inline void HFFCSSeHigh(void)  { HFFCS_SetHigh();  }
static inline void HFBCCSSetLow(void)  { HFBCCS_SetLow();  }
static inline void HFBCCSSetHigh(void)  { HFBCCS_SetHigh();  }
static inline void HFFCSSetHigh(void)  { HFFCS_SetHigh();  }
static inline void HFQCSSetLow(void)  { HFQCS_SetLow();  }
static inline void HFQCSSetHigh(void)  { HFQCS_SetHigh();  }

static inline void VOLCSSetLow(void)  { VOLCS_SetLow();  }
static inline void VOLCSSetHigh(void) { VOLCS_SetHigh(); }

static inline void SLCSSetLow(void)  { SLCS_SetLow();  }
static inline void SLCSSetHigh(void) { SLCS_SetHigh(); }

static inline void O_RCSetLow(void)  { O_RC_SetLow();  }
static inline void O_RCSetHigh(void) { O_RC_SetHigh(); }


static const DigiPot_t lffPot = {LFFCSSetLow,  LFFCSSetHigh};
static const DigiPot_t lfbcPot  = {LFBCCSSetLow,  LFBCCSSetHigh};
static const DigiPot_t lfqPot = {LFQCSSetLow,  LFQCSSetHigh};
static const DigiPot_t hffPot = {HFFCSSetLow,  HFFCSSetHigh};
static const DigiPot_t hfbcPot  = {HFBCCSSetLow,  HFBCCSSetHigh};
static const DigiPot_t hfqPot = {HFQCSSetLow,  HFQCSSetHigh};
static const DigiPot_t volPot     = {VOLCSSetLow,  VOLCSSetHigh};
static const DigiPot_t subLevelPot = {SLCSSetLow, SLCSSetHigh};
static const DigiPot_t outputExpanderPot = {O_RCSetLow, O_RCSetHigh};

static uint16_t outputExpanderRegisterState = 0x0000;

void WriteWiper(const DigiPot_t *pot, uint8_t wiperAddr, uint8_t value) {
    uint8_t txBuffer[2];
    txBuffer[0] = wiperAddr | 0x00;
    txBuffer[1] = value;

    SPI1_Host.Open(HOST_CONFIG);
    pot->csLow();
    SPI1_Host.BufferWrite(txBuffer, 2);
    pot->csHigh();
    SPI1_Host.Close();

}
void WriteRegister(const DigiPot_t *pot) {
    // Prepare the 2-byte SPI transfer buffer
    uint8_t txBuffer[2];
    
    // Split the 16-bit state into two bytes
    // Note: If your physical PCB wiring expects the low byte first, swap these indices.
    txBuffer[0] = (uint8_t)(outputExpanderRegisterState >> 8);   // MSB (Second chip in the chain)
    txBuffer[1] = (uint8_t)(outputExpanderRegisterState & 0xFF);  // LSB (First chip in the chain)

    // Send over SPI to latch the new outputs
    SPI1_Host.Open(HOST_CONFIG);
    pot->csLow();
    
    SPI1_Host.BufferWrite(txBuffer, 2);
    
    pot->csHigh(); // Pulse latch pin to apply the changes to physical pins
    SPI1_Host.Close();
}
void SetExpanderRegister(uint16_t bitMask, uint8_t value)
{
    if (value)
    {
       outputExpanderRegisterState |= bitMask;
    }
    else
    {
        outputExpanderRegisterState &= ~bitMask;
    }
    WriteRegister(&outputExpanderPot);
} 
void ToggleExpanderRegister(uint16_t bitMask)
{
    outputExpanderRegisterState ^= bitMask;
    WriteRegister(&outputExpanderPot);
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
    WriteWiper(&volPot, W0, finalRight);
    WriteWiper(&volPot, W1, finalLeft);
}

void UpdateLFBoostWipers()
{
    WriteWiper(&lfbcPot, W0, lfBoostKnob.value);
}
void UpdateLFFrequencyWipers()
{
    WriteWiper(&lffPot, W0, frequencyKnobLow.value);
}
void UpdateLFQWipers()
{
    WriteWiper(&lfqPot, W0, QKnobLow.value);
}
void UpdateHFBoostWipers()
{
    WriteWiper(&hfbcPot, W0, hfBoostKnob.value);
}
void UpdateHFFrequencyWipers()
{
    WriteWiper(&hffPot, W0, frequencyKnobHigh.value);
}
void UpdateHFQWipers()
{
    WriteWiper(&hfqPot, W0, QKnobHigh.value);
}

void UpdateSubLevelWipers(void) {
    WriteWiper(&subLevelPot, W0, subLevelRightKnob.value);
}
void DV1_Toggle()
{
    ToggleExpanderRegister(DV1_MASK);
}
void DV2_Toggle()
{
    ToggleExpanderRegister(DV2_MASK);
}
void DV3_Toggle()
{
    ToggleExpanderRegister(DV3_MASK);
}
void DVBT_Toggle()
{
    ToggleExpanderRegister(DVBT_MASK);
}
void SetInputState(uint8_t ISA, uint8_t ISB)
{
    SetExpanderRegister(ISA_MASK, ISA);
    SetExpanderRegister(ISB_MASK, ISB);
}
bool IsInputOneExpanderBitSet(void)
{
    return (outputExpanderRegisterState & DV1_MASK) != 0;
}
bool IsInputTwoExpanderBitSet(void)
{
    return (outputExpanderRegisterState & DV2_MASK) != 0;
}
bool IsInputThreeExpanderBitSet(void)
{
    return (outputExpanderRegisterState & DV3_MASK) != 0;
}
bool IsInputBTExpanderBitSet(void)
{
    return (outputExpanderRegisterState & DVBT_MASK) != 0;
}
