#include "display.h"
#include "power.h"
#include "mute.h"
#include "ir.h"
#include "mcc_generated_files\system\pins.h"
#include "mcc_generated_files\system\clock.h"
#include "audio_control.h"
#include "storage.h"

#include "as1115.h"

#define PSW_DEBOUNCE_MS   25

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
    Display_LEDsStandby(); 
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
    POWER_SetHigh();
    __delay_ms(10);
    Display_LEDsWake(); 
    
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

// A press is real only if the pin reads low for PSW_DEBOUNCE_MS in a row.
static bool PowerButton_ConfirmedPress(void)
{
    for (uint8_t i = 0; i < PSW_DEBOUNCE_MS; i++)
    {
        if (PSW_GetValue() != 0) return false;   // high = noise, not a press
        __delay_ms(1);
    }
    return true;
}

// Returns once the pin has read high for PSW_DEBOUNCE_MS in a row.
static void PowerButton_WaitRelease(void)
{
    uint8_t highMs = 0;
    while (highMs < PSW_DEBOUNCE_MS)
    {
        if (PSW_GetValue() != 0) { __delay_ms(1); highMs++; }
        else                      highMs = 0;     // still held or bouncing
    }
}

void Power_EnterSleep(void)
{
    TurnStandby();

    while (!remotePowerPressed)
    {
        PIE4bits.CCP1IE = 1;
        SLEEP();
        NOP();

        __delay_ms(5);                       // let the contact settle after the wake edge
        if (PowerButton_ConfirmedPress())    // check the button BEFORE the 100 ms IR delay
        {
            PowerButton_WaitRelease();
            break;
        }

        __delay_ms(100);                     // IR frame is still arriving
        IR_ProcessFrame();
    }

    TurnOn();
}

void Power_HandleSleepWake(void)
{
    if (remotePowerPressed || PowerButton_ConfirmedPress())
    {
        PowerButton_WaitRelease();
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
