/*
 * File:   as1115.c
 * Author: david
 *
 * Created on January 31, 2026, 11:47 AM
 */


#include <xc.h>
#include "as1115.h"
#include "mcc_generated_files\i2c_host\i2c2.h"
#include "mcc_generated_files/system/clock.h"

void WaitForBusy()
{
    // 2. Simple Wait (Don't use WaitForBusy here if it contains Reset logic)
    uint16_t safety = 1000;
    while(I2C2_IsBusy() && safety > 0) {
        safety--;
        __delay_us(10);
    }
    return;
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

    WaitForBusy();
    
    I2C2_Write(AS1115_I2C_ADDRESS, buffer, 2);

    uint8_t dummy[2];
    AS1115_ReadKeys(dummy);
}
void AS1115_ReadKeys(uint8_t *buffer) {
    uint8_t regAddr = 0x1C; // KEYA

    WaitForBusy();

    I2C2_Write(AS1115_I2C_ADDRESS, &regAddr, 1);
    
    WaitForBusy();

    I2C2_Read(AS1115_I2C_ADDRESS, buffer, 2);
    
    WaitForBusy(); 
}



