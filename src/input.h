// input.h
#ifndef INPUT_H
#define INPUT_H

#include "parameters.h"
#include <stdbool.h>
#include <stdint.h>
#include "buttons.h"

typedef struct {
    Parameter_t *powerOnDelay;
    Parameter_t *powerOffDelay;
    uint32_t powerOffStartTime;
    uint32_t powerOnStartTime;
    bool (*IsOn)(void);
    void (*TogglePower)(void);
} InputState;

extern InputState inputOne, inputTwo, inputThree, inputBt;
extern InputState *currentInput;
extern InputState *inputs[];
extern bool isAnyInputInPowerDelay;

void InputSwitch(ButtonType button);
void HandleInputSwitchPower(void);

#endif