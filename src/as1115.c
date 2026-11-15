/*
 * File:   as1115.c
 * Author: david
 *
 * Created on January 31, 2026, 11:47 AM
 */


#include <xc.h>
#include <stddef.h>
#include "as1115.h"
#include "mcc_generated_files\i2c_host\i2c2.h"
#include "mcc_generated_files/system/clock.h"

volatile uint8_t failedWrites = 0;

static bool WaitForBusy(void)
{
    uint16_t safety = 1000;
    while(I2C2_IsBusy() && safety > 0) {
        safety--;
        __delay_us(10);
    }
    return !I2C2_IsBusy();
}
void AS1115_Init() {
    AS1115_Write(AS1115_REG_SCAN_LIMIT, AS1115_DISPLAY_DIGITS_0_7);
    AS1115_Write(AS1115_REG_DECODE_MODE, AS1115_DECODE_DIGIT_0_6); // BCD on all digits
    AS1115_Write(AS1115_REG_SET_GLOBAL_INTENSITY, AS1115_INTENSITY_8_16);
    __delay_ms(200);
}

// Send I2C Commands
void AS1115_Write(uint8_t reg, uint8_t data) {
    static uint8_t buffer[2];

    buffer[0] = reg;
    buffer[1] = data;

    if (!WaitForBusy()) {
        failedWrites++;
        return;
    }

    I2C2_ErrorGet();
    if (!I2C2_Write(AS1115_I2C_ADDRESS, buffer, 2)) {
        failedWrites++;
        return;
    }
    if (!WaitForBusy() || I2C2_ErrorGet() != I2C_ERROR_NONE)
        failedWrites++;
}
bool AS1115_ReadKeys(uint8_t *buffer) {
    static uint8_t regAddr;
    static uint8_t keyData[2];

    if (buffer == NULL || !WaitForBusy()) return false;

    regAddr = AS1115_REG_KEYA;
    I2C2_ErrorGet();
    if (!I2C2_WriteRead(AS1115_I2C_ADDRESS, &regAddr, 1, keyData, sizeof(keyData)))
        return false;
    if (!WaitForBusy() || I2C2_ErrorGet() != I2C_ERROR_NONE)
        return false;

    buffer[0] = keyData[0];
    buffer[1] = keyData[1];
    return true;
}
