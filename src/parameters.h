// parameters.h
#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <stdint.h>
#include <stdbool.h>

#define WIPER_MIN 0
#define WIPER_MAX 254
typedef struct Parameter_t {
    int16_t value;      // current value, in DISPLAY units directly (no more raw pot units)
    int16_t minValue;   // minimum value, in display units
    int16_t maxValue;   // maximum value, in display units
    int slowStep;        // amount to add/subtract per slow click, in display units
    int fastStep;        // amount to add/subtract per fast click, in display units
    bool inverted;        // true if wiper is wired backwards: minValue->254, maxValue->0
    bool isDirty;
    bool isLooping;
    void (*_display)(int16_t value);
    void (*_update)(void);
} Parameter_t;

#define PARAM_COUNT 25U

extern Parameter_t volumeKnob, balanceKnob;
extern Parameter_t lfBoostKnob, frequencyKnobLow, QKnobLow;
extern Parameter_t hfBoostKnob, frequencyKnobHigh, QKnobHigh;
extern Parameter_t subPhaseKnob, subEqKnob;
extern Parameter_t subLevelLeftKnob, subLevelRightKnob;
extern Parameter_t subOuputKnob;
extern Parameter_t inputOneOnKnob,   inputOneOffKnob, inputOneGainKnob;
extern Parameter_t inputTwoOnKnob,   inputTwoOffKnob, inputTwoGainKnob;
extern Parameter_t inputThreeOnKnob, inputThreeOffKnob, inputThreeGainKnob;
extern Parameter_t inputBtOnKnob,   inputBtOffKnob, inputBtGainKnob;

extern Parameter_t* allParameters[PARAM_COUNT];

void Parameter_Display(Parameter_t *param);
void Parameter_Update(Parameter_t *param);
void Parameters_Initialize(void);
void Parameter_Adjust(Parameter_t *param, int8_t direction, bool fast);

#endif