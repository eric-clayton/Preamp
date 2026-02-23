/*
 * File:   as1115.c
 * Author: david
 *
 * Created on January 31, 2026, 11:47 AM
 */


#include <xc.h>

//void main(void) {
//    return;
//}


#include "as1115.h"


// I2C Function Implementations


// Function to initialize the AS1115 display
void AS1115_Init() {
    AS1115_Write(AS1115_REG_SHUTDOWN, AS1115_NORMAL_OP_RESET_FEATURE);// Turn on with default features
    AS1115_Write(AS1115_REG_SCAN_LIMIT, AS1115_DISPLAY_DIGITS_0); // Enable all digits
    AS1115_Write(AS1115_REG_DECODE_MODE, AS1115_DECODE_DIGIT_0); // Set decode on for all digits
    AS1115_Write(AS1115_REG_SET_GLOBAL_INTENSITY, AS1115_INTENSITY_8_16); // Set global medium brightness
    //AS1115_Write(AS1115_REG_DISPLAY_TEST_MODE, 1);
  __delay_ms(200);
}

// Send I2C Commands
void AS1115_Write(uint8_t reg, uint8_t data) {
    uint8_t buffer[2] = {reg, data};
    I2C1_Write(AS1115_I2C_ADDRESS, buffer, 2);
    __delay_ms(50);
}
void AS1115_Read(uint8_t *buffer) {
    I2C1_Read(AS1115_I2C_ADDRESS, buffer, 2);
    __delay_ms(50);
}
uint8_t AS1115_Read_Reg(uint8_t reg) {
    uint8_t val = 0;
    I2C1_Write(AS1115_I2C_ADDRESS, &reg, 1); // Point to register
    I2C1_Read(AS1115_I2C_ADDRESS, &val, 1);  // Read the value
    return val;
}
//Function to write a string to OLED, passed string
//void AS1115_WriteString(char *characters)
//{
//  while (*characters) AS1115_WriteCharacter(*characters++);
//}

//Function to write a character, passed character
//void AS1115_WriteCharacter(char character)
//{
//  for (int i=0; i<5; i++) AS1115_SendData((ASCII[character - 0x20][i]));
//  AS1115_SendData(0x00);
//}

//Function to clear OLED screen.
//void AS1115_Clear()
//{
//    AS1115_SelectPage(0);  
//    int i =0;
//    // AS1115_CLEAR_SIZE  = 1024  for 128*64
//    for (i; i<AS1115_CLEAR_SIZE ; i++) 
//    {
//      AS1115_SendData(0x00); // clear oled screen  
//    }
//}



