#include "power.h"
#include "mute.h"
#include "ir.h"
#include "mcc_generated_files\system\pins.h"
#include "mcc_generated_files\system\clock.h"
#include "digipot.h"
#include "as1115.h"

bool remotePowerPressed = false;

bool IsInputOneOn(void) {
    return IsInputOneExpanderBitSet();
}
bool IsInputTwoOn(void) {
    return IsInputTwoExpanderBitSet();
}
bool IsInputThreeOn(void) {
    return IsInputThreeExpanderBitSet();
}
bool IsInputBtOn(void) {
    return IsInputBTExpanderBitSet();
}

void ToggleInputOnePower(void) { DV1_Toggle(); }
void ToggleInputTwoPower(void) { DV2_Toggle();}
void ToggleInputThreePower(void) { DV3_Toggle();}
void ToggleInputBtPower(void) { DVBT_Toggle();}

void Power_HandleSleepWake()
{
    if (PSW_PORT == 0 || remotePowerPressed)
    {
        while(PSW_GetValue() == 0 && !remotePowerPressed); 
        __delay_ms(50); // Debounce

        PLED_SetLow();
        Mute_Engage();
        POWER_SetLow();
        AS1115_Write(AS1115_REG_SHUTDOWN, AS1115_SHUTDOWN);
        remotePowerPressed = false;
        // 2. DISABLE all interrupts except the Power Button (IOC)
        PIE5bits.INT1IE = 0;
        PIE3bits.TMR0IE = 0;
        PIE5bits.I2C2RXIE = 0;
        PIE5bits.I2C2TXIE = 0;
        PIE6bits.I2C2EIE = 0;
        PIE6bits.I2C2IE = 0;

        // 3. Ensure IOC (Power Button) is the only thing that can wake us
        PIE0bits.IOCIE = 1;   
        IOCAFbits.IOCAF4 = 0; // Clear the specific flag for RA4
        
        // 4. Go to Sleep
        Prepare_IR_For_Sleep();

        while(PSW_GetValue() != 0 && !remotePowerPressed)
        {
            // Enable only CCP1 and IOC interrupts here
            PIE4bits.CCP1IE = 1; 
            
            SLEEP(); 
            NOP(); 

            // After waking, give the IR state machine a moment to see if a full 
            // frame is coming in. NEC frames take about 70-100ms.
            __delay_ms(100); 
            
            IR_ProcessFrame(); // Check if frameReady was set by the ISR during that 100ms
            
            // If the remotePowerPressed wasn't updated by IR_ProcessFrame, 
            // the loop will check IO_PSW and then go back to SLEEP.
        }
        
        // --- MCU IS HALTED HERE UNTIL RA4 IS PRESSED ---
       
        // 5. Wake up logic: Wait for button release again
        while(PSW_GetValue() == 0 && !remotePowerPressed);
        __delay_ms(50);
        IOCAFbits.IOCAF4 = 0; // Clear flag so we don't immediately re-enter ISR
        
        // 6. RE-ENABLE all interrupts to resume normal operation
        PIE5bits.INT1IE = 1;
        PIE3bits.TMR0IE = 1;
        PIE5bits.I2C2RXIE = 1;
        PIE5bits.I2C2TXIE = 1;
        PIE6bits.I2C2EIE = 1;
        PIE6bits.I2C2IE = 1;

        PLED_SetHigh();
        POWER_SetHigh();
        Mute_ScheduleRelease();
        AS1115_Write(AS1115_REG_SHUTDOWN, AS1115_NORMAL_OP);
        remotePowerPressed = false;
    }
}
void HandleRemotePowerButton(void)
{
    remotePowerPressed = true;
}