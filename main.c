#include "mcc_generated_files/system/system.h"
#include "src/as1115.h"
#include <stdint.h>
#include "src/buttons.h"
#include "src/ir.h"
#include "src/systick.h"
#include "src/rotoryenc.h"
#include "src/storage.h"
#include "src/mode.h"
#include "src/power.h"
#include "src/input.h"
#include "src/mute.h"

int main(void) {
    SYSTEM_Initialize();
    IO_PLED_SetHigh();
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

        Power_HandleSleepWake();

        IR_ProcessFrame();

        UpdateButton();

        HandleLongPress();

        HandleLEDBlink();

        UpdateEncoders();

        SyncStorage();

        HandleInputSwitchPower();

        Mute_Update();
    }
}






