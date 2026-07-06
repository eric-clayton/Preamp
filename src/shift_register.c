#include "shift_register.h"
#include "cs_device.h"
#include "mcc_generated_files/spi/spi1.h"
#include "mcc_generated_files\system\pins.h"
#include "mcc_generated_files/system/clock.h"

const switch_condition_t SUB_EQ_ENA      = { S1AB|S2AB|S3AB|S4AB, S1AB|S4AB };
const switch_condition_t SUB_EQ_DIS      = { S1AB|S2AB|S3AB|S4AB, S2AB|S3AB };
const switch_condition_t PHASE_180       = { S5AB|S6AB,           S6AB };
const switch_condition_t PHASE_0         = { S5AB|S6AB,           S5AB };
const switch_condition_t PHASE_CORRECT   = { S7AB,                0 };
const switch_condition_t PHASE_INCORRECT = { S7AB,                S7AB };
const switch_condition_t SUB_MUTE        = { S8AB,                0 };
const switch_condition_t SUB_UNMUTE      = { S8AB,                S8AB };

uint16_t hc595_shadow = 0;
uint16_t sswcs_shadow = 0;

static inline void O_RCSetLow(void)    { O_RC_SetLow();  }
static inline void O_RCSetHigh(void)   { O_RC_SetHigh(); }
static inline void SSWCSSetLow(void)   { SSWCS_SetLow();  }
static inline void SSWCSSetHigh(void)  { SSWCS_SetHigh(); }

static const CS_Device_t outputExpanderCS = { O_RCSetLow, O_RCSetHigh };
static const CS_Device_t subSwitchCS      = { SSWCSSetLow, SSWCSSetHigh };

void apply_bits(uint16_t *shadow, uint16_t mask, uint16_t value)
{
    *shadow = (*shadow & ~mask) | (value & mask);
}
void WriteRegister(void)
{
    uint8_t txBuffer[2];

    // Note: if your physical PCB wiring expects the low byte first, swap these indices.
    txBuffer[0] = (uint8_t)(hc595_shadow >> 8);    // MSB (second chip in chain)
    txBuffer[1] = (uint8_t)(hc595_shadow & 0xFF);  // LSB (first chip in chain)

    SPI1_Host.Open(HOST_CONFIG);
    outputExpanderCS.csLow();
    SPI1_Host.BufferWrite(txBuffer, 2);
    outputExpanderCS.csHigh(); // latch pulse -- applies shifted bits to physical pins
    SPI1_Host.Close();
}

void WriteRegisterAnalog(void)
{
    uint8_t txBuffer[2];

    txBuffer[0] = (uint8_t)(sswcs_shadow >> 8);
    txBuffer[1] = (uint8_t)(sswcs_shadow & 0xFF);

    SPI1_Host.Open(HOST_CONFIG);
    subSwitchCS.csLow();
    SPI1_Host.BufferWrite(txBuffer, 2);
    subSwitchCS.csHigh(); // latch pulse
    SPI1_Host.Close();
}
void SetExpanderRegister(uint16_t bitMask, uint8_t value)
{
    apply_bits(&hc595_shadow, bitMask, value ? bitMask : 0);
    WriteRegister();
}

void ToggleExpanderRegister(uint16_t bitMask)
{
    hc595_shadow ^= bitMask;
    WriteRegister();
}

