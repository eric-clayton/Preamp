#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdbool.h>

#define BUTTON_ALL 0xFF 

typedef enum {
    BUTTON_INPUT_ONE, BUTTON_INPUT_TWO,
    BUTTON_INPUT_THREE, BUTTON_INPUT_BT, 
    BUTTON_TONE, BUTTON_PREV, BUTTON_PAUSE, BUTTON_NEXT, BUTTON_NONE
} ButtonType;

typedef enum {
    BUTTON_EVENT_SHORT_PRESS,
    BUTTON_EVENT_LONG_PRESS
} ButtonEvent;

// Function pointer signature for subscribers
typedef void (*ButtonEventHandler)(ButtonType button, ButtonEvent event);

// Allows external modules to listen to button events
// Optional: Add a wild-card if you ever need a module to listen to everything


// Change the subscribe function to accept the specific button it wants
void Button_Subscribe(ButtonType buttonToWatch, ButtonEventHandler handler);

void HandleButtonPressed(void);
void UpdateButton(void);
void CheckIfLongPress(void);
void Button_SetExclusive(ButtonType button);
void Button_ClearExclusive(void);
ButtonType Button_GetExclusive(void);

#endif // BUTTONS_H