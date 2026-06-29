#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "parameters.h"
#include "display.h"

typedef enum {
    MODE_FREQ_LOW, MODE_FREQ_HIGH, MODE_SUB,
    MODE_INPUT_ONE_POWER, MODE_INPUT_TWO_POWER,
    MODE_INPUT_THREE_POWER, MODE_INPUT_BT_POWER
} SystemMode;

typedef struct {
    Parameter_t* params[6];
    LEDType blinkLed;
} UI_Layout;

extern SystemMode currentSystemMode;
extern Parameter_t* activeDisplay2Encoder;
extern Parameter_t* activeParameters[6];
extern uint32_t display2Timer;

void SwitchMode(SystemMode newMode);
void UpdateEncoders(void);
void UI_Manager_Reset(void);
void UI_Manager_ApplyLayout(const UI_Layout* layout);
void UI_Manager_HandleBlink(void);

#endif