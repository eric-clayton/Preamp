#include "mcc_generated_files/system/system.h"
#include "as1115.h"
#include <stdint.h>
#include "buttons.h"
#include "ir.h"
#include "systick.h"
#include "rotoryenc.h"
#include "storage.h"
#include "mode.h"
#include "power.h"
#include "input.h"
#include "mute.h"

int main(void) {
    SYSTEM_Initialize();
    PIR0 = PIR1 = PIR2 = PIR3 = PIR4 = PIR5 = PIR6 = PIR7 = 0;
    IOCAF = IOCBF = IOCCF = IOCEF = 0;
    // 1. Give the hardware a moment to breathe (Essential for I2C slaves)
    __delay_ms(100); 

    // 2. Register handlers
    TMR0_OverflowCallbackRegister(SysTick_Callback);
    INT1_SetInterruptHandler(HandleButtonPressed);
    CCP1_SetCallBack(IR_CaptureHandler);
    

    // 3. ENABLE INTERRUPTS FIRST
    // If I2C is interrupt-based, it MUST have these on to function
    INTERRUPT_GlobalInterruptEnable(); 
    
    // 4. Now perform I2C operations
    uint8_t dummy[2];
    AS1115_ReadKeys(dummy);
    
    AS1115_Init();

    TMR0_Start();
    
    ROTARYENC_Initialize();
    GrabDataFromEEPROM();
    Parameters_Initialize();
    InitializeNormalMode();
    
    while(1) {
        // Inside your while(1) loop

        Power_HandleSleepWake();

        IR_ProcessFrame();

        UpdateButton();

        // --- Hold Detection Logic ---
        HandleLongPress();

        // --- Generalized Continuous Blink Logic ---
        HandleLEDBlink();

        UpdateEncoders();

        SyncDirtyParameters();

        HandleInputSwitchPower();

        Mute_Update();
    }
}






