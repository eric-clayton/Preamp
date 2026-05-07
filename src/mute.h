// mute.h
#ifndef MUTE_H
#define MUTE_H

#include <stdbool.h>

void Mute_Engage(void);               // Sets mute high, clears shouldUnmute
void Mute_ScheduleRelease(void); // Arms the timer
void Mute_Update(void);               // Called every loop tick, releases when ready

#endif