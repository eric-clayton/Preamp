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
#include "src/bluetooth.h"
#include "src/digipot.h"

int main(void) {
    SYSTEM_Initialize();
   
    // 2. Register handlers

    TMR0_OverflowCallbackRegister(SysTick_Callback);
    INT1_SetInterruptHandler(HandleButtonPressed);
    CCP3_SetCallBack(IR_CaptureHandler);

    DigiPot_Init();
    Tone_Init();
    Input_Init();
    Bluetooth_Init();
    ROTARYENC_Initialize();

    INTERRUPT_GlobalInterruptEnable(); 

    TMR0_Start();
    AS1115_Init();

    GrabDataFromEEPROM();
    Parameters_Initialize();

    uint8_t dummy[2];
    AS1115_ReadKeys(dummy);
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






