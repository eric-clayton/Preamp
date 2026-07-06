#include "power.h"
#include "mute.h"
#include "ir.h"
#include "mcc_generated_files\system\pins.h"
#include "mcc_generated_files\system\clock.h"
#include "audio_control.h"
#include "storage.h"

#include "as1115.h"

static bool remotePowerPressed = false;
static uint8_t systemPoweredOn = 0;

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

void TurnStandby()
{
    PLED_SetLow();
    Mute_Engage();
    POWER_SetLow();
    SetPowerState(0);
    AS1115_Write(AS1115_REG_SHUTDOWN, AS1115_SHUTDOWN);

    PIE5bits.INT1IE = 0;
    PIE3bits.TMR0IE = 0;
    PIE5bits.I2C2RXIE = 0;
    PIE5bits.I2C2TXIE = 0;
    PIE6bits.I2C2EIE = 0;
    PIE6bits.I2C2IE = 0;
    PIE0bits.IOCIE = 1;
    IOCAFbits.IOCAF4 = 0;

    Prepare_IR_For_Sleep();
    remotePowerPressed = false;
}
void TurnOn()
{
    PLED_SetHigh();
    POWER_SetHigh();
    SetPowerState(1);
    Mute_ScheduleRelease();
    AS1115_Write(AS1115_REG_SHUTDOWN, AS1115_NORMAL_OP);
    IOCAFbits.IOCAF4 = 0;

    PIE5bits.INT1IE = 1;
    PIE3bits.TMR0IE = 1;
    PIE5bits.I2C2RXIE = 1;
    PIE5bits.I2C2TXIE = 1;
    PIE6bits.I2C2EIE = 1;
    PIE6bits.I2C2IE = 1;
    remotePowerPressed = false;
}
// power.c
void Power_EnterSleep(void)
{
    TurnStandby();

    while (PSW_GetValue() != 0 && !remotePowerPressed)
    {
        PIE4bits.CCP1IE = 1;
        SLEEP();
        NOP();
        __delay_ms(100);
        IR_ProcessFrame();
    }

    while (PSW_GetValue() == 0 && !remotePowerPressed);
    __delay_ms(50);

    TurnOn();
}

void Power_HandleSleepWake(void)
{
    if (PSW_PORT == 0 || remotePowerPressed)
    {
        while (PSW_GetValue() == 0 && !remotePowerPressed);
        __delay_ms(50); // Debounce
        Power_EnterSleep();
    }
}

void Power_ApplyLoadedState(void)
{
    if (!systemPoweredOn)   // device was off when it last saved
    {
        Power_EnterSleep();
    }
    else
    {
        TurnOn();
    }
}
void HandleRemotePowerButton(void)
{
    remotePowerPressed = true;
}
uint8_t GetPowerState(void) {
    return systemPoweredOn;
}
void Power_LoadSettings(uint8_t isOn) {
    systemPoweredOn = isOn;
    Power_ApplyLoadedState();
    
}
void SetPowerState(uint8_t isOn) {
    if (systemPoweredOn == isOn) return;   // no real change, skip a dirty flag
    systemPoweredOn = isOn;
    Storage_MarkDirty();
    Storage_ForceSync();
}
