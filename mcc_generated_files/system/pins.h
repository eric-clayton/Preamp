/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.1
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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 aliases
#define BALB_TRIS                 TRISAbits.TRISA0
#define BALB_LAT                  LATAbits.LATA0
#define BALB_PORT                 PORTAbits.RA0
#define BALB_WPU                  WPUAbits.WPUA0
#define BALB_OD                   ODCONAbits.ODCA0
#define BALB_ANS                  ANSELAbits.ANSELA0
#define BALB_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define BALB_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define BALB_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define BALB_GetValue()           PORTAbits.RA0
#define BALB_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define BALB_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define BALB_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define BALB_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define BALB_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define BALB_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define BALB_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define BALB_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set RA1 aliases
#define BALA_TRIS                 TRISAbits.TRISA1
#define BALA_LAT                  LATAbits.LATA1
#define BALA_PORT                 PORTAbits.RA1
#define BALA_WPU                  WPUAbits.WPUA1
#define BALA_OD                   ODCONAbits.ODCA1
#define BALA_ANS                  ANSELAbits.ANSELA1
#define BALA_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define BALA_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define BALA_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define BALA_GetValue()           PORTAbits.RA1
#define BALA_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define BALA_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define BALA_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define BALA_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define BALA_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define BALA_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define BALA_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define BALA_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set RA2 aliases
#define VOLCS_TRIS                 TRISAbits.TRISA2
#define VOLCS_LAT                  LATAbits.LATA2
#define VOLCS_PORT                 PORTAbits.RA2
#define VOLCS_WPU                  WPUAbits.WPUA2
#define VOLCS_OD                   ODCONAbits.ODCA2
#define VOLCS_ANS                  ANSELAbits.ANSELA2
#define VOLCS_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define VOLCS_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define VOLCS_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define VOLCS_GetValue()           PORTAbits.RA2
#define VOLCS_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define VOLCS_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define VOLCS_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define VOLCS_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define VOLCS_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define VOLCS_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define VOLCS_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define VOLCS_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set RA3 aliases
#define OGCSL_TRIS                 TRISAbits.TRISA3
#define OGCSL_LAT                  LATAbits.LATA3
#define OGCSL_PORT                 PORTAbits.RA3
#define OGCSL_WPU                  WPUAbits.WPUA3
#define OGCSL_OD                   ODCONAbits.ODCA3
#define OGCSL_ANS                  ANSELAbits.ANSELA3
#define OGCSL_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define OGCSL_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define OGCSL_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define OGCSL_GetValue()           PORTAbits.RA3
#define OGCSL_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define OGCSL_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define OGCSL_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define OGCSL_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define OGCSL_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define OGCSL_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define OGCSL_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define OGCSL_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set RA4 aliases
#define HFBCCS_TRIS                 TRISAbits.TRISA4
#define HFBCCS_LAT                  LATAbits.LATA4
#define HFBCCS_PORT                 PORTAbits.RA4
#define HFBCCS_WPU                  WPUAbits.WPUA4
#define HFBCCS_OD                   ODCONAbits.ODCA4
#define HFBCCS_ANS                  ANSELAbits.ANSELA4
#define HFBCCS_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define HFBCCS_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define HFBCCS_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define HFBCCS_GetValue()           PORTAbits.RA4
#define HFBCCS_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define HFBCCS_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define HFBCCS_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define HFBCCS_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define HFBCCS_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define HFBCCS_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define HFBCCS_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define HFBCCS_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)
#define RA4_SetInterruptHandler  HFBCCS_SetInterruptHandler

// get/set RA5 aliases
#define OGCSR_TRIS                 TRISAbits.TRISA5
#define OGCSR_LAT                  LATAbits.LATA5
#define OGCSR_PORT                 PORTAbits.RA5
#define OGCSR_WPU                  WPUAbits.WPUA5
#define OGCSR_OD                   ODCONAbits.ODCA5
#define OGCSR_ANS                  ANSELAbits.ANSELA5
#define OGCSR_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define OGCSR_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define OGCSR_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define OGCSR_GetValue()           PORTAbits.RA5
#define OGCSR_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define OGCSR_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define OGCSR_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define OGCSR_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define OGCSR_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define OGCSR_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define OGCSR_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define OGCSR_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set RA6 aliases
#define POWER_TRIS                 TRISAbits.TRISA6
#define POWER_LAT                  LATAbits.LATA6
#define POWER_PORT                 PORTAbits.RA6
#define POWER_WPU                  WPUAbits.WPUA6
#define POWER_OD                   ODCONAbits.ODCA6
#define POWER_ANS                  ANSELAbits.ANSELA6
#define POWER_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define POWER_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define POWER_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define POWER_GetValue()           PORTAbits.RA6
#define POWER_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define POWER_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define POWER_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define POWER_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define POWER_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define POWER_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define POWER_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define POWER_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set RA7 aliases
#define O_SRC_TRIS                 TRISAbits.TRISA7
#define O_SRC_LAT                  LATAbits.LATA7
#define O_SRC_PORT                 PORTAbits.RA7
#define O_SRC_WPU                  WPUAbits.WPUA7
#define O_SRC_OD                   ODCONAbits.ODCA7
#define O_SRC_ANS                  ANSELAbits.ANSELA7
#define O_SRC_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define O_SRC_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define O_SRC_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define O_SRC_GetValue()           PORTAbits.RA7
#define O_SRC_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define O_SRC_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define O_SRC_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define O_SRC_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define O_SRC_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define O_SRC_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define O_SRC_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define O_SRC_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set RB0 aliases
#define FREQB_TRIS                 TRISBbits.TRISB0
#define FREQB_LAT                  LATBbits.LATB0
#define FREQB_PORT                 PORTBbits.RB0
#define FREQB_WPU                  WPUBbits.WPUB0
#define FREQB_OD                   ODCONBbits.ODCB0
#define FREQB_ANS                  ANSELBbits.ANSELB0
#define FREQB_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define FREQB_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define FREQB_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define FREQB_GetValue()           PORTBbits.RB0
#define FREQB_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define FREQB_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define FREQB_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define FREQB_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define FREQB_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define FREQB_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define FREQB_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define FREQB_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB1 aliases
#define I2CCLK_TRIS                 TRISBbits.TRISB1
#define I2CCLK_LAT                  LATBbits.LATB1
#define I2CCLK_PORT                 PORTBbits.RB1
#define I2CCLK_WPU                  WPUBbits.WPUB1
#define I2CCLK_OD                   ODCONBbits.ODCB1
#define I2CCLK_ANS                  ANSELBbits.ANSELB1
#define I2CCLK_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define I2CCLK_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define I2CCLK_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define I2CCLK_GetValue()           PORTBbits.RB1
#define I2CCLK_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define I2CCLK_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define I2CCLK_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define I2CCLK_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define I2CCLK_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define I2CCLK_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define I2CCLK_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define I2CCLK_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 aliases
#define I2CDAT_TRIS                 TRISBbits.TRISB2
#define I2CDAT_LAT                  LATBbits.LATB2
#define I2CDAT_PORT                 PORTBbits.RB2
#define I2CDAT_WPU                  WPUBbits.WPUB2
#define I2CDAT_OD                   ODCONBbits.ODCB2
#define I2CDAT_ANS                  ANSELBbits.ANSELB2
#define I2CDAT_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define I2CDAT_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define I2CDAT_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define I2CDAT_GetValue()           PORTBbits.RB2
#define I2CDAT_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define I2CDAT_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define I2CDAT_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define I2CDAT_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define I2CDAT_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define I2CDAT_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define I2CDAT_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define I2CDAT_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set RB3 aliases
#define FREQA_TRIS                 TRISBbits.TRISB3
#define FREQA_LAT                  LATBbits.LATB3
#define FREQA_PORT                 PORTBbits.RB3
#define FREQA_WPU                  WPUBbits.WPUB3
#define FREQA_OD                   ODCONBbits.ODCB3
#define FREQA_ANS                  ANSELBbits.ANSELB3
#define FREQA_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define FREQA_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define FREQA_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define FREQA_GetValue()           PORTBbits.RB3
#define FREQA_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define FREQA_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define FREQA_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define FREQA_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define FREQA_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define FREQA_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define FREQA_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define FREQA_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set RB4 aliases
#define PSW_TRIS                 TRISBbits.TRISB4
#define PSW_LAT                  LATBbits.LATB4
#define PSW_PORT                 PORTBbits.RB4
#define PSW_WPU                  WPUBbits.WPUB4
#define PSW_OD                   ODCONBbits.ODCB4
#define PSW_ANS                  ANSELBbits.ANSELB4
#define PSW_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define PSW_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define PSW_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define PSW_GetValue()           PORTBbits.RB4
#define PSW_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define PSW_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define PSW_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define PSW_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define PSW_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define PSW_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define PSW_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define PSW_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)
#define RB4_SetInterruptHandler  PSW_SetInterruptHandler

// get/set RB5 aliases
#define IRDA_TRIS                 TRISBbits.TRISB5
#define IRDA_LAT                  LATBbits.LATB5
#define IRDA_PORT                 PORTBbits.RB5
#define IRDA_WPU                  WPUBbits.WPUB5
#define IRDA_OD                   ODCONBbits.ODCB5
#define IRDA_ANS                  ANSELBbits.ANSELB5
#define IRDA_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define IRDA_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define IRDA_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define IRDA_GetValue()           PORTBbits.RB5
#define IRDA_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define IRDA_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define IRDA_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define IRDA_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define IRDA_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define IRDA_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define IRDA_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define IRDA_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set RC0 aliases
#define O_RC_TRIS                 TRISCbits.TRISC0
#define O_RC_LAT                  LATCbits.LATC0
#define O_RC_PORT                 PORTCbits.RC0
#define O_RC_WPU                  WPUCbits.WPUC0
#define O_RC_OD                   ODCONCbits.ODCC0
#define O_RC_ANS                  ANSELCbits.ANSELC0
#define O_RC_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define O_RC_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define O_RC_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define O_RC_GetValue()           PORTCbits.RC0
#define O_RC_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define O_RC_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define O_RC_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define O_RC_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define O_RC_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define O_RC_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define O_RC_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define O_RC_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set RC1 aliases
#define SSWCS_TRIS                 TRISCbits.TRISC1
#define SSWCS_LAT                  LATCbits.LATC1
#define SSWCS_PORT                 PORTCbits.RC1
#define SSWCS_WPU                  WPUCbits.WPUC1
#define SSWCS_OD                   ODCONCbits.ODCC1
#define SSWCS_ANS                  ANSELCbits.ANSELC1
#define SSWCS_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define SSWCS_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define SSWCS_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define SSWCS_GetValue()           PORTCbits.RC1
#define SSWCS_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define SSWCS_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define SSWCS_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define SSWCS_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define SSWCS_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define SSWCS_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define SSWCS_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define SSWCS_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set RC2 aliases
#define SCK_TRIS                 TRISCbits.TRISC2
#define SCK_LAT                  LATCbits.LATC2
#define SCK_PORT                 PORTCbits.RC2
#define SCK_WPU                  WPUCbits.WPUC2
#define SCK_OD                   ODCONCbits.ODCC2
#define SCK_ANS                  ANSELCbits.ANSELC2
#define SCK_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SCK_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SCK_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SCK_GetValue()           PORTCbits.RC2
#define SCK_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SCK_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SCK_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define SCK_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define SCK_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define SCK_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define SCK_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define SCK_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 aliases
#define SD2CD_TRIS                 TRISCbits.TRISC3
#define SD2CD_LAT                  LATCbits.LATC3
#define SD2CD_PORT                 PORTCbits.RC3
#define SD2CD_WPU                  WPUCbits.WPUC3
#define SD2CD_OD                   ODCONCbits.ODCC3
#define SD2CD_ANS                  ANSELCbits.ANSELC3
#define SD2CD_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SD2CD_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SD2CD_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SD2CD_GetValue()           PORTCbits.RC3
#define SD2CD_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SD2CD_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SD2CD_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define SD2CD_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define SD2CD_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define SD2CD_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define SD2CD_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define SD2CD_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 aliases
#define SD2MC_TRIS                 TRISCbits.TRISC4
#define SD2MC_LAT                  LATCbits.LATC4
#define SD2MC_PORT                 PORTCbits.RC4
#define SD2MC_WPU                  WPUCbits.WPUC4
#define SD2MC_OD                   ODCONCbits.ODCC4
#define SD2MC_ANS                  ANSELCbits.ANSELC4
#define SD2MC_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SD2MC_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SD2MC_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SD2MC_GetValue()           PORTCbits.RC4
#define SD2MC_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SD2MC_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SD2MC_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define SD2MC_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define SD2MC_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define SD2MC_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define SD2MC_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define SD2MC_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 aliases
#define VOLA_TRIS                 TRISCbits.TRISC5
#define VOLA_LAT                  LATCbits.LATC5
#define VOLA_PORT                 PORTCbits.RC5
#define VOLA_WPU                  WPUCbits.WPUC5
#define VOLA_OD                   ODCONCbits.ODCC5
#define VOLA_ANS                  ANSELCbits.ANSELC5
#define VOLA_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define VOLA_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define VOLA_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define VOLA_GetValue()           PORTCbits.RC5
#define VOLA_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define VOLA_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define VOLA_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define VOLA_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define VOLA_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define VOLA_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define VOLA_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define VOLA_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RC6 aliases
#define VOLB_TRIS                 TRISCbits.TRISC6
#define VOLB_LAT                  LATCbits.LATC6
#define VOLB_PORT                 PORTCbits.RC6
#define VOLB_WPU                  WPUCbits.WPUC6
#define VOLB_OD                   ODCONCbits.ODCC6
#define VOLB_ANS                  ANSELCbits.ANSELC6
#define VOLB_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define VOLB_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define VOLB_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define VOLB_GetValue()           PORTCbits.RC6
#define VOLB_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define VOLB_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define VOLB_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define VOLB_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define VOLB_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define VOLB_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define VOLB_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define VOLB_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RD0 aliases
#define BLED_TRIS                 TRISDbits.TRISD0
#define BLED_LAT                  LATDbits.LATD0
#define BLED_PORT                 PORTDbits.RD0
#define BLED_WPU                  WPUDbits.WPUD0
#define BLED_OD                   ODCONDbits.ODCD0
#define BLED_ANS                  ANSELDbits.ANSELD0
#define BLED_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define BLED_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define BLED_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define BLED_GetValue()           PORTDbits.RD0
#define BLED_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define BLED_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define BLED_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define BLED_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define BLED_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define BLED_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define BLED_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define BLED_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set RD1 aliases
#define IRQ_TRIS                 TRISDbits.TRISD1
#define IRQ_LAT                  LATDbits.LATD1
#define IRQ_PORT                 PORTDbits.RD1
#define IRQ_WPU                  WPUDbits.WPUD1
#define IRQ_OD                   ODCONDbits.ODCD1
#define IRQ_ANS                  ANSELDbits.ANSELD1
#define IRQ_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define IRQ_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define IRQ_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define IRQ_GetValue()           PORTDbits.RD1
#define IRQ_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define IRQ_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define IRQ_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define IRQ_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define IRQ_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define IRQ_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define IRQ_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define IRQ_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set RD2 aliases
#define LFFCS_TRIS                 TRISDbits.TRISD2
#define LFFCS_LAT                  LATDbits.LATD2
#define LFFCS_PORT                 PORTDbits.RD2
#define LFFCS_WPU                  WPUDbits.WPUD2
#define LFFCS_OD                   ODCONDbits.ODCD2
#define LFFCS_ANS                  ANSELDbits.ANSELD2
#define LFFCS_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define LFFCS_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define LFFCS_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define LFFCS_GetValue()           PORTDbits.RD2
#define LFFCS_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define LFFCS_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define LFFCS_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define LFFCS_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define LFFCS_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define LFFCS_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define LFFCS_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define LFFCS_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set RD3 aliases
#define WRCS_TRIS                 TRISDbits.TRISD3
#define WRCS_LAT                  LATDbits.LATD3
#define WRCS_PORT                 PORTDbits.RD3
#define WRCS_WPU                  WPUDbits.WPUD3
#define WRCS_OD                   ODCONDbits.ODCD3
#define WRCS_ANS                  ANSELDbits.ANSELD3
#define WRCS_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define WRCS_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define WRCS_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define WRCS_GetValue()           PORTDbits.RD3
#define WRCS_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define WRCS_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define WRCS_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define WRCS_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define WRCS_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define WRCS_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define WRCS_SetAnalogMode()      do { ANSELDbits.ANSELD3 = 1; } while(0)
#define WRCS_SetDigitalMode()     do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set RD4 aliases
#define QB_TRIS                 TRISDbits.TRISD4
#define QB_LAT                  LATDbits.LATD4
#define QB_PORT                 PORTDbits.RD4
#define QB_WPU                  WPUDbits.WPUD4
#define QB_OD                   ODCONDbits.ODCD4
#define QB_ANS                  ANSELDbits.ANSELD4
#define QB_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define QB_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define QB_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define QB_GetValue()           PORTDbits.RD4
#define QB_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define QB_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define QB_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define QB_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define QB_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define QB_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define QB_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define QB_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set RD5 aliases
#define QA_TRIS                 TRISDbits.TRISD5
#define QA_LAT                  LATDbits.LATD5
#define QA_PORT                 PORTDbits.RD5
#define QA_WPU                  WPUDbits.WPUD5
#define QA_OD                   ODCONDbits.ODCD5
#define QA_ANS                  ANSELDbits.ANSELD5
#define QA_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define QA_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define QA_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define QA_GetValue()           PORTDbits.RD5
#define QA_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define QA_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define QA_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define QA_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define QA_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define QA_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define QA_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define QA_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set RD6 aliases
#define HFA_TRIS                 TRISDbits.TRISD6
#define HFA_LAT                  LATDbits.LATD6
#define HFA_PORT                 PORTDbits.RD6
#define HFA_WPU                  WPUDbits.WPUD6
#define HFA_OD                   ODCONDbits.ODCD6
#define HFA_ANS                  ANSELDbits.ANSELD6
#define HFA_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define HFA_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define HFA_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define HFA_GetValue()           PORTDbits.RD6
#define HFA_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define HFA_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define HFA_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define HFA_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define HFA_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define HFA_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define HFA_SetAnalogMode()      do { ANSELDbits.ANSELD6 = 1; } while(0)
#define HFA_SetDigitalMode()     do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set RD7 aliases
#define HFB_TRIS                 TRISDbits.TRISD7
#define HFB_LAT                  LATDbits.LATD7
#define HFB_PORT                 PORTDbits.RD7
#define HFB_WPU                  WPUDbits.WPUD7
#define HFB_OD                   ODCONDbits.ODCD7
#define HFB_ANS                  ANSELDbits.ANSELD7
#define HFB_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define HFB_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define HFB_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define HFB_GetValue()           PORTDbits.RD7
#define HFB_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define HFB_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define HFB_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define HFB_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define HFB_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define HFB_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define HFB_SetAnalogMode()      do { ANSELDbits.ANSELD7 = 1; } while(0)
#define HFB_SetDigitalMode()     do { ANSELDbits.ANSELD7 = 0; } while(0)

// get/set RE0 aliases
#define LFQCS_TRIS                 TRISEbits.TRISE0
#define LFQCS_LAT                  LATEbits.LATE0
#define LFQCS_PORT                 PORTEbits.RE0
#define LFQCS_WPU                  WPUEbits.WPUE0
#define LFQCS_OD                   ODCONEbits.ODCE0
#define LFQCS_ANS                  ANSELEbits.ANSELE0
#define LFQCS_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define LFQCS_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define LFQCS_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define LFQCS_GetValue()           PORTEbits.RE0
#define LFQCS_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define LFQCS_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define LFQCS_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define LFQCS_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define LFQCS_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define LFQCS_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define LFQCS_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define LFQCS_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set RE1 aliases
#define LFBCCS_TRIS                 TRISEbits.TRISE1
#define LFBCCS_LAT                  LATEbits.LATE1
#define LFBCCS_PORT                 PORTEbits.RE1
#define LFBCCS_WPU                  WPUEbits.WPUE1
#define LFBCCS_OD                   ODCONEbits.ODCE1
#define LFBCCS_ANS                  ANSELEbits.ANSELE1
#define LFBCCS_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define LFBCCS_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define LFBCCS_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define LFBCCS_GetValue()           PORTEbits.RE1
#define LFBCCS_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define LFBCCS_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define LFBCCS_SetPullup()          do { WPUEbits.WPUE1 = 1; } while(0)
#define LFBCCS_ResetPullup()        do { WPUEbits.WPUE1 = 0; } while(0)
#define LFBCCS_SetPushPull()        do { ODCONEbits.ODCE1 = 0; } while(0)
#define LFBCCS_SetOpenDrain()       do { ODCONEbits.ODCE1 = 1; } while(0)
#define LFBCCS_SetAnalogMode()      do { ANSELEbits.ANSELE1 = 1; } while(0)
#define LFBCCS_SetDigitalMode()     do { ANSELEbits.ANSELE1 = 0; } while(0)

// get/set RE2 aliases
#define O_SER_TRIS                 TRISEbits.TRISE2
#define O_SER_LAT                  LATEbits.LATE2
#define O_SER_PORT                 PORTEbits.RE2
#define O_SER_WPU                  WPUEbits.WPUE2
#define O_SER_OD                   ODCONEbits.ODCE2
#define O_SER_ANS                  ANSELEbits.ANSELE2
#define O_SER_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define O_SER_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define O_SER_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define O_SER_GetValue()           PORTEbits.RE2
#define O_SER_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define O_SER_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define O_SER_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define O_SER_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define O_SER_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define O_SER_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define O_SER_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define O_SER_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

// get/set RF0 aliases
#define SLCS_TRIS                 TRISFbits.TRISF0
#define SLCS_LAT                  LATFbits.LATF0
#define SLCS_PORT                 PORTFbits.RF0
#define SLCS_WPU                  WPUFbits.WPUF0
#define SLCS_OD                   ODCONFbits.ODCF0
#define SLCS_ANS                  ANSELFbits.ANSELF0
#define SLCS_SetHigh()            do { LATFbits.LATF0 = 1; } while(0)
#define SLCS_SetLow()             do { LATFbits.LATF0 = 0; } while(0)
#define SLCS_Toggle()             do { LATFbits.LATF0 = ~LATFbits.LATF0; } while(0)
#define SLCS_GetValue()           PORTFbits.RF0
#define SLCS_SetDigitalInput()    do { TRISFbits.TRISF0 = 1; } while(0)
#define SLCS_SetDigitalOutput()   do { TRISFbits.TRISF0 = 0; } while(0)
#define SLCS_SetPullup()          do { WPUFbits.WPUF0 = 1; } while(0)
#define SLCS_ResetPullup()        do { WPUFbits.WPUF0 = 0; } while(0)
#define SLCS_SetPushPull()        do { ODCONFbits.ODCF0 = 0; } while(0)
#define SLCS_SetOpenDrain()       do { ODCONFbits.ODCF0 = 1; } while(0)
#define SLCS_SetAnalogMode()      do { ANSELFbits.ANSELF0 = 1; } while(0)
#define SLCS_SetDigitalMode()     do { ANSELFbits.ANSELF0 = 0; } while(0)

// get/set RF1 aliases
#define HFFCS_TRIS                 TRISFbits.TRISF1
#define HFFCS_LAT                  LATFbits.LATF1
#define HFFCS_PORT                 PORTFbits.RF1
#define HFFCS_WPU                  WPUFbits.WPUF1
#define HFFCS_OD                   ODCONFbits.ODCF1
#define HFFCS_ANS                  ANSELFbits.ANSELF1
#define HFFCS_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define HFFCS_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define HFFCS_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define HFFCS_GetValue()           PORTFbits.RF1
#define HFFCS_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define HFFCS_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define HFFCS_SetPullup()          do { WPUFbits.WPUF1 = 1; } while(0)
#define HFFCS_ResetPullup()        do { WPUFbits.WPUF1 = 0; } while(0)
#define HFFCS_SetPushPull()        do { ODCONFbits.ODCF1 = 0; } while(0)
#define HFFCS_SetOpenDrain()       do { ODCONFbits.ODCF1 = 1; } while(0)
#define HFFCS_SetAnalogMode()      do { ANSELFbits.ANSELF1 = 1; } while(0)
#define HFFCS_SetDigitalMode()     do { ANSELFbits.ANSELF1 = 0; } while(0)

// get/set RF2 aliases
#define IGAINCS_TRIS                 TRISFbits.TRISF2
#define IGAINCS_LAT                  LATFbits.LATF2
#define IGAINCS_PORT                 PORTFbits.RF2
#define IGAINCS_WPU                  WPUFbits.WPUF2
#define IGAINCS_OD                   ODCONFbits.ODCF2
#define IGAINCS_ANS                  ANSELFbits.ANSELF2
#define IGAINCS_SetHigh()            do { LATFbits.LATF2 = 1; } while(0)
#define IGAINCS_SetLow()             do { LATFbits.LATF2 = 0; } while(0)
#define IGAINCS_Toggle()             do { LATFbits.LATF2 = ~LATFbits.LATF2; } while(0)
#define IGAINCS_GetValue()           PORTFbits.RF2
#define IGAINCS_SetDigitalInput()    do { TRISFbits.TRISF2 = 1; } while(0)
#define IGAINCS_SetDigitalOutput()   do { TRISFbits.TRISF2 = 0; } while(0)
#define IGAINCS_SetPullup()          do { WPUFbits.WPUF2 = 1; } while(0)
#define IGAINCS_ResetPullup()        do { WPUFbits.WPUF2 = 0; } while(0)
#define IGAINCS_SetPushPull()        do { ODCONFbits.ODCF2 = 0; } while(0)
#define IGAINCS_SetOpenDrain()       do { ODCONFbits.ODCF2 = 1; } while(0)
#define IGAINCS_SetAnalogMode()      do { ANSELFbits.ANSELF2 = 1; } while(0)
#define IGAINCS_SetDigitalMode()     do { ANSELFbits.ANSELF2 = 0; } while(0)

// get/set RF3 aliases
#define HFQCS_TRIS                 TRISFbits.TRISF3
#define HFQCS_LAT                  LATFbits.LATF3
#define HFQCS_PORT                 PORTFbits.RF3
#define HFQCS_WPU                  WPUFbits.WPUF3
#define HFQCS_OD                   ODCONFbits.ODCF3
#define HFQCS_ANS                  ANSELFbits.ANSELF3
#define HFQCS_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define HFQCS_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define HFQCS_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define HFQCS_GetValue()           PORTFbits.RF3
#define HFQCS_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define HFQCS_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define HFQCS_SetPullup()          do { WPUFbits.WPUF3 = 1; } while(0)
#define HFQCS_ResetPullup()        do { WPUFbits.WPUF3 = 0; } while(0)
#define HFQCS_SetPushPull()        do { ODCONFbits.ODCF3 = 0; } while(0)
#define HFQCS_SetOpenDrain()       do { ODCONFbits.ODCF3 = 1; } while(0)
#define HFQCS_SetAnalogMode()      do { ANSELFbits.ANSELF3 = 1; } while(0)
#define HFQCS_SetDigitalMode()     do { ANSELFbits.ANSELF3 = 0; } while(0)

// get/set RF4 aliases
#define LFB_TRIS                 TRISFbits.TRISF4
#define LFB_LAT                  LATFbits.LATF4
#define LFB_PORT                 PORTFbits.RF4
#define LFB_WPU                  WPUFbits.WPUF4
#define LFB_OD                   ODCONFbits.ODCF4
#define LFB_ANS                  ANSELFbits.ANSELF4
#define LFB_SetHigh()            do { LATFbits.LATF4 = 1; } while(0)
#define LFB_SetLow()             do { LATFbits.LATF4 = 0; } while(0)
#define LFB_Toggle()             do { LATFbits.LATF4 = ~LATFbits.LATF4; } while(0)
#define LFB_GetValue()           PORTFbits.RF4
#define LFB_SetDigitalInput()    do { TRISFbits.TRISF4 = 1; } while(0)
#define LFB_SetDigitalOutput()   do { TRISFbits.TRISF4 = 0; } while(0)
#define LFB_SetPullup()          do { WPUFbits.WPUF4 = 1; } while(0)
#define LFB_ResetPullup()        do { WPUFbits.WPUF4 = 0; } while(0)
#define LFB_SetPushPull()        do { ODCONFbits.ODCF4 = 0; } while(0)
#define LFB_SetOpenDrain()       do { ODCONFbits.ODCF4 = 1; } while(0)
#define LFB_SetAnalogMode()      do { ANSELFbits.ANSELF4 = 1; } while(0)
#define LFB_SetDigitalMode()     do { ANSELFbits.ANSELF4 = 0; } while(0)

// get/set RF5 aliases
#define LFA_TRIS                 TRISFbits.TRISF5
#define LFA_LAT                  LATFbits.LATF5
#define LFA_PORT                 PORTFbits.RF5
#define LFA_WPU                  WPUFbits.WPUF5
#define LFA_OD                   ODCONFbits.ODCF5
#define LFA_ANS                  ANSELFbits.ANSELF5
#define LFA_SetHigh()            do { LATFbits.LATF5 = 1; } while(0)
#define LFA_SetLow()             do { LATFbits.LATF5 = 0; } while(0)
#define LFA_Toggle()             do { LATFbits.LATF5 = ~LATFbits.LATF5; } while(0)
#define LFA_GetValue()           PORTFbits.RF5
#define LFA_SetDigitalInput()    do { TRISFbits.TRISF5 = 1; } while(0)
#define LFA_SetDigitalOutput()   do { TRISFbits.TRISF5 = 0; } while(0)
#define LFA_SetPullup()          do { WPUFbits.WPUF5 = 1; } while(0)
#define LFA_ResetPullup()        do { WPUFbits.WPUF5 = 0; } while(0)
#define LFA_SetPushPull()        do { ODCONFbits.ODCF5 = 0; } while(0)
#define LFA_SetOpenDrain()       do { ODCONFbits.ODCF5 = 1; } while(0)
#define LFA_SetAnalogMode()      do { ANSELFbits.ANSELF5 = 1; } while(0)
#define LFA_SetDigitalMode()     do { ANSELFbits.ANSELF5 = 0; } while(0)

// get/set RF6 aliases
#define PLED_TRIS                 TRISFbits.TRISF6
#define PLED_LAT                  LATFbits.LATF6
#define PLED_PORT                 PORTFbits.RF6
#define PLED_WPU                  WPUFbits.WPUF6
#define PLED_OD                   ODCONFbits.ODCF6
#define PLED_ANS                  ANSELFbits.ANSELF6
#define PLED_SetHigh()            do { LATFbits.LATF6 = 1; } while(0)
#define PLED_SetLow()             do { LATFbits.LATF6 = 0; } while(0)
#define PLED_Toggle()             do { LATFbits.LATF6 = ~LATFbits.LATF6; } while(0)
#define PLED_GetValue()           PORTFbits.RF6
#define PLED_SetDigitalInput()    do { TRISFbits.TRISF6 = 1; } while(0)
#define PLED_SetDigitalOutput()   do { TRISFbits.TRISF6 = 0; } while(0)
#define PLED_SetPullup()          do { WPUFbits.WPUF6 = 1; } while(0)
#define PLED_ResetPullup()        do { WPUFbits.WPUF6 = 0; } while(0)
#define PLED_SetPushPull()        do { ODCONFbits.ODCF6 = 0; } while(0)
#define PLED_SetOpenDrain()       do { ODCONFbits.ODCF6 = 1; } while(0)
#define PLED_SetAnalogMode()      do { ANSELFbits.ANSELF6 = 1; } while(0)
#define PLED_SetDigitalMode()     do { ANSELFbits.ANSELF6 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the HFBCCS pin functionality
 * @param none
 * @return none
 */
void HFBCCS_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for HFBCCS pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for HFBCCS at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void HFBCCS_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for HFBCCS pin.
 *        This is a dynamic interrupt handler to be used together with the HFBCCS_SetInterruptHandler() method.
 *        This handler is called every time the HFBCCS ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*HFBCCS_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for HFBCCS pin. 
 *        This is a predefined interrupt handler to be used together with the HFBCCS_SetInterruptHandler() method.
 *        This handler is called every time the HFBCCS ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void HFBCCS_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the PSW pin functionality
 * @param none
 * @return none
 */
void PSW_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PSW pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for PSW at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void PSW_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for PSW pin.
 *        This is a dynamic interrupt handler to be used together with the PSW_SetInterruptHandler() method.
 *        This handler is called every time the PSW ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*PSW_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PSW pin. 
 *        This is a predefined interrupt handler to be used together with the PSW_SetInterruptHandler() method.
 *        This handler is called every time the PSW ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void PSW_DefaultInterruptHandler(void);


#endif // PINS_H
/**
 End of File
*/