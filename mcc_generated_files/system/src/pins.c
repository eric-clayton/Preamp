/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 3.1.1
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

#include "../pins.h"

void (*IO_PSW_InterruptHandler)(void);

void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0x0;
    LATB = 0x6;
    LATC = 0x0;
    LATD = 0x0;
    LATE = 0x0;
    LATF = 0x0;
    /**
    ODx registers
    */
    ODCONA = 0x0;
    ODCONB = 0x6;
    ODCONC = 0x0;
    ODCOND = 0x0;
    ODCONE = 0x0;
    ODCONF = 0x0;

    /**
    TRISx registers
    */
    TRISA = 0x10;
    TRISB = 0xF9;
    TRISC = 0xEE;
    TRISD = 0xD3;
    TRISE = 0x0;
    TRISF = 0x30;

    /**
    ANSELx registers
    */
    ANSELA = 0x0;
    ANSELB = 0xC0;
    ANSELC = 0x0;
    ANSELD = 0x1;
    ANSELE = 0x0;
    ANSELF = 0x0;

    /**
    WPUx registers
    */
    WPUA = 0x10;
    WPUB = 0x0;
    WPUC = 0x0;
    WPUD = 0x0;
    WPUE = 0x0;
    WPUF = 0x0;


    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    SLRCOND = 0xFF;
    SLRCONE = 0x7;
    SLRCONF = 0xFF;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLD = 0xFF;
    INLVLE = 0xF;
    INLVLF = 0xFF;

   /**
    RxyI2C | RxyFEAT registers   
    */
    RB1I2C = 0x0;
    RB2I2C = 0x0;
    RC3I2C = 0x0;
    RC4I2C = 0x0;
    RD0I2C = 0x0;
    RD1I2C = 0x0;
    /**
    PPS registers
    */
    CCP1PPS = 0x11; //RC1->CCP1:CCP1;
    INT1PPS = 0x19; //RD1->INTERRUPT MANAGER:INT1;
    SPI1SDIPPS = 0x13; //RC3->SPI1:SDI1;
    RC4PPS = 0x1F;  //RC4->SPI1:SDO1;
    I2C2SCLPPS = 0x9;  //RB1->I2C2:SCL2;
    RB1PPS = 0x23;  //RB1->I2C2:SCL2;
    I2C2SDAPPS = 0xA;  //RB2->I2C2:SDA2;
    RB2PPS = 0x24;  //RB2->I2C2:SDA2;
    SPI1SCKPPS = 0x12;  //RC2->SPI1:SCK1;
    RC2PPS = 0x1E;  //RC2->SPI1:SCK1;

   /**
    IOCx registers 
    */
    IOCAP = 0x0;
    IOCAN = 0x10;
    IOCAF = 0x0;
    IOCBP = 0x0;
    IOCBN = 0x0;
    IOCBF = 0x0;
    IOCCP = 0x0;
    IOCCN = 0x0;
    IOCCF = 0x0;
    IOCEP = 0x0;
    IOCEN = 0x0;
    IOCEF = 0x0;

    IO_PSW_SetInterruptHandler(IO_PSW_DefaultInterruptHandler);

    // Enable PIE0bits.IOCIE interrupt 
    PIE0bits.IOCIE = 1; 
}
  
void PIN_MANAGER_IOC(void)
{
    // interrupt on change for pin IO_PSW
    if(IOCAFbits.IOCAF4 == 1)
    {
        IO_PSW_ISR();  
    }
}
   
/**
   IO_PSW Interrupt Service Routine
*/
void IO_PSW_ISR(void) {

    // Add custom IO_PSW code

    // Call the interrupt handler for the callback registered at runtime
    if(IO_PSW_InterruptHandler)
    {
        IO_PSW_InterruptHandler();
    }
    IOCAFbits.IOCAF4 = 0;
}

/**
  Allows selecting an interrupt handler for IO_PSW at application runtime
*/
void IO_PSW_SetInterruptHandler(void (* InterruptHandler)(void)){
    IO_PSW_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IO_PSW
*/
void IO_PSW_DefaultInterruptHandler(void){
    // add your IO_PSW interrupt custom code
    // or set custom function using IO_PSW_SetInterruptHandler()
}
/**
 End of File
*/