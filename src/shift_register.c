#include "shift_register.h"
#include "cs_device.h"
#include "mcc_generated_files/spi/spi1.h"
#include "mcc_generated_files\system\pins.h"
#include "mcc_generated_files/system/clock.h"

uint16_t hc595_shadow = 0;
uint16_t led595_shadow = 0;
static uint8_t ledBlank = 0;

static inline void O595CSSetLow(void)    { O595CS_SetLow();  }
static inline void O595CSSetHigh(void)   { O595CS_SetHigh(); }
static inline void LED595CSSetLow(void)  { LED595CS_SetLow();  }
static inline void LED595CSSetHigh(void) { LED595CS_SetHigh(); }

static const CS_Device_t outputExpanderCS = { O595CSSetLow, O595CSSetHigh };
static const CS_Device_t ledExpanderCS = { LED595CSSetLow, LED595CSSetHigh };

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
    SPI1_Host.BufferExchange(txBuffer, 2);
    outputExpanderCS.csHigh(); // latch pulse -- applies shifted bits to physical pins
    SPI1_Host.Close();
}

void WriteRegisterLED(void)
{
    uint8_t txBuffer[2];

    txBuffer[0] = (uint8_t)(led595_shadow >> 8);
    txBuffer[1] = (uint8_t)(led595_shadow & 0xFF);

    SPI1_Host.Open(HOST_CONFIG);
    ledExpanderCS.csLow();
    SPI1_Host.BufferExchange(txBuffer, 2);
    ledExpanderCS.csHigh(); // latch pulse
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

void SetExpanderBits(uint16_t mask, uint16_t bits)
{
    apply_bits(&hc595_shadow, mask, bits);
    WriteRegister();
}

void SetLEDRegister(uint16_t bitMask, uint8_t value)
{
    apply_bits(&led595_shadow, bitMask, value ? bitMask : 0);
    WriteRegisterLED();
}

void ToggleLEDRegister(uint16_t bitMask)
{
    led595_shadow ^= bitMask;
    WriteRegisterLED();
}

void SetLEDBits(uint16_t mask, uint16_t bits)
{
    apply_bits(&led595_shadow, mask, bits);
    WriteRegisterLED();
}
