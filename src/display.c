#include "display.h"
#include "as1115.h"
#include <stdbool.h>
#include "mcc_generated_files\system\clock.h"

const uint8_t balanceLevels[9][3] = {
    {1, 10, 9}, {2, 10, 8}, {3, 10, 7}, 
    {4, 10, 6}, {5, 10, 5}, {6, 10, 4}, 
    {7, 10, 3}, {8, 10, 2}, {9, 10, 1}
};
static uint8_t lightMap = 0x00;

LEDType LEDBlinkType = LED_NONE;
#define LED_BITS_SIZE 6
static const uint8_t LEDBits[LED_BITS_SIZE] = {
    [LED_INPUT_ONE] = 0x40, // 64
    [LED_INPUT_TWO] = 0x20, // 32
    [LED_INPUT_THREE] = 0x10, // 16
    [LED_INPUT_BT] = 0x08, // 8
    [LED_TONE] = 0x04, // 4
    [LED_NONE] = 0x00 // 0
};
#define INPUT_BITMASK (LEDBits[LED_INPUT_ONE] | LEDBits[LED_INPUT_TWO] | LEDBits[LED_INPUT_THREE] | LEDBits[LED_INPUT_BT])
void DisplaySubEnableDisable(int16_t value)
{
    AS1115_Write(AS1115_REG_DECODE_MODE, 0x0);

    static const uint8_t sub_disable_display[] = {0x5B, 0x30, 0x3D, 0x1F, 0x1C, 0x5B, 0};
    static const uint8_t phase_0_display[]     = {0x7E, 0, 0, 0x5B, 0x77, 0x37, 0x67};
    static const uint8_t phase_180_display[]   = {0x7E, 0x7F, 0x30, 0x5B, 0x77, 0x37, 0x67};

    const uint8_t* selectedDisplay;
    switch (value){
        case 0:
            selectedDisplay = sub_disable_display;
            break;
        case 1:
            selectedDisplay = phase_0_display;
            break;
        case 2:
            selectedDisplay = phase_180_display;
            break;
    }

    AS1115_DisplayDataPartition(selectedDisplay, 7, 0x01);
}
void DisplaySubEQ(int16_t value)
{
    AS1115_Write(AS1115_REG_DECODE_MODE, 0x0);
    static const uint8_t sub_eq_in_display[] = {0x15, 0x30, 0x00, 0xFE, 0x4F, 0x01, 0x5B};
    static const uint8_t sub_eq_out_display[] = {0x0F, 0x1C, 0x7E, 0xFE, 0x4F, 0x01, 0x5B};

    const uint8_t* selectedDisplay;
    switch (value){
        case 0:
            selectedDisplay = sub_eq_in_display;
            break;
        case 1:
            selectedDisplay = sub_eq_out_display;
            break;
    }

    AS1115_DisplayDataPartition(selectedDisplay, 7, 0x01);
}
void DisplaySubLevelRight(int16_t value)
{
    static uint8_t sub_level_display[] = {0x05, 0x0E, 0x01, 0x5B};

    AS1115_Write(AS1115_REG_DECODE_MODE, AS1115_DECODE_DIGIT_0_2);

    AS1115_DisplayPartition(value, 1, 3);

    AS1115_DisplayDataPartition(sub_level_display, 4, 0x04);
}
void DisplaySubLevelLeft(int16_t value)
{
    static uint8_t sub_level_display[] = {0x0E, 0x0E, 0x01, 0x5B};

    AS1115_Write(AS1115_REG_DECODE_MODE, AS1115_DECODE_DIGIT_0_2);

    AS1115_DisplayPartition(value, 1, 3);

    AS1115_DisplayDataPartition(sub_level_display, 4, 0x04);
}
void DisplayOutputGain(int16_t value)
{
    static uint8_t out_l_display[] = {0x0E, 0x0F, 0x1C, 0x1D}; // "outL"
    //                                   L           t         u          o

    AS1115_Write(AS1115_REG_DECODE_MODE, AS1115_DECODE_DIGIT_0_2);

    AS1115_DisplayPartitionDecimal(value, 1, 3);

    AS1115_DisplayDataPartition(out_l_display, 4, 0x04);
}
void DisplayVolume(int16_t value) {
    AS1115_DisplayPartition(value, 1, 3);
}
void DisplayBalance(int16_t value)
{
    AS1115_DisplayDataPartition(balanceLevels[value], 3, 1);
}
void DisplayBoostCut(int16_t value)
{
    bool negative = value < 0;
    AS1115_Write(AS1115_REG_DECODE_MODE, 0x67);  // turn off decode mode to display db on digit 4 and 5
    AS1115_Write(0x04, 0x1F); // d
    AS1115_Write(0x05, 0x3D); // b
    AS1115_DisplayPartition(value, 6, 2);
}
void DisplayFreqLow(int16_t value){
    AS1115_Write(AS1115_REG_DECODE_MODE, 0x77); //decode off on 4 and 8;
    AS1115_Write(0x04, 0x17); //display h;
    AS1115_DisplayPartition(value, 5, 3); 
}
void DisplayFreqHigh(int16_t value) {
    AS1115_Write(AS1115_REG_DECODE_MODE, 0x77); //decode off on 4 and 8;
    AS1115_Write(0x04, 0x37); //display H;
    AS1115_DisplayPartitionDecimal(value, 5, 3);
}
void DisplayQ(int16_t value)
{
    AS1115_Write(AS1115_REG_DECODE_MODE, AS1115_DECODE_DIGIT_0_6); 
    AS1115_DisplayPartition(value, 4, 4); 
}
void DisplayPowerDelayOn(int16_t value)
{
    // --- LEFT SIDE: "On" ---
    // Array reversed for Right-to-Left writing: 'n', 'O'
    static uint8_t on_label[] = {0x15, 0x7E};

    // 1. Set Decode Mode for the Right Side ONLY (Registers 1, 2, 3 -> 0x07)
    AS1115_Write(AS1115_REG_DECODE_MODE, 0x07);

    // 3. Write Number to Right Side
    // Signature: (value, length, start_register)
    AS1115_DisplayPartition(value, 1, 3);

    // 4. Write "On" to Left Side
    // Signature: (data_array, length, start_register)
    AS1115_DisplayDataPartition(on_label, 2, 4);
    
    // (Optional) Clear registers 6 and 7 if needed
    static uint8_t clear_label[] = {0x00, 0x00};
    AS1115_DisplayDataPartition(clear_label, 2, 6);
}

void DisplayPowerDelayOff(int16_t value)
{
    // --- LEFT SIDE: "OFF" ---
    // Reversed: 'F', 'F', 'O'
    static uint8_t off_label[] = {0x47, 0x47, 0x7E};
    
    // --- RIGHT SIDE: "inf" ---
    // Reversed: 'f', 'n', 'i'
    static uint8_t inf_label[] = {0x47, 0x15, 0x10};

    // 1. Write "OFF" to the Left Side starting at Register 4
    AS1115_DisplayDataPartition(off_label, 3, 4);
    
    // (Optional) Clear register 7
    static uint8_t clear_label[] = {0x00};
    AS1115_DisplayDataPartition(clear_label, 1, 7);

    // 2. Handle the Right Side (Numbers or "inf")
    if (value == 100) 
    {
        // DISPLAY "inf"
        AS1115_Write(AS1115_REG_DECODE_MODE, 0x00); 
        
        // Write 'f', 'n', 'i' starting at Register 1
        AS1115_DisplayDataPartition(inf_label, 3, 1);
    }
    else 
    {
        // DISPLAY NUMBERS ("0" to "99")
        AS1115_Write(AS1115_REG_DECODE_MODE, 0x07);
        
        // Write the number starting at Register 1
        AS1115_DisplayPartition(value, 1, 3);
    }
}
void DisplayInputGain(int16_t value)
{
    static uint8_t inp_l_display[] = {0x0E, 0x67, 0x15, 0x30}; // "InpL"
    //                                   L      p      n      I

    AS1115_Write(AS1115_REG_DECODE_MODE, AS1115_DECODE_DIGIT_0_2);
    AS1115_DisplayPartitionDecimal(value, 1, 3);
    AS1115_DisplayDataPartition(inp_l_display, 4, 0x04);
}
void AS1115_DisplayPartitionDecimal(int16_t number, uint8_t startReg, uint8_t numDigits) {
    uint16_t temp;
    bool shouldWriteNegative = false;
    if(number < 0)
    {
        temp = (uint16_t)(number * -1);
        shouldWriteNegative = true;
    }
    else
    {
        temp = (uint16_t)number;
    }

    for (uint8_t i = 0; i < numDigits; i++) {
        // Always display at least 2 digits (e.g., '1.0'), otherwise display if we still have values
        if (i <= 1 || temp > 0) {
            uint8_t displayValue = i == 1 ? (temp % 10) | 0x80 : temp % 10; // add a decimal to the second number
            AS1115_Write(startReg + i, displayValue);
            temp /= 10;
        } else if (shouldWriteNegative)
        {
            AS1115_Write(startReg + i, 0xA);
            shouldWriteNegative = false;
        }
        else {
            // Fill remaining assigned digits with BLANK (0xF in BCD mode)
            AS1115_Write(startReg + i, 0xF); 
        }
    }
}
// Displays a number constrained to a specific section of the 7-segment display
void AS1115_DisplayPartition(int16_t number, uint8_t startReg, uint8_t numDigits) {
    uint16_t temp;
    bool shouldWriteNegative = false;
    if(number < 0)
    {
        temp = (uint16_t)(number * -1);
        shouldWriteNegative = true;
    }
    else
    {
        temp = (uint16_t)number;
    }

    for (uint8_t i = 0; i < numDigits; i++) {
        // Always display at least one digit (e.g., '0'), otherwise display if we still have values
        if (i == 0 || temp > 0) {
            AS1115_Write(startReg + i, temp % 10);
            temp /= 10;
        } else if (shouldWriteNegative)
        {
            AS1115_Write(startReg + i, 0xA);
            shouldWriteNegative = false;
        }
        else
         {
            // Fill remaining assigned digits with BLANK (0xF in BCD mode)
            AS1115_Write(startReg + i, 0xF); 
        }
    }
}

// Writes raw data arrays (like your Balance visualization) to a specific section
void AS1115_DisplayDataPartition(const uint8_t* data, uint8_t len, uint8_t startReg) {
    for(uint8_t i = 0; i < len; i++) {
        AS1115_Write(startReg + i, data[i]); 
    }
}
void Display_WriteLEDs(void) {
    AS1115_Write(0x08, lightMap);
}
void Display_SetToneLED(uint8_t enabled) {
    if (enabled) lightMap |=  LEDBits[LED_TONE];
    else         lightMap &= ~LEDBits[LED_TONE];
    Display_WriteLEDs();
}

void Display_SetInputLED(LEDType ledType) {
    lightMap = (lightMap & ~INPUT_BITMASK) | LEDBits[ledType];
    Display_WriteLEDs();
}

void Display_BlinkLED(void) {
    lightMap ^= LEDBits[LEDBlinkType];
    Display_WriteLEDs();
}

void Display_SetBlinkBitIndex(LEDType ledType)
{
    LEDBlinkType = ledType;
}
void Display_TestButtons(void)
{
    while (true) 
    {
        for (uint8_t bit = 0; bit < 8; bit++) 
        {
            // Calculate the 8-bit value (1, 2, 4, 8, 16, 32, 64, 128)
            uint8_t lightValue = (1 << bit);

            // Option A: Display the bit INDEX (0 through 7)
            AS1115_DisplayPartition(bit, 1, 3);
            
            // Option B: If you prefer to see the raw decimal value (1 to 128), 
            // uncomment the line below and comment out Option A:
            // AS1115_DisplayPartition(lightValue, 1, 3);

            // Write the isolated bit to Register 8
            AS1115_Write(0x08, lightValue);
            __delay_ms(1000);
        }
    }
}

