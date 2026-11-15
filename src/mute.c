// mute.c
#include "mute.h"
#include "audio_control.h"
#include "mcc_generated_files\system\pins.h"
#include "systick.h"

#define MUTE_TIMEOUT 2000

typedef struct {
    bool shouldUnmute;
    uint32_t unmuteStartTime;
} UnmuteState;

static UnmuteState unmuteState = {false, 0};

void Mute_Engage(void) {
    SetSubMute(true);
    SetIODisabled(true);
    unmuteState.shouldUnmute = false;
}

void Mute_ScheduleRelease(void) {
    unmuteState.unmuteStartTime = SysTick_Now();
    unmuteState.shouldUnmute   = true;
}

void Mute_Update(void) {
    if (unmuteState.shouldUnmute &&
       (SysTick_Now() - unmuteState.unmuteStartTime) >= MUTE_TIMEOUT) {
        SetSubMute(false);
        SetIODisabled(false);
        unmuteState.shouldUnmute = false;
    }
}