#include "digipot.h"
#include "parameters.h"
#include "input.h"
#include "balance.h"
#include "mcc_generated_files/spi/spi1.h"
#include "mcc_generated_files\system\pins.h"
#include "mcc_generated_files/system/clock.h"

#define OUTPUT_DEFAULT_CENTER 80
#define KNOB_CENTER 127

#define MASTER_MAX_SHIFT_TOP 45    // how far master can push center up/down from 127 on the top range
#define MASTER_MAX_SHIFT_BOTTOM 57   // how far master can push center up/down from 127 on the bottom range
#define BALANCE_DEADZONE_CENTER (254 / 8) // deadzone for balance knob, within this range, the balance is considered centered

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

static inline void IGAINCSSetHigh(void)  { IGAINCS_SetHigh(); }
static inline void IGAINCSSetLow(void)   { IGAINCS_SetLow(); }

static const CS_Device_t lffPot       = { LFFCSSetLow,  LFFCSSetHigh };
static const CS_Device_t lfbcPot      = { LFBCCSSetLow, LFBCCSSetHigh };
static const CS_Device_t lfqPot       = { LFQCSSetLow,  LFQCSSetHigh };
static const CS_Device_t hffPot       = { HFFCSSetLow,  HFFCSSetHigh };
static const CS_Device_t hfbcPot      = { HFBCCSSetLow, HFBCCSSetHigh };
static const CS_Device_t hfqPot       = { HFQCSSetLow,  HFQCSSetHigh };
static const CS_Device_t volPot       = { VOLCSSetLow,  VOLCSSetHigh };
static const CS_Device_t subLevelPot  = { SLCSSetLow,   SLCSSetHigh };
static const CS_Device_t outputPotR   = { OGCSRSetLow,   OGCSRSetHigh};
static const CS_Device_t outputPotL   = { OGCSLSetLow,   OGCSLSetHigh };
static const CS_Device_t inputGainPot = { IGAINCSSetLow,   IGAINCSSetHigh };

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
    WriteWiper(&volPot, W0, Parameter_GetWiperValue(&volumeKnob));
}

void UpdateLFBoostWipers(void)
{
    WriteWiper(&lfbcPot, W0, Parameter_GetWiperValue(&lfBoostKnob));
}

void UpdateLFFrequencyWipers(void)
{
    WriteWiper(&lffPot, W0, Parameter_GetWiperValue(&frequencyKnobLow));
}

void UpdateLFQWipers(void)
{
    WriteWiper(&lfqPot, W0, Parameter_GetWiperValue(&QKnobLow));
}

void UpdateHFBoostWipers(void)
{
    WriteWiper(&hfbcPot, W0, Parameter_GetWiperValue(&hfBoostKnob));
}

void UpdateHFFrequencyWipers(void)
{
    WriteWiper(&hffPot, W0, Parameter_GetWiperValue(&frequencyKnobHigh));
}

void UpdateHFQWipers(void)
{
    WriteWiper(&hfqPot, W0, Parameter_GetWiperValue(&QKnobHigh));
}

void UpdateSubLevelWipers(void)
{
    WriteWiper(&subLevelPot, W0, Parameter_GetWiperValue(&subLevelRightKnob));
}

void UpdateOutputWipers(void)
{
    // Map master (0-254) to a small +/- shift around 127
    int32_t masterDelta = (int32_t)subOuputKnob.value - (int32_t)KNOB_CENTER;
    int32_t max_shift   = masterDelta < 0 ? MASTER_MAX_SHIFT_BOTTOM : MASTER_MAX_SHIFT_TOP;
    int32_t center      = OUTPUT_DEFAULT_CENTER + (masterDelta * max_shift) / 127;

    int32_t balanceDelta = Balance_Offset(balanceKnob.value);            // -BAL_SPAN..+BAL_SPAN
    int32_t ratio = ((balanceDelta < 0 ? -balanceDelta : balanceDelta) * 127) / BAL_SPAN;   // 0..127

    // One wiper goes up while the other goes down by the same ratio
    int32_t up   = center + ((int32_t)(WIPER_MAX - center) * ratio) / 127;
    int32_t down = center - ((int32_t)(center - WIPER_MIN) * ratio) / 127;

    uint8_t leftValue  = (uint8_t)(balanceDelta < 0 ? up   : down);
    uint8_t rightValue = (uint8_t)(balanceDelta < 0 ? down : up);

    WriteWiper(&outputPotR, W0, rightValue);
    WriteWiper(&outputPotL, W0, leftValue);
}

void UpdateInputGainWipers(void)
{
    Parameter_t *activeGainKnob = NULL;

    switch (GetInputType()) {
        case INPUT_ONE:   
            activeGainKnob = &inputOneGainKnob; 
            break;
        case INPUT_TWO:   
            activeGainKnob = &inputTwoGainKnob; 
            break;
        case INPUT_THREE: 
            activeGainKnob = &inputThreeGainKnob; 
            break;
        case INPUT_BT:    
            activeGainKnob = &inputBtGainKnob; 
            break;
        default: 
            return;
    }

    WriteWiper(&inputGainPot, W0, Parameter_GetWiperValue(activeGainKnob));
}