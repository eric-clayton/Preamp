#include "buttons.h"
#include "as1115.h"
#include "systick.h"

#define LONG_PRESS_MS 1500  // Duration for a "Long Press"
#define MAX_SUBSCRIBERS 10  // Adjust based on how many modules need to listen

// Struct to link a specific button to a handler
typedef struct {
    ButtonType watchedButton;
    ButtonEventHandler handler;
} Subscriber_t;

// --- Publisher / Subscriber State ---
static Subscriber_t subscribers[MAX_SUBSCRIBERS];
static uint8_t subscriberCount = 0;

// --- Physical Button State ---
ButtonType activeButton = BUTTON_NONE;
volatile bool buttonEventPending = false;

typedef struct {
    bool isCurrentlyPressed;
    bool longPressFired;
    uint32_t pressStartTime;
} ButtonState_t;

ButtonState_t pressState = {false, false, 0};

void Button_Subscribe(ButtonType buttonToWatch, ButtonEventHandler handler) {
    if (subscriberCount < MAX_SUBSCRIBERS) {
        subscribers[subscriberCount].watchedButton = buttonToWatch;
        subscribers[subscriberCount].handler = handler;
        subscriberCount++;
    }
}
static void PublishEvent(ButtonType button, ButtonEvent event) {
    for (uint8_t i = 0; i < subscriberCount; i++) {
        // Only trigger the handler if it matches the exact button, 
        // or if it was subscribed to BUTTON_ALL
        if (subscribers[i].watchedButton == button || subscribers[i].watchedButton == BUTTON_ALL) {
            subscribers[i].handler(button, event);
        }
    }
}

// --- Core Logic ---
void HandleButtonPressed() {
    buttonEventPending = true;
}
static ButtonType exclusiveButton = BUTTON_NONE;

void Button_SetExclusive(ButtonType button) { exclusiveButton = button; }
void Button_ClearExclusive(void) { exclusiveButton = BUTTON_NONE; }
ButtonType Button_GetExclusive(void) { return exclusiveButton; }

void UpdateButton() {
    if (!buttonEventPending) {
        return;
    }
    
    uint8_t readData[2];
    AS1115_ReadKeys(readData); 
   
    uint8_t pA = ~readData[0];
    uint8_t pB = ~readData[1];
    
    // 1. Determine what is physically being pressed right now
    ButtonType physicalButton = BUTTON_NONE;
    if (pA & (1 << 6))      physicalButton = BUTTON_TONE;
    else if (pB & (1 << 6)) physicalButton = BUTTON_INPUT_ONE;
    else if (pA & (1 << 5)) physicalButton = BUTTON_INPUT_TWO;
    else if (pB & (1 << 5)) physicalButton = BUTTON_INPUT_THREE;
    else if (pA & (1 << 4)) physicalButton = BUTTON_INPUT_BT;
    else if (pB & (1 << 5)) physicalButton = BUTTON_PREV;  // Note: Check bit map, previously shared (1<<5) with INPUT_THREE
    else if (pA & (1 << 3)) physicalButton = BUTTON_PAUSE;
    else if (pB & (1 << 3)) physicalButton = BUTTON_NEXT;

    if (exclusiveButton != BUTTON_NONE && physicalButton != exclusiveButton) {
        physicalButton = BUTTON_NONE; 
    }
    // 2. Handle State Changes
    if (physicalButton != BUTTON_NONE) {
        // FRESH TOUCH
        if (!pressState.isCurrentlyPressed) {
            pressState.isCurrentlyPressed = true;
            pressState.pressStartTime = systemTicks;
            pressState.longPressFired = false;
            activeButton = physicalButton;
        }
    } 
    else {
        // FINGER RELEASED
        if (pressState.isCurrentlyPressed) {
            // If released before a long press was triggered, it's a short press
            if (!pressState.longPressFired) {
                PublishEvent(activeButton, BUTTON_EVENT_SHORT_PRESS);
            }
            
            // Reset state
            pressState.isCurrentlyPressed = false;
            activeButton = BUTTON_NONE;
        }
    }
    
    buttonEventPending = false;
}

void CheckIfLongPress() {
    if (pressState.isCurrentlyPressed && !pressState.longPressFired) {
        // Check if this specific button is allowed to trigger a long press
        if ((systemTicks - pressState.pressStartTime) >= LONG_PRESS_MS) {
            
            // Mark as fired so releasing the button doesn't trigger a short press
            pressState.longPressFired = true; 
            
            // Broadcast the long press event to all listeners
            PublishEvent(activeButton, BUTTON_EVENT_LONG_PRESS);
        }
    }
}