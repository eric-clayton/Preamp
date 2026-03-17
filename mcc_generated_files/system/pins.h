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
#define IO_VOLCS_TRIS                 TRISAbits.TRISA0
#define IO_VOLCS_LAT                  LATAbits.LATA0
#define IO_VOLCS_PORT                 PORTAbits.RA0
#define IO_VOLCS_WPU                  WPUAbits.WPUA0
#define IO_VOLCS_OD                   ODCONAbits.ODCA0
#define IO_VOLCS_ANS                  ANSELAbits.ANSELA0
#define IO_VOLCS_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define IO_VOLCS_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define IO_VOLCS_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define IO_VOLCS_GetValue()           PORTAbits.RA0
#define IO_VOLCS_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define IO_VOLCS_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define IO_VOLCS_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define IO_VOLCS_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define IO_VOLCS_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define IO_VOLCS_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define IO_VOLCS_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define IO_VOLCS_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set RA1 aliases
#define IO_HFBCS_TRIS                 TRISAbits.TRISA1
#define IO_HFBCS_LAT                  LATAbits.LATA1
#define IO_HFBCS_PORT                 PORTAbits.RA1
#define IO_HFBCS_WPU                  WPUAbits.WPUA1
#define IO_HFBCS_OD                   ODCONAbits.ODCA1
#define IO_HFBCS_ANS                  ANSELAbits.ANSELA1
#define IO_HFBCS_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define IO_HFBCS_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define IO_HFBCS_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define IO_HFBCS_GetValue()           PORTAbits.RA1
#define IO_HFBCS_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define IO_HFBCS_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define IO_HFBCS_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define IO_HFBCS_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define IO_HFBCS_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define IO_HFBCS_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define IO_HFBCS_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define IO_HFBCS_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set RA2 aliases
#define IO_LFBCS_TRIS                 TRISAbits.TRISA2
#define IO_LFBCS_LAT                  LATAbits.LATA2
#define IO_LFBCS_PORT                 PORTAbits.RA2
#define IO_LFBCS_WPU                  WPUAbits.WPUA2
#define IO_LFBCS_OD                   ODCONAbits.ODCA2
#define IO_LFBCS_ANS                  ANSELAbits.ANSELA2
#define IO_LFBCS_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define IO_LFBCS_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define IO_LFBCS_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define IO_LFBCS_GetValue()           PORTAbits.RA2
#define IO_LFBCS_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define IO_LFBCS_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define IO_LFBCS_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define IO_LFBCS_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define IO_LFBCS_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define IO_LFBCS_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define IO_LFBCS_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define IO_LFBCS_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set RA3 aliases
#define IO_RSET_TRIS                 TRISAbits.TRISA3
#define IO_RSET_LAT                  LATAbits.LATA3
#define IO_RSET_PORT                 PORTAbits.RA3
#define IO_RSET_WPU                  WPUAbits.WPUA3
#define IO_RSET_OD                   ODCONAbits.ODCA3
#define IO_RSET_ANS                  ANSELAbits.ANSELA3
#define IO_RSET_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define IO_RSET_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define IO_RSET_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define IO_RSET_GetValue()           PORTAbits.RA3
#define IO_RSET_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define IO_RSET_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define IO_RSET_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define IO_RSET_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define IO_RSET_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define IO_RSET_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define IO_RSET_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define IO_RSET_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set RA5 aliases
#define IO_SUBEN_TRIS                 TRISAbits.TRISA5
#define IO_SUBEN_LAT                  LATAbits.LATA5
#define IO_SUBEN_PORT                 PORTAbits.RA5
#define IO_SUBEN_WPU                  WPUAbits.WPUA5
#define IO_SUBEN_OD                   ODCONAbits.ODCA5
#define IO_SUBEN_ANS                  ANSELAbits.ANSELA5
#define IO_SUBEN_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define IO_SUBEN_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define IO_SUBEN_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define IO_SUBEN_GetValue()           PORTAbits.RA5
#define IO_SUBEN_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define IO_SUBEN_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define IO_SUBEN_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define IO_SUBEN_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define IO_SUBEN_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define IO_SUBEN_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define IO_SUBEN_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define IO_SUBEN_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set RA7 aliases
#define IO_POWER_TRIS                 TRISAbits.TRISA7
#define IO_POWER_LAT                  LATAbits.LATA7
#define IO_POWER_PORT                 PORTAbits.RA7
#define IO_POWER_WPU                  WPUAbits.WPUA7
#define IO_POWER_OD                   ODCONAbits.ODCA7
#define IO_POWER_ANS                  ANSELAbits.ANSELA7
#define IO_POWER_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define IO_POWER_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define IO_POWER_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define IO_POWER_GetValue()           PORTAbits.RA7
#define IO_POWER_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define IO_POWER_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define IO_POWER_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define IO_POWER_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define IO_POWER_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define IO_POWER_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define IO_POWER_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define IO_POWER_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set RB0 aliases
#define IO_FREQB_TRIS                 TRISBbits.TRISB0
#define IO_FREQB_LAT                  LATBbits.LATB0
#define IO_FREQB_PORT                 PORTBbits.RB0
#define IO_FREQB_WPU                  WPUBbits.WPUB0
#define IO_FREQB_OD                   ODCONBbits.ODCB0
#define IO_FREQB_ANS                  ANSELBbits.ANSELB0
#define IO_FREQB_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define IO_FREQB_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define IO_FREQB_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define IO_FREQB_GetValue()           PORTBbits.RB0
#define IO_FREQB_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define IO_FREQB_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define IO_FREQB_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define IO_FREQB_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define IO_FREQB_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define IO_FREQB_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define IO_FREQB_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define IO_FREQB_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB1 aliases
#define IO_RB1_TRIS                 TRISBbits.TRISB1
#define IO_RB1_LAT                  LATBbits.LATB1
#define IO_RB1_PORT                 PORTBbits.RB1
#define IO_RB1_WPU                  WPUBbits.WPUB1
#define IO_RB1_OD                   ODCONBbits.ODCB1
#define IO_RB1_ANS                  ANSELBbits.ANSELB1
#define IO_RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define IO_RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define IO_RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define IO_RB1_GetValue()           PORTBbits.RB1
#define IO_RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define IO_RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define IO_RB1_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define IO_RB1_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define IO_RB1_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define IO_RB1_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define IO_RB1_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define IO_RB1_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 aliases
#define IO_RB2_TRIS                 TRISBbits.TRISB2
#define IO_RB2_LAT                  LATBbits.LATB2
#define IO_RB2_PORT                 PORTBbits.RB2
#define IO_RB2_WPU                  WPUBbits.WPUB2
#define IO_RB2_OD                   ODCONBbits.ODCB2
#define IO_RB2_ANS                  ANSELBbits.ANSELB2
#define IO_RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define IO_RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define IO_RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define IO_RB2_GetValue()           PORTBbits.RB2
#define IO_RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define IO_RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define IO_RB2_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define IO_RB2_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define IO_RB2_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define IO_RB2_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define IO_RB2_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define IO_RB2_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set RB3 aliases
#define IO_FREQA_TRIS                 TRISBbits.TRISB3
#define IO_FREQA_LAT                  LATBbits.LATB3
#define IO_FREQA_PORT                 PORTBbits.RB3
#define IO_FREQA_WPU                  WPUBbits.WPUB3
#define IO_FREQA_OD                   ODCONBbits.ODCB3
#define IO_FREQA_ANS                  ANSELBbits.ANSELB3
#define IO_FREQA_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define IO_FREQA_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define IO_FREQA_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define IO_FREQA_GetValue()           PORTBbits.RB3
#define IO_FREQA_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define IO_FREQA_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define IO_FREQA_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define IO_FREQA_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define IO_FREQA_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define IO_FREQA_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define IO_FREQA_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define IO_FREQA_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set RB4 aliases
#define IO_BALB_TRIS                 TRISBbits.TRISB4
#define IO_BALB_LAT                  LATBbits.LATB4
#define IO_BALB_PORT                 PORTBbits.RB4
#define IO_BALB_WPU                  WPUBbits.WPUB4
#define IO_BALB_OD                   ODCONBbits.ODCB4
#define IO_BALB_ANS                  ANSELBbits.ANSELB4
#define IO_BALB_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_BALB_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_BALB_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IO_BALB_GetValue()           PORTBbits.RB4
#define IO_BALB_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_BALB_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IO_BALB_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IO_BALB_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IO_BALB_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define IO_BALB_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define IO_BALB_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define IO_BALB_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set RB5 aliases
#define IO_BALA_TRIS                 TRISBbits.TRISB5
#define IO_BALA_LAT                  LATBbits.LATB5
#define IO_BALA_PORT                 PORTBbits.RB5
#define IO_BALA_WPU                  WPUBbits.WPUB5
#define IO_BALA_OD                   ODCONBbits.ODCB5
#define IO_BALA_ANS                  ANSELBbits.ANSELB5
#define IO_BALA_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define IO_BALA_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define IO_BALA_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define IO_BALA_GetValue()           PORTBbits.RB5
#define IO_BALA_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define IO_BALA_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define IO_BALA_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define IO_BALA_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define IO_BALA_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define IO_BALA_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define IO_BALA_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define IO_BALA_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set RC0 aliases
#define IO_DVSB_TRIS                 TRISCbits.TRISC0
#define IO_DVSB_LAT                  LATCbits.LATC0
#define IO_DVSB_PORT                 PORTCbits.RC0
#define IO_DVSB_WPU                  WPUCbits.WPUC0
#define IO_DVSB_OD                   ODCONCbits.ODCC0
#define IO_DVSB_ANS                  ANSELCbits.ANSELC0
#define IO_DVSB_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define IO_DVSB_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define IO_DVSB_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define IO_DVSB_GetValue()           PORTCbits.RC0
#define IO_DVSB_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define IO_DVSB_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define IO_DVSB_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define IO_DVSB_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define IO_DVSB_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define IO_DVSB_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define IO_DVSB_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define IO_DVSB_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set RC1 aliases
#define IO_DVSA_TRIS                 TRISCbits.TRISC1
#define IO_DVSA_LAT                  LATCbits.LATC1
#define IO_DVSA_PORT                 PORTCbits.RC1
#define IO_DVSA_WPU                  WPUCbits.WPUC1
#define IO_DVSA_OD                   ODCONCbits.ODCC1
#define IO_DVSA_ANS                  ANSELCbits.ANSELC1
#define IO_DVSA_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define IO_DVSA_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define IO_DVSA_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define IO_DVSA_GetValue()           PORTCbits.RC1
#define IO_DVSA_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define IO_DVSA_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define IO_DVSA_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define IO_DVSA_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define IO_DVSA_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define IO_DVSA_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define IO_DVSA_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define IO_DVSA_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set RC2 aliases
#define IO_RC2_TRIS                 TRISCbits.TRISC2
#define IO_RC2_LAT                  LATCbits.LATC2
#define IO_RC2_PORT                 PORTCbits.RC2
#define IO_RC2_WPU                  WPUCbits.WPUC2
#define IO_RC2_OD                   ODCONCbits.ODCC2
#define IO_RC2_ANS                  ANSELCbits.ANSELC2
#define IO_RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define IO_RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define IO_RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define IO_RC2_GetValue()           PORTCbits.RC2
#define IO_RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define IO_RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define IO_RC2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define IO_RC2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define IO_RC2_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define IO_RC2_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define IO_RC2_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define IO_RC2_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 aliases
#define IO_RC3_TRIS                 TRISCbits.TRISC3
#define IO_RC3_LAT                  LATCbits.LATC3
#define IO_RC3_PORT                 PORTCbits.RC3
#define IO_RC3_WPU                  WPUCbits.WPUC3
#define IO_RC3_OD                   ODCONCbits.ODCC3
#define IO_RC3_ANS                  ANSELCbits.ANSELC3
#define IO_RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_RC3_GetValue()           PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_RC3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define IO_RC3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define IO_RC3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define IO_RC3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define IO_RC3_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 aliases
#define IO_RC4_TRIS                 TRISCbits.TRISC4
#define IO_RC4_LAT                  LATCbits.LATC4
#define IO_RC4_PORT                 PORTCbits.RC4
#define IO_RC4_WPU                  WPUCbits.WPUC4
#define IO_RC4_OD                   ODCONCbits.ODCC4
#define IO_RC4_ANS                  ANSELCbits.ANSELC4
#define IO_RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define IO_RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define IO_RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define IO_RC4_GetValue()           PORTCbits.RC4
#define IO_RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define IO_RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define IO_RC4_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define IO_RC4_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define IO_RC4_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define IO_RC4_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define IO_RC4_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define IO_RC4_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 aliases
#define IO_VOLA_TRIS                 TRISCbits.TRISC5
#define IO_VOLA_LAT                  LATCbits.LATC5
#define IO_VOLA_PORT                 PORTCbits.RC5
#define IO_VOLA_WPU                  WPUCbits.WPUC5
#define IO_VOLA_OD                   ODCONCbits.ODCC5
#define IO_VOLA_ANS                  ANSELCbits.ANSELC5
#define IO_VOLA_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define IO_VOLA_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define IO_VOLA_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define IO_VOLA_GetValue()           PORTCbits.RC5
#define IO_VOLA_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define IO_VOLA_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define IO_VOLA_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define IO_VOLA_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define IO_VOLA_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define IO_VOLA_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define IO_VOLA_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define IO_VOLA_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RC6 aliases
#define IO_VOLB_TRIS                 TRISCbits.TRISC6
#define IO_VOLB_LAT                  LATCbits.LATC6
#define IO_VOLB_PORT                 PORTCbits.RC6
#define IO_VOLB_WPU                  WPUCbits.WPUC6
#define IO_VOLB_OD                   ODCONCbits.ODCC6
#define IO_VOLB_ANS                  ANSELCbits.ANSELC6
#define IO_VOLB_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define IO_VOLB_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define IO_VOLB_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define IO_VOLB_GetValue()           PORTCbits.RC6
#define IO_VOLB_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define IO_VOLB_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define IO_VOLB_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define IO_VOLB_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define IO_VOLB_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define IO_VOLB_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define IO_VOLB_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define IO_VOLB_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 aliases
#define IO_RQB_TRIS                 TRISCbits.TRISC7
#define IO_RQB_LAT                  LATCbits.LATC7
#define IO_RQB_PORT                 PORTCbits.RC7
#define IO_RQB_WPU                  WPUCbits.WPUC7
#define IO_RQB_OD                   ODCONCbits.ODCC7
#define IO_RQB_ANS                  ANSELCbits.ANSELC7
#define IO_RQB_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define IO_RQB_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define IO_RQB_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define IO_RQB_GetValue()           PORTCbits.RC7
#define IO_RQB_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define IO_RQB_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define IO_RQB_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define IO_RQB_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define IO_RQB_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define IO_RQB_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define IO_RQB_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define IO_RQB_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

// get/set RD1 aliases
#define IO_RD1_TRIS                 TRISDbits.TRISD1
#define IO_RD1_LAT                  LATDbits.LATD1
#define IO_RD1_PORT                 PORTDbits.RD1
#define IO_RD1_WPU                  WPUDbits.WPUD1
#define IO_RD1_OD                   ODCONDbits.ODCD1
#define IO_RD1_ANS                  ANSELDbits.ANSELD1
#define IO_RD1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define IO_RD1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define IO_RD1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define IO_RD1_GetValue()           PORTDbits.RD1
#define IO_RD1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define IO_RD1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define IO_RD1_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define IO_RD1_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define IO_RD1_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define IO_RD1_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define IO_RD1_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define IO_RD1_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set RD2 aliases
#define IO_ISB_TRIS                 TRISDbits.TRISD2
#define IO_ISB_LAT                  LATDbits.LATD2
#define IO_ISB_PORT                 PORTDbits.RD2
#define IO_ISB_WPU                  WPUDbits.WPUD2
#define IO_ISB_OD                   ODCONDbits.ODCD2
#define IO_ISB_ANS                  ANSELDbits.ANSELD2
#define IO_ISB_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define IO_ISB_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define IO_ISB_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define IO_ISB_GetValue()           PORTDbits.RD2
#define IO_ISB_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define IO_ISB_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define IO_ISB_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define IO_ISB_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define IO_ISB_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define IO_ISB_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define IO_ISB_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define IO_ISB_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set RD3 aliases
#define IO_ISA_TRIS                 TRISDbits.TRISD3
#define IO_ISA_LAT                  LATDbits.LATD3
#define IO_ISA_PORT                 PORTDbits.RD3
#define IO_ISA_WPU                  WPUDbits.WPUD3
#define IO_ISA_OD                   ODCONDbits.ODCD3
#define IO_ISA_ANS                  ANSELDbits.ANSELD3
#define IO_ISA_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define IO_ISA_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define IO_ISA_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define IO_ISA_GetValue()           PORTDbits.RD3
#define IO_ISA_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define IO_ISA_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define IO_ISA_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define IO_ISA_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define IO_ISA_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define IO_ISA_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define IO_ISA_SetAnalogMode()      do { ANSELDbits.ANSELD3 = 1; } while(0)
#define IO_ISA_SetDigitalMode()     do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set RD4 aliases
#define IO_RQA_TRIS                 TRISDbits.TRISD4
#define IO_RQA_LAT                  LATDbits.LATD4
#define IO_RQA_PORT                 PORTDbits.RD4
#define IO_RQA_WPU                  WPUDbits.WPUD4
#define IO_RQA_OD                   ODCONDbits.ODCD4
#define IO_RQA_ANS                  ANSELDbits.ANSELD4
#define IO_RQA_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define IO_RQA_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define IO_RQA_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define IO_RQA_GetValue()           PORTDbits.RD4
#define IO_RQA_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define IO_RQA_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define IO_RQA_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define IO_RQA_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define IO_RQA_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define IO_RQA_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define IO_RQA_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define IO_RQA_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set RD5 aliases
#define IO_IRDAT_TRIS                 TRISDbits.TRISD5
#define IO_IRDAT_LAT                  LATDbits.LATD5
#define IO_IRDAT_PORT                 PORTDbits.RD5
#define IO_IRDAT_WPU                  WPUDbits.WPUD5
#define IO_IRDAT_OD                   ODCONDbits.ODCD5
#define IO_IRDAT_ANS                  ANSELDbits.ANSELD5
#define IO_IRDAT_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define IO_IRDAT_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define IO_IRDAT_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define IO_IRDAT_GetValue()           PORTDbits.RD5
#define IO_IRDAT_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define IO_IRDAT_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define IO_IRDAT_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define IO_IRDAT_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define IO_IRDAT_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define IO_IRDAT_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define IO_IRDAT_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define IO_IRDAT_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set RD6 aliases
#define IO_HFA_TRIS                 TRISDbits.TRISD6
#define IO_HFA_LAT                  LATDbits.LATD6
#define IO_HFA_PORT                 PORTDbits.RD6
#define IO_HFA_WPU                  WPUDbits.WPUD6
#define IO_HFA_OD                   ODCONDbits.ODCD6
#define IO_HFA_ANS                  ANSELDbits.ANSELD6
#define IO_HFA_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define IO_HFA_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define IO_HFA_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define IO_HFA_GetValue()           PORTDbits.RD6
#define IO_HFA_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define IO_HFA_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define IO_HFA_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define IO_HFA_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define IO_HFA_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define IO_HFA_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define IO_HFA_SetAnalogMode()      do { ANSELDbits.ANSELD6 = 1; } while(0)
#define IO_HFA_SetDigitalMode()     do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set RD7 aliases
#define IO_HFB_TRIS                 TRISDbits.TRISD7
#define IO_HFB_LAT                  LATDbits.LATD7
#define IO_HFB_PORT                 PORTDbits.RD7
#define IO_HFB_WPU                  WPUDbits.WPUD7
#define IO_HFB_OD                   ODCONDbits.ODCD7
#define IO_HFB_ANS                  ANSELDbits.ANSELD7
#define IO_HFB_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define IO_HFB_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define IO_HFB_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define IO_HFB_GetValue()           PORTDbits.RD7
#define IO_HFB_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define IO_HFB_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define IO_HFB_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define IO_HFB_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define IO_HFB_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define IO_HFB_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define IO_HFB_SetAnalogMode()      do { ANSELDbits.ANSELD7 = 1; } while(0)
#define IO_HFB_SetDigitalMode()     do { ANSELDbits.ANSELD7 = 0; } while(0)

// get/set RE0 aliases
#define IO_FEN_TRIS                 TRISEbits.TRISE0
#define IO_FEN_LAT                  LATEbits.LATE0
#define IO_FEN_PORT                 PORTEbits.RE0
#define IO_FEN_WPU                  WPUEbits.WPUE0
#define IO_FEN_OD                   ODCONEbits.ODCE0
#define IO_FEN_ANS                  ANSELEbits.ANSELE0
#define IO_FEN_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define IO_FEN_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define IO_FEN_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define IO_FEN_GetValue()           PORTEbits.RE0
#define IO_FEN_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define IO_FEN_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define IO_FEN_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define IO_FEN_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define IO_FEN_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define IO_FEN_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define IO_FEN_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define IO_FEN_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set RE1 aliases
#define IO_HFACS_TRIS                 TRISEbits.TRISE1
#define IO_HFACS_LAT                  LATEbits.LATE1
#define IO_HFACS_PORT                 PORTEbits.RE1
#define IO_HFACS_WPU                  WPUEbits.WPUE1
#define IO_HFACS_OD                   ODCONEbits.ODCE1
#define IO_HFACS_ANS                  ANSELEbits.ANSELE1
#define IO_HFACS_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define IO_HFACS_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define IO_HFACS_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define IO_HFACS_GetValue()           PORTEbits.RE1
#define IO_HFACS_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define IO_HFACS_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define IO_HFACS_SetPullup()          do { WPUEbits.WPUE1 = 1; } while(0)
#define IO_HFACS_ResetPullup()        do { WPUEbits.WPUE1 = 0; } while(0)
#define IO_HFACS_SetPushPull()        do { ODCONEbits.ODCE1 = 0; } while(0)
#define IO_HFACS_SetOpenDrain()       do { ODCONEbits.ODCE1 = 1; } while(0)
#define IO_HFACS_SetAnalogMode()      do { ANSELEbits.ANSELE1 = 1; } while(0)
#define IO_HFACS_SetDigitalMode()     do { ANSELEbits.ANSELE1 = 0; } while(0)

// get/set RE2 aliases
#define IO_LFACS_TRIS                 TRISEbits.TRISE2
#define IO_LFACS_LAT                  LATEbits.LATE2
#define IO_LFACS_PORT                 PORTEbits.RE2
#define IO_LFACS_WPU                  WPUEbits.WPUE2
#define IO_LFACS_OD                   ODCONEbits.ODCE2
#define IO_LFACS_ANS                  ANSELEbits.ANSELE2
#define IO_LFACS_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define IO_LFACS_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define IO_LFACS_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define IO_LFACS_GetValue()           PORTEbits.RE2
#define IO_LFACS_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define IO_LFACS_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define IO_LFACS_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define IO_LFACS_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define IO_LFACS_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define IO_LFACS_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define IO_LFACS_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define IO_LFACS_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

// get/set RF0 aliases
#define IO_MUTE_TRIS                 TRISFbits.TRISF0
#define IO_MUTE_LAT                  LATFbits.LATF0
#define IO_MUTE_PORT                 PORTFbits.RF0
#define IO_MUTE_WPU                  WPUFbits.WPUF0
#define IO_MUTE_OD                   ODCONFbits.ODCF0
#define IO_MUTE_ANS                  ANSELFbits.ANSELF0
#define IO_MUTE_SetHigh()            do { LATFbits.LATF0 = 1; } while(0)
#define IO_MUTE_SetLow()             do { LATFbits.LATF0 = 0; } while(0)
#define IO_MUTE_Toggle()             do { LATFbits.LATF0 = ~LATFbits.LATF0; } while(0)
#define IO_MUTE_GetValue()           PORTFbits.RF0
#define IO_MUTE_SetDigitalInput()    do { TRISFbits.TRISF0 = 1; } while(0)
#define IO_MUTE_SetDigitalOutput()   do { TRISFbits.TRISF0 = 0; } while(0)
#define IO_MUTE_SetPullup()          do { WPUFbits.WPUF0 = 1; } while(0)
#define IO_MUTE_ResetPullup()        do { WPUFbits.WPUF0 = 0; } while(0)
#define IO_MUTE_SetPushPull()        do { ODCONFbits.ODCF0 = 0; } while(0)
#define IO_MUTE_SetOpenDrain()       do { ODCONFbits.ODCF0 = 1; } while(0)
#define IO_MUTE_SetAnalogMode()      do { ANSELFbits.ANSELF0 = 1; } while(0)
#define IO_MUTE_SetDigitalMode()     do { ANSELFbits.ANSELF0 = 0; } while(0)

// get/set RF1 aliases
#define IO_PHASE_TRIS                 TRISFbits.TRISF1
#define IO_PHASE_LAT                  LATFbits.LATF1
#define IO_PHASE_PORT                 PORTFbits.RF1
#define IO_PHASE_WPU                  WPUFbits.WPUF1
#define IO_PHASE_OD                   ODCONFbits.ODCF1
#define IO_PHASE_ANS                  ANSELFbits.ANSELF1
#define IO_PHASE_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define IO_PHASE_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define IO_PHASE_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define IO_PHASE_GetValue()           PORTFbits.RF1
#define IO_PHASE_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define IO_PHASE_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define IO_PHASE_SetPullup()          do { WPUFbits.WPUF1 = 1; } while(0)
#define IO_PHASE_ResetPullup()        do { WPUFbits.WPUF1 = 0; } while(0)
#define IO_PHASE_SetPushPull()        do { ODCONFbits.ODCF1 = 0; } while(0)
#define IO_PHASE_SetOpenDrain()       do { ODCONFbits.ODCF1 = 1; } while(0)
#define IO_PHASE_SetAnalogMode()      do { ANSELFbits.ANSELF1 = 1; } while(0)
#define IO_PHASE_SetDigitalMode()     do { ANSELFbits.ANSELF1 = 0; } while(0)

// get/set RF2 aliases
#define IO_LFEQ_TRIS                 TRISFbits.TRISF2
#define IO_LFEQ_LAT                  LATFbits.LATF2
#define IO_LFEQ_PORT                 PORTFbits.RF2
#define IO_LFEQ_WPU                  WPUFbits.WPUF2
#define IO_LFEQ_OD                   ODCONFbits.ODCF2
#define IO_LFEQ_ANS                  ANSELFbits.ANSELF2
#define IO_LFEQ_SetHigh()            do { LATFbits.LATF2 = 1; } while(0)
#define IO_LFEQ_SetLow()             do { LATFbits.LATF2 = 0; } while(0)
#define IO_LFEQ_Toggle()             do { LATFbits.LATF2 = ~LATFbits.LATF2; } while(0)
#define IO_LFEQ_GetValue()           PORTFbits.RF2
#define IO_LFEQ_SetDigitalInput()    do { TRISFbits.TRISF2 = 1; } while(0)
#define IO_LFEQ_SetDigitalOutput()   do { TRISFbits.TRISF2 = 0; } while(0)
#define IO_LFEQ_SetPullup()          do { WPUFbits.WPUF2 = 1; } while(0)
#define IO_LFEQ_ResetPullup()        do { WPUFbits.WPUF2 = 0; } while(0)
#define IO_LFEQ_SetPushPull()        do { ODCONFbits.ODCF2 = 0; } while(0)
#define IO_LFEQ_SetOpenDrain()       do { ODCONFbits.ODCF2 = 1; } while(0)
#define IO_LFEQ_SetAnalogMode()      do { ANSELFbits.ANSELF2 = 1; } while(0)
#define IO_LFEQ_SetDigitalMode()     do { ANSELFbits.ANSELF2 = 0; } while(0)

// get/set RF3 aliases
#define IO_SLCS_TRIS                 TRISFbits.TRISF3
#define IO_SLCS_LAT                  LATFbits.LATF3
#define IO_SLCS_PORT                 PORTFbits.RF3
#define IO_SLCS_WPU                  WPUFbits.WPUF3
#define IO_SLCS_OD                   ODCONFbits.ODCF3
#define IO_SLCS_ANS                  ANSELFbits.ANSELF3
#define IO_SLCS_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define IO_SLCS_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define IO_SLCS_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define IO_SLCS_GetValue()           PORTFbits.RF3
#define IO_SLCS_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define IO_SLCS_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define IO_SLCS_SetPullup()          do { WPUFbits.WPUF3 = 1; } while(0)
#define IO_SLCS_ResetPullup()        do { WPUFbits.WPUF3 = 0; } while(0)
#define IO_SLCS_SetPushPull()        do { ODCONFbits.ODCF3 = 0; } while(0)
#define IO_SLCS_SetOpenDrain()       do { ODCONFbits.ODCF3 = 1; } while(0)
#define IO_SLCS_SetAnalogMode()      do { ANSELFbits.ANSELF3 = 1; } while(0)
#define IO_SLCS_SetDigitalMode()     do { ANSELFbits.ANSELF3 = 0; } while(0)

// get/set RF4 aliases
#define IO_LFB_TRIS                 TRISFbits.TRISF4
#define IO_LFB_LAT                  LATFbits.LATF4
#define IO_LFB_PORT                 PORTFbits.RF4
#define IO_LFB_WPU                  WPUFbits.WPUF4
#define IO_LFB_OD                   ODCONFbits.ODCF4
#define IO_LFB_ANS                  ANSELFbits.ANSELF4
#define IO_LFB_SetHigh()            do { LATFbits.LATF4 = 1; } while(0)
#define IO_LFB_SetLow()             do { LATFbits.LATF4 = 0; } while(0)
#define IO_LFB_Toggle()             do { LATFbits.LATF4 = ~LATFbits.LATF4; } while(0)
#define IO_LFB_GetValue()           PORTFbits.RF4
#define IO_LFB_SetDigitalInput()    do { TRISFbits.TRISF4 = 1; } while(0)
#define IO_LFB_SetDigitalOutput()   do { TRISFbits.TRISF4 = 0; } while(0)
#define IO_LFB_SetPullup()          do { WPUFbits.WPUF4 = 1; } while(0)
#define IO_LFB_ResetPullup()        do { WPUFbits.WPUF4 = 0; } while(0)
#define IO_LFB_SetPushPull()        do { ODCONFbits.ODCF4 = 0; } while(0)
#define IO_LFB_SetOpenDrain()       do { ODCONFbits.ODCF4 = 1; } while(0)
#define IO_LFB_SetAnalogMode()      do { ANSELFbits.ANSELF4 = 1; } while(0)
#define IO_LFB_SetDigitalMode()     do { ANSELFbits.ANSELF4 = 0; } while(0)

// get/set RF5 aliases
#define IO_LFA_TRIS                 TRISFbits.TRISF5
#define IO_LFA_LAT                  LATFbits.LATF5
#define IO_LFA_PORT                 PORTFbits.RF5
#define IO_LFA_WPU                  WPUFbits.WPUF5
#define IO_LFA_OD                   ODCONFbits.ODCF5
#define IO_LFA_ANS                  ANSELFbits.ANSELF5
#define IO_LFA_SetHigh()            do { LATFbits.LATF5 = 1; } while(0)
#define IO_LFA_SetLow()             do { LATFbits.LATF5 = 0; } while(0)
#define IO_LFA_Toggle()             do { LATFbits.LATF5 = ~LATFbits.LATF5; } while(0)
#define IO_LFA_GetValue()           PORTFbits.RF5
#define IO_LFA_SetDigitalInput()    do { TRISFbits.TRISF5 = 1; } while(0)
#define IO_LFA_SetDigitalOutput()   do { TRISFbits.TRISF5 = 0; } while(0)
#define IO_LFA_SetPullup()          do { WPUFbits.WPUF5 = 1; } while(0)
#define IO_LFA_ResetPullup()        do { WPUFbits.WPUF5 = 0; } while(0)
#define IO_LFA_SetPushPull()        do { ODCONFbits.ODCF5 = 0; } while(0)
#define IO_LFA_SetOpenDrain()       do { ODCONFbits.ODCF5 = 1; } while(0)
#define IO_LFA_SetAnalogMode()      do { ANSELFbits.ANSELF5 = 1; } while(0)
#define IO_LFA_SetDigitalMode()     do { ANSELFbits.ANSELF5 = 0; } while(0)

// get/set RF6 aliases
#define IO_PLED_TRIS                 TRISFbits.TRISF6
#define IO_PLED_LAT                  LATFbits.LATF6
#define IO_PLED_PORT                 PORTFbits.RF6
#define IO_PLED_WPU                  WPUFbits.WPUF6
#define IO_PLED_OD                   ODCONFbits.ODCF6
#define IO_PLED_ANS                  ANSELFbits.ANSELF6
#define IO_PLED_SetHigh()            do { LATFbits.LATF6 = 1; } while(0)
#define IO_PLED_SetLow()             do { LATFbits.LATF6 = 0; } while(0)
#define IO_PLED_Toggle()             do { LATFbits.LATF6 = ~LATFbits.LATF6; } while(0)
#define IO_PLED_GetValue()           PORTFbits.RF6
#define IO_PLED_SetDigitalInput()    do { TRISFbits.TRISF6 = 1; } while(0)
#define IO_PLED_SetDigitalOutput()   do { TRISFbits.TRISF6 = 0; } while(0)
#define IO_PLED_SetPullup()          do { WPUFbits.WPUF6 = 1; } while(0)
#define IO_PLED_ResetPullup()        do { WPUFbits.WPUF6 = 0; } while(0)
#define IO_PLED_SetPushPull()        do { ODCONFbits.ODCF6 = 0; } while(0)
#define IO_PLED_SetOpenDrain()       do { ODCONFbits.ODCF6 = 1; } while(0)
#define IO_PLED_SetAnalogMode()      do { ANSELFbits.ANSELF6 = 1; } while(0)
#define IO_PLED_SetDigitalMode()     do { ANSELFbits.ANSELF6 = 0; } while(0)

// get/set RF7 aliases
#define IO_PSW_TRIS                 TRISFbits.TRISF7
#define IO_PSW_LAT                  LATFbits.LATF7
#define IO_PSW_PORT                 PORTFbits.RF7
#define IO_PSW_WPU                  WPUFbits.WPUF7
#define IO_PSW_OD                   ODCONFbits.ODCF7
#define IO_PSW_ANS                  ANSELFbits.ANSELF7
#define IO_PSW_SetHigh()            do { LATFbits.LATF7 = 1; } while(0)
#define IO_PSW_SetLow()             do { LATFbits.LATF7 = 0; } while(0)
#define IO_PSW_Toggle()             do { LATFbits.LATF7 = ~LATFbits.LATF7; } while(0)
#define IO_PSW_GetValue()           PORTFbits.RF7
#define IO_PSW_SetDigitalInput()    do { TRISFbits.TRISF7 = 1; } while(0)
#define IO_PSW_SetDigitalOutput()   do { TRISFbits.TRISF7 = 0; } while(0)
#define IO_PSW_SetPullup()          do { WPUFbits.WPUF7 = 1; } while(0)
#define IO_PSW_ResetPullup()        do { WPUFbits.WPUF7 = 0; } while(0)
#define IO_PSW_SetPushPull()        do { ODCONFbits.ODCF7 = 0; } while(0)
#define IO_PSW_SetOpenDrain()       do { ODCONFbits.ODCF7 = 1; } while(0)
#define IO_PSW_SetAnalogMode()      do { ANSELFbits.ANSELF7 = 1; } while(0)
#define IO_PSW_SetDigitalMode()     do { ANSELFbits.ANSELF7 = 0; } while(0)

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


#endif // PINS_H
/**
 End of File
*/