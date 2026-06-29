#include "ui_manager.h"
#include "rotoryenc.h"
#include "systick.h"
#include "storage.h"
#include <stddef.h>

#define DISPLAY_TIMEOUT 4000
#define BLINK_INTERVAL 250 // Moved here from the old buttons.c

Parameter_t* activeDisplay2Encoder = &volumeKnob;
Parameter_t* activeParameters[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
uint32_t display2Timer = 0;
bool isShowingBaseEQ = true;


static LEDType activeBlinkLed = LED_NONE;
static uint32_t lastBlinkTime = 0;

// ... (other variables like activeParameters) ...
void Mode_SetEncoderLayout(Parameter_t* p0, Parameter_t* p1, Parameter_t* p2, Parameter_t* p3, Parameter_t* p4, Parameter_t* p5) {
    activeParameters[0] = p0;
    activeParameters[1] = p1;
    activeParameters[2] = p2;
    activeParameters[3] = p3;
    activeParameters[4] = p4;
    activeParameters[5] = p5;
}

void UI_Manager_ApplyLayout(const UI_Layout* layout) {
    // 1. Update params
    for(int i=0; i<6; i++) activeParameters[i] = layout->params[i];
    
    // 2. Update Blink State
    activeBlinkLed = layout->blinkLed;
    Display_SetBlinkBitIndex(activeBlinkLed); 
    Parameter_Display(activeParameters[0]);
}

void UI_Manager_Reset() {
    isShowingBaseEQ = true;
    Mode_SetEncoderLayout(&lfBoostKnob, &frequencyKnobLow, &QKnobLow, &hfBoostKnob, &balanceKnob, &volumeKnob);
    
    // Reset Blink State
    activeBlinkLed = LED_NONE;
    Display_SetBlinkBitIndex(LED_NONE);
    
    Parameter_Display(&volumeKnob);
    Parameter_Display(&lfBoostKnob);
    activeDisplay2Encoder = &volumeKnob;
}

// New function to replace the old HandleLEDBlink
void UI_Manager_HandleBlink() {
    if (activeBlinkLed == LED_NONE) return; // Nothing to blink

    if (systemTicks - lastBlinkTime >= BLINK_INTERVAL) {
        Display_BlinkLED();
        lastBlinkTime = systemTicks;
    }
}

// Swaps to high freq EQ (called internally)
void Mode_SwitchToHighEQ() {
    isShowingBaseEQ = true;
    Mode_SetEncoderLayout(&lfBoostKnob, &frequencyKnobHigh, &QKnobHigh, &hfBoostKnob, &balanceKnob, &volumeKnob);
}

void UpdateEncoders() {
    for(uint8_t i = 0; i < 6; i++) {
        // Only process if a parameter is assigned to this physical knob
        if(activeParameters[i] != NULL && ROTARYENC_Process(&physicalKnobs[i], activeParameters[i], systemTicks)) {
            
            Parameter_t* current = activeParameters[i];
            
            // Base mode switching logic
            if (current == &lfBoostKnob) UI_Manager_Reset();
            else if (current == &hfBoostKnob) Mode_SwitchToHighEQ();
            else if (current == &balanceKnob || current == &volumeKnob) {
                activeDisplay2Encoder = current;
                display2Timer = systemTicks;
            }

            current->isDirty = true;
            Parameter_Display(current);
            Parameter_Update(current);
            Storage_MarkDirty();
        }
    }
    
    // Timeout for volume display
    if (isShowingBaseEQ && activeDisplay2Encoder != &volumeKnob) {
        if ((systemTicks - display2Timer) >= DISPLAY_TIMEOUT) {
            Parameter_Display(&volumeKnob);
            activeDisplay2Encoder = &volumeKnob;
        }
    }
}