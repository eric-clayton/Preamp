/**
 * CCP3 Generated Driver File.
 * 
 * @file ccp3.c
 * 
 * @ingroup capture3
 * 
 * @brief This file contains the API implementation for the CCP3 driver.
 *
 * @version CCP3 Driver Version 2.0.4
*/
/*
© [2026] Microchip Technology Inc. and its subsidiaries.

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

 /**
   Section: Included Files
 */

#include <xc.h>
#include "../ccp3.h"

static void (*CCP3_CallBack)(uint16_t);

/**
  Section: Capture Module APIs
*/

/**
 * @ingroup capture3
 * @brief Default callback function for the capture interrupt events.
 * @param capturedValue - 16-bit captured value.
 * @return None.
 */
/* cppcheck-suppress misra-c2012-2.7 */
static void CCP3_DefaultCallBack(uint16_t capturedValue) {
    // Add your code here
}

void CCP3_Initialize(void)
{

    // CTS CCP3 pin; 
    CCP3CAP = (uint8_t) 0x0U;

    // CCPRH 0; 
    CCPR3H = (uint8_t) 0x0U;

    // CCPRL 0; 
    CCPR3L = (uint8_t)(0x0U);
    
    

    // Set the default call back function for CCP3
    CCP3_SetCallBack(CCP3_DefaultCallBack);

    // Selecting Timer 1
    CCPTMRS0bits.C3TSEL = 0x1U;

    // Clear the CCP3 interrupt flag    
    PIR9bits.CCP3IF = 0U;    

    // Enable the CCP3 interrupt
    PIE9bits.CCP3IE = 1U;
    
    // CCPM Falling edge; EN enabled; FMT right_aligned; 
    CCP3CON = (uint8_t) 0x84U;
}

void CCP3_CaptureISR(void)
{
/**
 * @misradeviation{@advisory,19.2}
 * The CCP register values necessitates to store and accessing the register values within the group byte therefore the use of a union is essential.
 */
 /* cppcheck-suppress misra-c2012-19.2 */
    CCPR3_PERIOD_REG_T module;

    // Clear the CCP3 interrupt flag
    PIR9bits.CCP3IF = 0U;
    
    // Copy captured value.
    module.ccpr3l = CCPR3L;
    module.ccpr3h = CCPR3H;
    
    // Return 16-bit captured value
    CCP3_CallBack(module.ccpr3_16Bit);
}

void CCP3_SetCallBack(void (*customCallBack)(uint16_t)){
    CCP3_CallBack = customCallBack;
}
/**
 End of File
*/
