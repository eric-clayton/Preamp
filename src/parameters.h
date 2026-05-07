// parameters.h
#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <stdint.h>
#include <stdbool.h>

typedef struct Parameter_t {
    uint8_t value;
    uint8_t maxValue;
    uint8_t slowStep;
    uint8_t fastStep;
    uint32_t displayRange;
    int16_t displayOrigin;
    bool isDirty;
    bool isLooping;
    void (*_display)(int16_t value);
    void (*_update)(void);  
} Parameter_t;

#define PARAM_COUNT 20U

extern Parameter_t volumeKnob, balanceKnob;
extern Parameter_t lfBoostKnob, frequencyKnobLow, QKnobLow;
extern Parameter_t hfBoostKnob, frequencyKnobHigh, QKnobHigh;
extern Parameter_t subPhaseKnob, subEqKnob;
extern Parameter_t subLevelLeftKnob, subLevelRightKnob;
extern Parameter_t inputOneOnKnob,   inputOneOffKnob;
extern Parameter_t inputTwoOnKnob,   inputTwoOffKnob;
extern Parameter_t inputThreeOnKnob, inputThreeOffKnob;
extern Parameter_t inputBtOnKnob,    inputBtOffKnob;

extern Parameter_t* allParameters[PARAM_COUNT];

int16_t Parameter_Interpolate(Parameter_t *param);
void Parameter_Display(Parameter_t *param);
void Parameter_Update(Parameter_t *param);
void Parameters_Initialize(void);

#endif