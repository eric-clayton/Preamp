 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
� [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "as1115.h"
#include "rotoryenc.h"
#include <stdint.h>
#include <math.h>


#define vol_CS_LAT LATAbits.LATA0
#define vol_CS_TRIS TRISAbits.TRISA0

#define DISPLAY_TIMEOUT 4000
/*
    Main application
*/
volatile uint8_t volume_val = 0;
volatile uint8_t balance_val = 0;
volatile uint32_t systemTicks = 0;

void AS1115_DisplayNumber(uint32_t number);
void vol_Write(uint8_t address, uint8_t data);
void AS1115_DisplayData(const uint8_t* data, uint8_t len);
// Initialize your two knobs with different behaviors
Encoder_t volumeKnob = {0, 254, 1, 0, 0, 5, 1};
Encoder_t balanceKnob = {127, 254, 1, 0, 0, 4, 4}; 
Encoder_t* displayEncoder = NULL;
// Corrected 2D array: 9 rows, 3 columns
const uint8_t balanceLevels[9][3] = {
    {1, 10, 9}, {2, 10, 8}, {3, 10, 7}, 
    {4, 10, 6}, {5, 10, 5}, {6, 10, 4}, 
    {7, 10, 3}, {8, 10, 2}, {9, 10, 1}
};
void MyTimerCallback(void) {
    systemTicks++; // Increment every 1ms
}    
void DisplayVolume()
{
   uint8_t displayVol = (uint8_t)roundf((volumeKnob.value / 254.0) * 100);
    //AS1115_DisplayNumber(volumeKnob.value);
   
   AS1115_DisplayNumber(displayVol);
    displayEncoder = &volumeKnob; // Switch state to Volume
}
int main(void) {
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 
    TMR0_Start();
    TMR0_OverflowCallbackRegister(MyTimerCallback);

    // Disable the Global Interrupts 
    // INTERRUPT_GlobalInterruptDisable(); 
    __delay_ms(100);
     AS1115_Init();
     __delay_ms(100);
    AS1115_Write(AS1115_REG_SCAN_LIMIT, AS1115_DISPLAY_DIGITS_0_6); // Enable all digits
    AS1115_Write(AS1115_REG_DECODE_MODE, AS1115_DECODE_DIGIT_0_6); // Set decode on for all digits
    
    AS1115_Write(AS1115_FEATURE, AS1115_DECODE_SEL_CODE_B); // Enable BCD decode first
    
    uint32_t displayTimer = 0;
    DisplayVolume();
    while(1) {
        IO_PLED_LAT = 1;

        // 2. Priority 1: If Volume changes, it always takes over immediately
        if (ROTARYENC_Process(&volumeKnob, IO_VOLA_PORT, IO_VOLB_PORT, &systemTicks)) {
            DisplayVolume();
        } 

        // 3. Priority 2: If Balance changes
        if (ROTARYENC_Process(&balanceKnob, IO_BALA_PORT, IO_BALB_PORT, &systemTicks)) {
            uint8_t balIndex = (uint8_t)roundf((balanceKnob.value / 254.0) * 8);
            AS1115_DisplayData(balanceLevels[balIndex], 3);
            displayEncoder = &balanceKnob; // Switch state to Balance
            displayTimer = systemTicks; 
        }

        // 4. Timeout Logic: If we are currently showing Balance, check the clock
        if (displayEncoder != &volumeKnob) {
            uint32_t timeDelta = systemTicks - displayTimer;

            // If time is up, revert to volume display
            if (timeDelta >= DISPLAY_TIMEOUT) {
                DisplayVolume();
            }
        }
    }
}


// Function to write to Volume pot (address byte + data byte)
void vol_Write(uint8_t address, uint8_t data) {
    vol_CS_LAT = 0; // CS low
    SPI1_ByteExchange(address); // Send register address
    SPI1_ByteExchange(data); // Send data
    vol_CS_LAT = 1; // CS high
}


// Display a number (e.g., 12345678) on 7-segment (BCD mode)
void AS1115_DisplayNumber(uint32_t number) {
        
    uint8_t digits[8] = {0};
    uint8_t dcount = 0;
    uint8_t i = 1;
    uint8_t sz = 1;
    for (i = 1; number > 0; i++) {
        digits[i] = number % 10;
        number /= 10;
        sz = i ;
        dcount++;
    }
    
    for (uint8_t d = 0; d <= i; d++) {
        if (d <= i){
        AS1115_Write(d, digits[d]); // Right-align
        }
        else if(d>=1 && !digits[d] )
        {
            
        AS1115_Write(d, 0x0F);
        }
        
    }
}
void AS1115_DisplayData(const uint8_t* data, uint8_t len) {
    for(uint8_t i = 0; i < len; i++) {
        AS1115_Write(i + 1, data[i]); 
    }
}