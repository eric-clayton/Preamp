#include "bluetooth.h"
#include "buttons.h"
#include "audio_control.h"
#include "display.h"
#include "input.h"
#include "mcc_generated_files/system/pins.h"

static bool btStatusLedState;

void ButtonHandler(ButtonType button, ButtonEvent event)
{
    bool pressed;
    if (event == BUTTON_EVENT_PRESSED)
        pressed = true;
    else if (event == BUTTON_EVENT_RELEASED)
        pressed = false;
    else
        return;

    bool commandActive = pressed && GetInputType() == INPUT_BT;

    switch (button) {
        case BUTTON_PREV:
            BluetoothPrev(commandActive);
            Display_ShowBluetoothCommand(DISPLAY_BT_PREV, commandActive);
            break;
        case BUTTON_PAUSE:
            BluetoothPause(commandActive);
            Display_ShowBluetoothCommand(DISPLAY_BT_PAUSE, commandActive);
            break;
        case BUTTON_NEXT:
            BluetoothNext(commandActive);
            Display_ShowBluetoothCommand(DISPLAY_BT_NEXT, commandActive);
            break;
        default:
            break;
    }
}

void Bluetooth_Init()
{
    Button_Subscribe(BUTTON_PREV, ButtonHandler);
    Button_Subscribe(BUTTON_PAUSE, ButtonHandler);
    Button_Subscribe(BUTTON_NEXT, ButtonHandler);

    BluetoothPrev(false);
    BluetoothPause(false);
    BluetoothNext(false);

    btStatusLedState = BLED_GetValue() != 0;
    Display_SetBTStatusLED(btStatusLedState);
}

void Bluetooth_Update(void)
{
    bool bledState = BLED_GetValue() != 0;
    if (bledState != btStatusLedState) {
        btStatusLedState = bledState;
        Display_SetBTStatusLED(btStatusLedState);
    }
}