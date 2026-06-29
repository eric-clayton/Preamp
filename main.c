#include "mcc_generated_files/system/system.h"
#include "src/as1115.h"
#include <stdint.h>
#include "src/buttons.h"
#include "src/ir.h"
#include "src/systick.h"
#include "src/rotoryenc.h"
#include "src/storage.h"
#include "src/ui_manager.h"
#include "src/power.h"
#include "src/input.h"
#include "src/mute.h"
#include "src/tone.h"


int main(void) {
    SYSTEM_Initialize();
    PLED_SetHigh();
    POWER_SetHigh();
    // 2. Register handlers
    TMR0_OverflowCallbackRegister(SysTick_Callback);
    INT1_SetInterruptHandler(HandleButtonPressed);
    CCP3_SetCallBack(IR_CaptureHandler);
    

    // 3. ENABLE INTERRUPTS FIRST
    // If I2C is interrupt-based, it MUST have these on to function
    INTERRUPT_GlobalInterruptEnable(); 
    
    // 4. Now perform I2C operations
    uint8_t dummy[2];
    AS1115_ReadKeys(dummy);
    
    AS1115_Init();
    
    TMR0_Start();
    
    ROTARYENC_Initialize();
    Tone_Init();
    Input_Init();
    GrabDataFromEEPROM();
    Parameters_Initialize();
    UI_Manager_Reset();
    
    while(1) {

        Power_HandleSleepWake();

        IR_ProcessFrame();

        UpdateButton();

        CheckIfLongPress();

        UI_Manager_HandleBlink();

        UpdateEncoders();

        SyncStorage();

        HandleInputSwitchPower();

        Mute_Update();
    }
}






