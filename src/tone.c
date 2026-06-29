#include "tone.h"
#include "display.h"
#include "buttons.h"
#include "storage.h"
#include "ui_manager.h"
#include "mcc_generated_files\system\pins.h"

// The Tone module simply defines what it needs, it doesn't "command" the mode
const UI_Layout toneSubModeLayout = {
    .params = { &subLevelLeftKnob, &subEqKnob, &subPhaseKnob, &subLevelRightKnob, NULL, NULL },
    .blinkLed = LED_TONE
};

void Tone_ButtonHandler(ButtonType button, ButtonEvent event) {
    if (event == BUTTON_EVENT_LONG_PRESS) {
        if (Button_GetExclusive() == BUTTON_TONE) {
            UI_Manager_Reset(); // Just tell the UI Manager to go back to default
        } else {
            Button_SetExclusive(BUTTON_TONE);

            UI_Manager_ApplyLayout(&toneSubModeLayout); // Provide the config
        }
    }
    if (event == BUTTON_EVENT_SHORT_PRESS)
    {
        ToggleTone();
        Storage_MarkDirty();
    }
}

void Tone_Init(void) {
    Button_Subscribe(BUTTON_TONE, Tone_ButtonHandler);
}

// Apply the "State" - Call this whenever data is retrieved from storage
void Tone_LoadSettings(uint8_t tone) {
    isToneOn = tone;
    Display_SetToneLED(GetToneValue());
}
uint8_t GetToneValue(void)
{
    return isToneOn; 
}
void ToggleTone(void)
{
    isToneOn = isToneOn ? 0 : 1;
    Display_SetToneLED(GetToneValue());
}  