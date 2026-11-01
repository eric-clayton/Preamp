#ifndef ROTORYENC_H
#define	ROTORYENC_H

#include <stdbool.h>
#include <stdint.h>
#include "parameters.h"

#define KNOB_COUNT 6

typedef struct { uint8_t RCA; uint8_t RCB;} RCValues;

typedef struct {
    RCValues (*ReadHardware)(void); // Pointer to the functions above
    uint8_t lastState;
    int8_t lastDirection;
    uint32_t lastChangeTime;
} PhysicalKnob_t;

extern PhysicalKnob_t physicalKnobs[KNOB_COUNT];

void ROTARYENC_Initialize(void);
void ROTARYENC_UpdateLastState(PhysicalKnob_t *hw);
int8_t ROTARYENC_Read(PhysicalKnob_t *hw, uint32_t systemTicks, bool *fast);


#endif

