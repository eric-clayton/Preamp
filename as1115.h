/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

/* This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
*/


// This is a guard condition so that contents of this file are not included
// more than once.  

#ifndef AS1115_H
#define AS1115_H

#include "mcc_generated_files/system/system.h"
#include <string.h>
#include <xc.h> // include processor files - each processor file is guarded. 
//#include "font.h"

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#define SUCCESS 1
    
//AS1115 128x64 Definition
#define AS1115_I2C_ADDRESS 0x0000    

// Digit Register
#define DIGIT_0                                       0x01
#define DIGIT_1                                       0x02
#define DIGIT_2                                       0x03
#define DIGIT_3                                       0x04
#define DIGIT_4                                       0x05
#define DIGIT_5                                       0x06
#define DIGIT_6                                       0x07
#define DIGIT_7                                       0x08

// Control Register
#define AS1115_REG_DECODE_MODE                             0x09
#define AS1115_REG_SET_GLOBAL_INTENSITY                    0x0A
#define AS1115_REG_SCAN_LIMIT                              0x0B
#define AS1115_REG_SHUTDOWN                                0x0C
#define AS1115_REG_SELF_ADDRESSING                         0x0D
#define AS1115_REG_FEATURE                                 0x0E
#define AS1115_REG_DISPLAY_TEST_MODE                       0x0F
#define AS1115_REG_DIG0_DIG1_INTENSITY                     0x10
#define AS1115_REG_DIG2_DIG3_INTENSITY                     0x11
#define AS1115_REG_DIG4_DIG5_INTENSITY                     0x12
#define AS1115_REG_DIG6_DIG7_INTENSITY                     0x13

// Keyscan/Diagnostic Register
#define AS1115_REG_DIAGNOSTIC_DIGIT_0                      0x14
#define AS1115_REG_DIAGNOSTIC_DIGIT_1                      0x15
#define AS1115_REG_DIAGNOSTIC_DIGIT_2                      0x16
#define AS1115_REG_DIAGNOSTIC_DIGIT_3                      0x17
#define AS1115_REG_DIAGNOSTIC_DIGIT_4                      0x18
#define AS1115_REG_DIAGNOSTIC_DIGIT_5                      0x19
#define AS1115_REG_DIAGNOSTIC_DIGIT_6                      0x1A
#define AS1115_REG_DIAGNOSTIC_DIGIT_7                      0x1B
#define AS1115_REG_KEYA                                    0x1C
#define AS1115_REG_KEYB                                    0xD1

// Feature Register
#define AS1115_FEATURE                                     0x0E

// Feature Register Bit Descriptions   
#define AS1115_REG_RESET_DISABLED                          0x00
#define AS1115_REG_RESET_DEFAULT                           0x02
#define AS1115_DECODE_SEL_CODE_B                           0x00
#define AS1115_DECODE_SEL_HEX                              0x04
    
// Shutdown controls
#define AS1115_SHUTDOWN_RESET_FEATURE                      0x00
#define AS1115_SHUTDOWN                                    0x80
#define AS1115_NORMAL_OP_RESET_FEATURE                     0x01
#define AS1115_NORMAL_OP                                   0x81

// Decode Mode    
#define AS1115_NO_DECODE                                   0x00
#define AS1115_DECODE_DIGIT_0                              0x01
#define AS1115_DECODE_DIGIT_0_1                            0x03
#define AS1115_DECODE_DIGIT_0_2                            0x07
#define AS1115_DECODE_DIGIT_0_3                            0x0F
#define AS1115_DECODE_DIGIT_0_4                            0x1F
#define AS1115_DECODE_DIGIT_0_5                            0x3F
#define AS1115_DECODE_DIGIT_0_6                            0x7F
#define AS1115_DECODE_DIGIT_0_7                            0xFF
    
// Intensity duty cycles
#define AS1115_INTENSITY_1_16      0x00  // Minimum brightness
#define AS1115_INTENSITY_2_16      0x01
#define AS1115_INTENSITY_3_16      0x02
#define AS1115_INTENSITY_4_16      0x03
#define AS1115_INTENSITY_5_16      0x04
#define AS1115_INTENSITY_6_16      0x05
#define AS1115_INTENSITY_7_16      0x06
#define AS1115_INTENSITY_8_16      0x07  // Mid-point
#define AS1115_INTENSITY_9_16      0x08
#define AS1115_INTENSITY_10_16     0x09
#define AS1115_INTENSITY_11_16     0x0A
#define AS1115_INTENSITY_12_16     0x0B
#define AS1115_INTENSITY_13_16     0x0C
#define AS1115_INTENSITY_14_16     0x0D
#define AS1115_INTENSITY_15_16     0x0E
#define AS1115_INTENSITY_16_16     0x0F  // Maximum brightness
    
// Scan Limit
#define AS1115_DISPLAY_DIGITS_0                            0x00
#define AS1115_DISPLAY_DIGITS_0_1                          0x01
#define AS1115_DISPLAY_DIGITS_0_2                          0x02
#define AS1115_DISPLAY_DIGITS_0_3                          0x03
#define AS1115_DISPLAY_DIGITS_0_4                          0x04
#define AS1115_DISPLAY_DIGITS_0_5                          0x05
#define AS1115_DISPLAY_DIGITS_0_6                          0x06
#define AS1115_DISPLAY_DIGITS_0_7                          0x07

    
void AS1115_Write(uint8_t reg, uint8_t data);
void AS1115_Init();
uint8_t AS1115_Read_Reg(uint8_t reg);
//void AS1115_WriteString(char *characters);
//void AS1115_WriteCharacter(char character);
//void AS1115_Clear();
//void AS1115_ClearLine(uint8_t page_num);
//void AS1115_SelectPage(uint8_t page_num);
//const uint8_t* GetFontCharacter(uint8_t character);
//void AS1115_DrawBitmap(const uint8_t* bitmap);


#ifdef	__cplusplus
}
#endif /* __cplusplus */



#endif //AS1115_H