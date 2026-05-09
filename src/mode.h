#ifndef MODE_H
#define MODE_H

#include "parameters.h"

typedef enum {
    MODE_FREQ_LOW, MODE_FREQ_HIGH, MODE_SUB,
    MODE_INPUT_ONE_POWER, MODE_INPUT_TWO_POWER,
    MODE_INPUT_THREE_POWER, MODE_INPUT_BT_POWER
} SystemMode;

extern SystemMode currentSystemMode;
extern Parameter_t* activeDisplay2Encoder;
extern Parameter_t* activeParameters[6];
extern uint32_t display2Timer;

void SwitchMode(SystemMode newMode);
void UpdateEncoders(void);
void InitializeNormalMode(void);
void InitializeSubSettingModes(SystemMode mode);

#endif