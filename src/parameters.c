#include <stddef.h>
#include "parameters.h"
#include "display.h"
#include "digipot.h"
#include "subcontrol.h"

Parameter_t volumeKnob        = { -325, -810,  155,   5,  25, false, false, false, DisplayVolume,           UpdateVolumeWipers};
Parameter_t balanceKnob       = {    4,    0,    8,   1,   1, false, false, false, DisplayBalance,          UpdateOutputWipers};
Parameter_t lfBoostKnob       = {    0,  -60,   60,   1,   1, false, false, false, DisplayBoostCut,         UpdateLFBoostWipers};
Parameter_t hfBoostKnob       = {    0,  -60,   60,   1,   1, false, false, false, DisplayBoostCut,         UpdateHFBoostWipers};
Parameter_t frequencyKnobLow  = {  511,   22,  999,   4,   4, false, false, false, DisplayFreqLow,          UpdateLFFrequencyWipers};
Parameter_t frequencyKnobHigh = {   85,   10,  160,   1,   2, false, false, false, DisplayFreqHigh,         UpdateHFFrequencyWipers};
Parameter_t QKnobLow          = {    6,    1,   10,   1,   1, false, false, false, DisplayQ,                UpdateLFQWipers};
Parameter_t QKnobHigh         = {    6,    1,   10,   1,   1, false, false, false, DisplayQ,                UpdateHFQWipers};
// Sub
Parameter_t subPhaseKnob      = {    0,    0,    2,   1,   1, false, false, false, DisplaySubEnableDisable, UpdateSubEnable};
Parameter_t subEqKnob         = {    0,    0,    1,   1,   1, false, false, false, DisplaySubEQ,            UpdateSubEQ};
Parameter_t subLevelLeftKnob  = {    0,    0,   99,   2,   2, false, false, false, DisplaySubLevelLeft,     UpdateSubLevelWipers};
Parameter_t subLevelRightKnob = {    0,    0,   99,   2,   2, false, false, false, DisplaySubLevelRight,    UpdateSubLevelWipers};
Parameter_t subOuputKnob      = {    5,    5,   25,   1,   1, false, false, false, DisplayOutputGain,       UpdateOutputWipers};
// Inputs
Parameter_t inputOneOnKnob    = {    0,    0,   30,   1,   1, false, false, false, DisplayPowerDelayOn,     NULL};
Parameter_t inputOneOffKnob   = {    0,    0,  100,   1,   1, false, false,  true, DisplayPowerDelayOff,    NULL};
Parameter_t inputOneGainKnob  = {   15,    5,   25,   1,   1, false, false, false, DisplayInputGain,        UpdateInputOneGainWipers};
Parameter_t inputTwoOnKnob    = {    0,    0,   30,   1,   1, false, false, false, DisplayPowerDelayOn,     NULL};
Parameter_t inputTwoOffKnob   = {    0,    0,  100,   1,   1, false, false,  true, DisplayPowerDelayOff,    NULL};
Parameter_t inputTwoGainKnob  = {   15,    5,   25,   1,   1, false, false, false, DisplayInputGain,        UpdateInputTwoGainWipers};
Parameter_t inputThreeOnKnob  = {    0,    0,   30,   1,   1, false, false, false, DisplayPowerDelayOn,     NULL};
Parameter_t inputThreeOffKnob = {    0,    0,  100,   1,   1, false, false,  true, DisplayPowerDelayOff,    NULL};
Parameter_t inputThreeGainKnob= {   15,    5,   25,   1,   1, false, false, false, DisplayInputGain,        UpdateInputThreeGainWipers};
Parameter_t inputBtOnKnob     = {    0,    0,   30,   1,   1, false, false, false, DisplayPowerDelayOn,     NULL};
Parameter_t inputBtOffKnob    = {    0,    0,  100,   1,   1, false, false,  true, DisplayPowerDelayOff,    NULL};
Parameter_t inputBtGainKnob   = {   15,    5,   25,   1,   1, false, false, false, DisplayInputGain,        UpdateInputBtGainWipers};

// The Master Array for looping
Parameter_t* allParameters[] = {
    &volumeKnob, &balanceKnob, &lfBoostKnob, &frequencyKnobHigh, &QKnobHigh,
    &frequencyKnobLow, &QKnobLow, &hfBoostKnob, &subPhaseKnob, &subEqKnob,
    &subLevelLeftKnob, &subLevelRightKnob, &subOuputKnob, &inputOneOnKnob, &inputOneOffKnob, &inputOneGainKnob,
    &inputTwoOnKnob, &inputTwoOffKnob, &inputTwoGainKnob, &inputThreeOnKnob, &inputThreeOffKnob, &inputThreeGainKnob,
    &inputBtOnKnob, &inputBtOffKnob, &inputBtGainKnob
};

uint8_t Parameter_GetWiperValue(Parameter_t *param) {
    int32_t range = (int32_t)param->maxValue - param->minValue;
    if (range <= 0) return 0; // misconfigured knob guard

    int32_t offset = (int32_t)param->value - param->minValue;
    if (offset < 0) offset = 0;
    if (offset > range) offset = range;

    int32_t wiperPos = (offset * WIPER_MAX + (range / 2)) / range;

    return param->inverted ? (uint8_t)(WIPER_MAX - wiperPos) : (uint8_t)wiperPos;
}
void Parameter_Display(Parameter_t *param) {
    param->_display(param->value);
}

void Parameter_Update(Parameter_t *param) {
    if (param->_update != NULL)
        param->_update();
}
void Parameters_Initialize(void)
{
    for(int i = 0; i < PARAM_COUNT; i++)
    {
        Parameter_Update(allParameters[i]);
    }
}