#include "bluetooth.h"
#include "buttons.h"
#include "audio_control.h"
void ButtonHandler(ButtonType button, ButtonEvent event)
{
    if(event == BUTTON_EVENT_SHORT_PRESS)
    {
        switch(button)
        {
            case BUTTON_PREV:
                BluetoothPrev();
                break;
            case BUTTON_PAUSE:
                BluetoothPause();
                break;
            case BUTTON_NEXT:
                BluetoothNext();
                break;
            default:
                return;
        }
    }
}
void Bluetooth_Init()
{
    Button_Subscribe(BUTTON_PREV, ButtonHandler);
    Button_Subscribe(BUTTON_PAUSE, ButtonHandler);
    Button_Subscribe(BUTTON_NEXT, ButtonHandler);
}