/**
 * CCP3 Generated Driver API Header File.
 * 
 * @file ccp3.h
 * 
 * @defgroup capture3 CAPTURE3
 * 
 * @brief This file contains the API prototypes and other data types for the CCP3 module.
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

#ifndef CCP3_H
#define CCP3_H

 /**
   Section: Included Files
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>


/** 
   Section: Data Type Definition
*/

/**
 * @ingroup capture3
 * @union CCPR3_PERIOD_REG_T
 * @brief Custom data type to hold the low byte, high byte, and 16-bit values of the period register.
 */
 /**
 * @misradeviation{@advisory,19.2}
 * The CCP register values necessitates to store and accessing the register values within the group byte therefore the use of a union is essential.
 */
 /* cppcheck-suppress misra-c2012-19.2 */
typedef union CCPR3Reg_tag
{
   struct
   {
      uint8_t ccpr3l; /**< CCPR3L low byte.*/
      uint8_t ccpr3h; /**< CCPR3H high byte.*/
   };
   struct
   {
      uint16_t ccpr3_16Bit; /**< CCPR3 16-bit.*/
   };
} CCPR3_PERIOD_REG_T ;

/**
  Section: CCP3 Capture Module APIs
*/

/**
 * @ingroup capture3
 * @brief Initializes the CCP3 module. This is called only once before calling other CCP3 APIs.
 * @param None.
 * @return None.
 */
void CCP3_Initialize(void);

/**
 * @ingroup capture3
 * @brief Implements the Interrupt Service Routine (ISR) for the capture interrupt.
 * @param None.
 * @return None.
 */
void CCP3_CaptureISR(void);

/**
 * @ingroup capture3
 * @brief Assigns a callback function that will be called from the Capture ISR when a capture interrupt event occurs.
 * @param (*customCallBack)(uint16_t) - Function pointer to the new callback.
 * @return None.
 */
void CCP3_SetCallBack(void (*customCallBack)(uint16_t));

#endif // CCP3_H
/**
 End of File
*/