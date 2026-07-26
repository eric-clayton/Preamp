#include "tone.h"
#include "display.h"
#include "buttons.h"
#include "storage.h"
#include "ui_manager.h"
#include "audio_control.h"
#include "mcc_generated_files\system\pins.h"

// The Tone module simply defines what it needs, it doesn't "command" the mode
const UI_Layout toneSubModeLayout = {
    .params = { &subLevelLeftKnob, &subEqKnob, &subPhaseKnob, &subLevelRightKnob, NULL, &subOuputKnob },
    .blinkLed = LED_TONE
};

void Tone_ButtonHandler(ButtonType button, ButtonEvent event) {
    if (event == BUTTON_EVENT_LONG_PRESS) {
        if (Button_GetExclusive() == BUTTON_TONE) {
            Button_ClearExclusive();
            UI_Manager_Reset(); // Just tell the UI Manager to go back to default
            Display_SetToneLED(isToneOn); // Restore the LED state based on the current tone value
        } else {
            Button_SetExclusive(BUTTON_TONE);
            UI_Manager_ApplyLayout(&toneSubModeLayout); // Provide the config
        }
    }
    if (event == BUTTON_EVENT_SHORT_PRESS)
    {
        if (Button_GetExclusive() == BUTTON_NONE)
        {
            ToggleTone();
            Storage_MarkDirty();
        }
    }
}

void Tone_Init(void) {
    Button_Subscribe(BUTTON_TONE, Tone_ButtonHandler);
}

// Apply the "State" - Call this whenever data is retrieved from storage
void Tone_LoadSettings(uint8_t tone) {
    isToneOn = tone;
    AudioControl_SetTone(isToneOn);
    Display_SetToneLED(isToneOn);
}
uint8_t GetToneValue(void)
{
    return isToneOn; 
}
void ToggleTone(void)
{
    isToneOn = isToneOn ? 0 : 1;
    Storage_MarkDirty();
    AudioControl_SetTone(isToneOn);
    Display_SetToneLED(isToneOn);
}  