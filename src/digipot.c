#include "digipot.h"
#include "parameters.h"
#include "input.h"
#include "balance.h"
#include "mcc_generated_files/spi/spi1.h"
#include "mcc_generated_files\system\pins.h"
#include "mcc_generated_files/system/clock.h"


#define OUTPUT_DEFAULT_CENTER 80
#define KNOB_CENTER 127

#define MASTER_MAX_SHIFT_TOP 45   // how far master can push center up/down from 127 on the top range
#define MASTER_MAX_SHIFT_BOTTOM 57   // how far master can push center up/down from 127 on the bottom range
#define BALANCE_DEADZONE_CENTER 254 / 8 // deadzone for balance knob, within this range, the balance is considered centered

static inline void LFFCSSetLow(void)   { LFFCS_SetLow();  }
static inline void LFFCSSetHigh(void)  { LFFCS_SetHigh(); }
static inline void LFBCCSSetLow(void)  { LFBCCS_SetLow();  }
static inline void LFBCCSSetHigh(void) { LFBCCS_SetHigh(); }
static inline void LFQCSSetLow(void)   { LFQCS_SetLow();  }
static inline void LFQCSSetHigh(void)  { LFQCS_SetHigh(); }

static inline void HFFCSSetLow(void)   { HFFCS_SetLow();  }
static inline void HFFCSSetHigh(void)  { HFFCS_SetHigh(); }
static inline void HFBCCSSetLow(void)  { HFBCCS_SetLow();  }
static inline void HFBCCSSetHigh(void) { HFBCCS_SetHigh(); }
static inline void HFQCSSetLow(void)   { HFQCS_SetLow();  }
static inline void HFQCSSetHigh(void)  { HFQCS_SetHigh(); }

static inline void VOLCSSetLow(void)   { VOLCS_SetLow();  }
static inline void VOLCSSetHigh(void)  { VOLCS_SetHigh(); }

static inline void SLCSSetLow(void)    { SLCS_SetLow();  }
static inline void SLCSSetHigh(void)   { SLCS_SetHigh(); }

static inline void OGCSRSetLow(void)    { OGCSR_SetLow();  }
static inline void OGCSRSetHigh(void)   { OGCSR_SetHigh(); }
static inline void OGCSLSetLow(void)    { OGCSL_SetLow();  }
static inline void OGCSLSetHigh(void)   { OGCSL_SetHigh(); }

static inline void IGAINCSSetHigh(void)   { IGAINCS_SetHigh(); }
static inline void IGAINCSSetLow(void)   { IGAINCS_SetLow(); }

static const CS_Device_t lffPot       = { LFFCSSetLow,  LFFCSSetHigh };
static const CS_Device_t lfbcPot      = { LFBCCSSetLow, LFBCCSSetHigh };
static const CS_Device_t lfqPot       = { LFQCSSetLow,  LFQCSSetHigh };
static const CS_Device_t hffPot       = { HFFCSSetLow,  HFFCSSetHigh };
static const CS_Device_t hfbcPot      = { HFBCCSSetLow, HFBCCSSetHigh };
static const CS_Device_t hfqPot       = { HFQCSSetLow,  HFQCSSetHigh };
static const CS_Device_t volPot       = { VOLCSSetLow,  VOLCSSetHigh };
static const CS_Device_t subLevelPot  = { SLCSSetLow,   SLCSSetHigh };
static const CS_Device_t outputPotR  = { OGCSRSetLow,   OGCSRSetHigh};
static const CS_Device_t outputPotL  = { OGCSLSetLow,   OGCSLSetHigh };
static const CS_Device_t inputGainPot  = { IGAINCSSetLow,   IGAINCSSetHigh };
// digipot.c
void DigiPot_Init(void)
{
    lffPot.csHigh();
    lfbcPot.csHigh();
    lfqPot.csHigh();
    hffPot.csHigh();
    hfbcPot.csHigh();
    hfqPot.csHigh();
    volPot.csHigh();
    subLevelPot.csHigh();
    outputPotR.csHigh();
    outputPotL.csHigh();
    inputGainPot.csHigh();
}
void WriteWiper(const CS_Device_t *pot, uint8_t wiperAddr, uint8_t value)
{
    uint8_t txBuffer[2];
    txBuffer[0] = wiperAddr | 0x00;
    txBuffer[1] = value;

    SPI1_Host.Open(HOST_CONFIG);
    pot->csLow();
    SPI1_Host.BufferWrite(txBuffer, 2);
    pot->csHigh();
    SPI1_Host.Close();
}

void UpdateVolumeWipers(void)
{   
    WriteWiper(&volPot, W0, volumeKnob.value);
}

void UpdateLFBoostWipers(void)
{
    WriteWiper(&lfbcPot, W0, WIPER_MAX - lfBoostKnob.value);
}
void UpdateLFFrequencyWipers(void)
{
    WriteWiper(&lffPot, W0, WIPER_MAX - frequencyKnobLow.value);
}
void UpdateLFQWipers(void)
{
    WriteWiper(&lfqPot, W0, WIPER_MAX - QKnobLow.value);
}
void UpdateHFBoostWipers(void)
{
    WriteWiper(&hfbcPot, W0, WIPER_MAX - hfBoostKnob.value);
}
void UpdateHFFrequencyWipers(void)
{
    WriteWiper(&hffPot, W0, WIPER_MAX - frequencyKnobHigh.value);
}
void UpdateHFQWipers(void)
{
    WriteWiper(&hfqPot, W0, WIPER_MAX - QKnobHigh.value);
}
void UpdateSubLevelWipers(void)
{
    WriteWiper(&subLevelPot, W0, subLevelRightKnob.value);
}

void UpdateOutputWipers(void)
{
    // Map master (0-254) to a small +/- shift around 127
    int32_t masterDelta = (int32_t)subOuputKnob.value - (int32_t)KNOB_CENTER;
    int32_t max_shift   = masterDelta < 0 ? MASTER_MAX_SHIFT_BOTTOM : MASTER_MAX_SHIFT_TOP;
    int32_t center      = OUTPUT_DEFAULT_CENTER + (masterDelta * max_shift) / 127;

    // Balance: -127..+127, exactly 0 across the center hold
    int32_t balanceDelta = Balance_Offset(balanceKnob.value);
    int32_t ratio        = balanceDelta < 0 ? -balanceDelta : balanceDelta;

    // One wiper goes up while the other goes down by the same ratio
    int32_t up   = center + ((int32_t)(WIPER_MAX - center) * ratio) / 127;
    int32_t down = center - ((int32_t)(center - WIPER_MIN) * ratio) / 127;

    uint8_t leftValue  = (uint8_t)(balanceDelta < 0 ? up   : down);
    uint8_t rightValue = (uint8_t)(balanceDelta < 0 ? down : up);

    WriteWiper(&outputPotR, W0, rightValue);
    WriteWiper(&outputPotL, W0, leftValue);
}
void UpdateInputOneGainWipers(void)
{
    if (GetInputType() == INPUT_ONE)
        WriteWiper(&inputGainPot, W0, WIPER_MAX - inputOneGainKnob.value);
}
void UpdateInputTwoGainWipers(void)
{
    if (GetInputType() == INPUT_TWO)
        WriteWiper(&inputGainPot, W0, WIPER_MAX - inputTwoGainKnob.value);
}

void UpdateInputThreeGainWipers(void)
{
    if (GetInputType() == INPUT_THREE)
        WriteWiper(&inputGainPot, W0, WIPER_MAX - inputThreeGainKnob.value);
}

void UpdateInputBtGainWipers(void)
{
    if (GetInputType() == INPUT_BT)
        WriteWiper(&inputGainPot, W0, WIPER_MAX - inputBtGainKnob.value);
}


