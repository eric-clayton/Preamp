#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    BUTTON_INPUT_ONE, BUTTON_INPUT_TWO,
    BUTTON_INPUT_THREE, BUTTON_INPUT_BT, 
    BUTTON_TONE, BUTTON_NONE
} ButtonType;

typedef struct {
    bool isCurrentlyPressed;
    bool isSubMode;
    bool longPressInitialized;
    uint32_t pressStartTime;
    uint32_t lastBlinkTime;
} ButtonState_t;

extern ButtonType activeButton;
extern ButtonState_t longPressState;
extern volatile bool buttonEventPending;

void HandleButtonPressed(void);
void UpdateButton(void);
void HandleLongPress(void);
void HandleLEDBlink(void);

#endif