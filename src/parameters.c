#include <stddef.h>
#include "parameters.h"
#include "display.h"
#include "digipot.h"
#include "subcontrol.h"

Parameter_t volumeKnob        = { 127, 254,  1,  5,   100,     0, false, false, DisplayVolume,           UpdateVolumeWipers};
Parameter_t balanceKnob       = { 127, 254,  4,  4,     8,     0, false, false, DisplayBalance,          UpdateVolumeWipers};
Parameter_t lfBoostKnob       = { 127, 254,  4,  4,    12,    -6, false, false, DisplayBoostCut,         UpdateLFBoostWipers};
Parameter_t hfBoostKnob       = { 127, 254,  4,  4,    12,    -6, false, false, DisplayBoostCut,         UpdateHFBoostWipers};
Parameter_t frequencyKnobLow  = { 127, 254,  4,  4,   977,    22, false, false, DisplayFreqLow,          UpdateLFFrequencyWipers};
Parameter_t frequencyKnobHigh = { 127, 254,  4,  4,   150,    10, false, false, DisplayFreqHigh,         UpdateHFFrequencyWipers};
Parameter_t QKnobLow          = { 127, 254,  4,  4,     9,     1, false, false, DisplayQ,                UpdateLFQWipers};
Parameter_t QKnobHigh         = { 127, 254,  4,  4,     9,     1, false, false, DisplayQ,                UpdateHFQWipers};
// Sub
Parameter_t subPhaseKnob      = {   0, 254,  4,  4,     2,     0, false, false, DisplaySubEnableDisable, UpdateSubEnable};
Parameter_t subEqKnob         = {   0, 254,  4,  4,     1,     0, false, false, DisplaySubEQ,            UpdateSubEQ};
Parameter_t subLevelLeftKnob  = {   0, 254,  4,  4,    99,     0, false, false, DisplaySubLevelLeft,     UpdateSubLevelWipers};
Parameter_t subLevelRightKnob = {   0, 254,  4,  4,    99,     0, false, false, DisplaySubLevelRight,    UpdateSubLevelWipers};
// Power
Parameter_t inputOneOnKnob    = {   0, 254,  1,  1,    30,     0, false, false, DisplayPowerDelayOn,     NULL};
Parameter_t inputOneOffKnob   = {   0, 254,  1,  1,    100,     0, false,  true, DisplayPowerDelayOff,    NULL};
Parameter_t inputTwoOnKnob    = {   0, 254,  1,  1,    30,     0, false, false, DisplayPowerDelayOn,     NULL};
Parameter_t inputTwoOffKnob   = {   0, 254,  1,  1,    100,     0, false,  true, DisplayPowerDelayOff,    NULL};
Parameter_t inputThreeOnKnob  = {   0, 254,  1,  1,    30,     0, false, false, DisplayPowerDelayOn,     NULL};
Parameter_t inputThreeOffKnob = {   0, 254,  1,  1,    100,     0, false,  true, DisplayPowerDelayOff,    NULL};
Parameter_t inputBtOnKnob     = {   0, 254,  1,  1,    30,     0, false, false, DisplayPowerDelayOn,     NULL};
Parameter_t inputBtOffKnob    = {   0, 254,  1,  1,    100,     0, false,  true, DisplayPowerDelayOff,    NULL};

// The Master Array for looping
Parameter_t* allParameters[] = {
    &volumeKnob, &balanceKnob, &lfBoostKnob, &frequencyKnobHigh, &QKnobHigh,
    &frequencyKnobLow, &QKnobLow, &hfBoostKnob, &subPhaseKnob, &subEqKnob,
    &subLevelLeftKnob, &subLevelRightKnob, &inputOneOnKnob, &inputOneOffKnob,
    &inputTwoOnKnob, &inputTwoOffKnob, &inputThreeOnKnob, &inputThreeOffKnob,
    &inputBtOnKnob, &inputBtOffKnob
};

int16_t Parameter_Interpolate(Parameter_t *param) {
    return (int16_t)(((uint32_t)param->value * param->displayRange + 127) / 254) + param->displayOrigin;
}

void Parameter_Display(Parameter_t *param) {
    param->_display(Parameter_Interpolate(param));
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