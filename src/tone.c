#include "tone.h"
#include "display.h"
#include "mcc_generated_files\system\pins.h"

void InitializeTone(uint8_t tone)
{
    if(tone)
    {
        IO_FEN_SetHigh();
    }
    else
    {
        IO_FEN_SetLow();
    }     
    Display_SetToneLED(GetToneValue());
}
uint8_t GetToneValue(void)
{
    return IO_FEN_PORT;
}
void ToggleTone(void)
{
    IO_FEN_Toggle();
    Display_SetToneLED(GetToneValue());
}  