#include "power.h"
#include "mcc_generated_files\system\pins.h"
#include "mcc_generated_files\system\interrupt.h"
#include "mcc_generated_files\system\clock.h"
#include "as1115.h"

bool lastButtonState = true; 

bool IsInputOneOn(void) { return (IO_DV1_PORT == 1); }
bool IsInputTwoOn(void) { return (IO_DV2_PORT == 1); }
bool IsInputThreeOn(void) { return (IO_DV3_PORT == 1); }
bool IsInputBtOn(void) { return (IO_DVBT_PORT == 1); }
void ToggleInputOnePower(void) { IO_DV1_Toggle(); }
void ToggleInputTwoPower(void) { IO_DV2_Toggle(); }
void ToggleInputThreePower(void) { IO_DV3_Toggle(); }
void ToggleInputBtPower(void) { IO_DVBT_Toggle(); }
void Power_HandleSleepWake()
{
            bool currentButtonState = IO_PSW_PORT;   // or IO_PSW_GetValue()

        if (currentButtonState == 0 && lastButtonState == 1)
        {
            __delay_ms(80);                    // debounce

            AS1115_Write(AS1115_REG_SHUTDOWN, AS1115_SHUTDOWN);
            __delay_ms(100);

            // === TURN OFF ===
            IO_PLED_Toggle();                  // Toggle when user presses to turn off
            IO_POWER_SetLow();

            // === PREPARE FOR SLEEP ===
            INTERRUPT_GlobalInterruptDisable();

            // Disable all peripheral interrupts
            PIE0 = 0; PIE1 = 0; PIE2 = 0; PIE3 = 0;
            PIE4 = 0; PIE5 = 0; PIE6 = 0; PIE7 = 0;

            // Clear all flags
            PIR0 = 0; PIR1 = 0; PIR2 = 0; PIR3 = 0;
            PIR4 = 0; PIR5 = 0; PIR6 = 0; PIR7 = 0;

            IOCAF = 0; IOCBF = 0; IOCCF = 0; IOCEF = 0;

            CLRWDT();
            WDTCON0bits.SEN = 0;               // Disable WDT

            SLEEP();
            NOP();

            // ========================
            // WAKE UP
            // ========================
            WDTCON0bits.SEN = 1;               // Optional: re-enable WDT

            IO_POWER_SetHigh();

            // Force LED ON after wake-up (as you requested)
            IO_PLED_SetHigh();

            // Re-enable your normal system interrupts
            INTERRUPT_GlobalInterruptEnable();

            // Re-enable the peripherals you use
            PIE5bits.INT1IE = 1;     // AS1115 button matrix
            PIE4bits.CCP1IE = 1;     // IR receiver
            PIE3bits.TMR0IE = 1;     // System timer

            // Re-enable AS1115
            AS1115_Write(AS1115_REG_SHUTDOWN, AS1115_NORMAL_OP);

            // Optional: short confirmation flash
            // __delay_ms(50);
            // IO_PLED_Toggle();
            // __delay_ms(80);
            // IO_PLED_Toggle();
        }

        lastButtonState = currentButtonState;
}