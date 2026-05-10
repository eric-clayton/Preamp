#include "ir.h"
#include "power.h"
#include <xc.h>
#include "mcc_generated_files\system\interrupt.h"
#include "systick.h"
#include "parameters.h"

typedef enum {
    IR_IDLE,
    IR_DATA
} IR_State;

static IR_State irState = IR_IDLE;
static uint8_t  lastFrameValid = 0;
static uint32_t activeCode = 0;
volatile uint16_t lastCapture = 0;
volatile uint32_t necCode = 0;
volatile uint8_t bitIndex = 0;
volatile uint8_t frameReady = 0;
volatile uint8_t repeatReady = 0;
volatile uint32_t lastIrTime = 0;

void HandleRemoteAction(uint32_t code, bool repeat) {
    // 1. Convert current raw value to display percent (0-100)
    uint16_t currentPercent = ((uint16_t)volumeKnob.value * 100 + 127) / 254;

    if (code == 0xF609FF00) { // Up
        if (currentPercent < 100) currentPercent++;
    } 
    else if (code == 0xEA15FF00) { // Down
        if (currentPercent > 0) currentPercent--;
    }
    else if(code == 0xBA45FF00) 
    {
        if(!repeat)
        {
            HandleRemotePowerButton(); // no repeat for power
        }
        return;
    }
    else {
        return;
    }

    // 2. Convert percent back to raw value (0-254)
    // Formula: (Percent * 254 + 50) / 100
    // 50 is half of 100, which handles the rounding
    volumeKnob.value = (uint8_t)(((uint16_t)currentPercent * 254 + 50) / 100);

    // 3. Sync the display
    Parameter_Display(&volumeKnob);
}




void IR_CaptureHandler(uint16_t now)
{
    uint16_t currentPulse = now - lastCapture;
    lastCapture = now;
    lastIrTime = systemTicks;

    switch (irState)
    {
        case IR_IDLE:
            // Header: Expecting ~27k to 31k (13.5ms to 15ms)
            if (currentPulse > 29000 && currentPulse < 32000) {
                irState  = IR_DATA;
                necCode  = 0;
                bitIndex = 0;
            }
            // Repeat: Expecting ~25.5k (11.25ms)
            else if (currentPulse > 24000 && currentPulse < 29000) {
                if (lastFrameValid) {
                    repeatReady = 1;
                }
            }
            break;

        case IR_DATA:
            // Bit 0 is ~2250, Bit 1 is ~4500. 
            // We use a window of 1500 to 6000.
            if (currentPulse > 1500 && currentPulse < 6000) {
                necCode >>= 1;
                
                // Threshold: halfway between 2250 and 4500 is 3375
                if (currentPulse > 3375) { 
                    necCode |= 0x80000000;
                }
                
                bitIndex++;
                if (bitIndex == 32) {
                    frameReady     = 1;
                    lastFrameValid = 1;
                    irState        = IR_IDLE;
                }
            } else {
                // If we get a pulse that is way too short or way too long, reset
                irState = IR_IDLE;
            }
            break;
    }
}

void IR_ProcessFrame(void)
{
    // 1. Handle New Data Frames
    if (frameReady) {
        INTERRUPT_GlobalInterruptDisable();
        uint32_t capturedCode = necCode;
        frameReady = 0;
        INTERRUPT_GlobalInterruptEnable();

        // NEC checksum validation before accepting
        uint8_t addr    =  capturedCode        & 0xFF;
        uint8_t addrInv = (capturedCode >> 8)  & 0xFF;
        uint8_t cmd     = (capturedCode >> 16) & 0xFF;
        uint8_t cmdInv  = (capturedCode >> 24) & 0xFF;

        if ((addr ^ addrInv) == 0xFF && (cmd ^ cmdInv) == 0xFF) {
            activeCode     = capturedCode;
            lastFrameValid = 1;
            HandleRemoteAction(activeCode, false);
        } else {
            lastFrameValid = 0; // corrupt — block repeats
        }
    }

    // 2. Handle Repeats
    if (repeatReady) {
        repeatReady = 0;
        if (lastFrameValid && activeCode != 0) {
            HandleRemoteAction(activeCode, true);
        }
    }

    // 3. Safety: If no IR seen for 150ms, user let go of button
    if (systemTicks - lastIrTime > 150) {
        activeCode     = 0;
        lastFrameValid = 0;
    }
}
void Prepare_IR_For_Sleep(void) {
    irState = IR_IDLE;
    lastFrameValid = 0; // Crucial: This prevents the "Repeat" logic from being allowed
    repeatReady = 0;
}