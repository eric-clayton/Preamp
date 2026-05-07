#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    NONE, TONE_BUTTON,
    INPUT_ONE_BUTTON, INPUT_TWO_BUTTON,
    INPUT_THREE_BUTTON, INPUT_BT_BUTTON
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
extern uint8_t lightMap;
extern volatile bool buttonEventPending;

void HandleButtonPressed(void);
void UpdateButton(void);
void HandleLongPress(void);
void HandleLEDBlink(void);
uint8_t GetDisplayButtonBit(ButtonType button);

#endif