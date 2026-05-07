// mute.c
#include "mute.h"
#include "mcc_generated_files\system\pins.h"

#define MUTE_TIMEOUT 2000
extern volatile uint32_t systemTicks;

typedef struct {
    bool shouldUnmute;
    uint32_t unmuteStartTime;
} UnmuteState;

static UnmuteState unmuteState = {false, 0};

void Mute_Engage(void) {
    IO_MUTE_SetHigh();
    unmuteState.shouldUnmute = false;
}

void Mute_ScheduleRelease(void) {
    unmuteState.unmuteStartTime = systemTicks;
    unmuteState.shouldUnmute   = true;
}

void Mute_Update(void) {
    if (unmuteState.shouldUnmute &&
       (systemTicks - unmuteState.unmuteStartTime) >= MUTE_TIMEOUT) {
        IO_MUTE_SetLow();
        unmuteState.shouldUnmute = false;
    }
}