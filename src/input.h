// input.h
#ifndef INPUT_H
#define INPUT_H

#include "parameters.h"
#include "display.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    INPUT_ONE,
    INPUT_TWO,
    INPUT_THREE,
    INPUT_BT,
    INPUT_NONE
} InputType;

typedef struct {
    Parameter_t *powerOnDelay;
    Parameter_t *powerOffDelay;
    uint32_t powerOffStartTime;
    uint32_t powerOnStartTime;
    bool (*IsOn)(void);
    void (*TogglePower)(void);
} InputState;

extern InputState inputOne, inputTwo, inputThree, inputBt;
extern InputState *inputs[];
extern bool isAnyInputInPowerDelay;

LEDType MapInputTypeToLedType(InputType button);
void Input_LoadSettings(InputType inputType);
void Input_Init(void);
void InputSwitch(InputType inputType) ;
void HandleInputSwitchPower(void);
InputType GetInputType(void);

#endif