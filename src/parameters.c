#include <stddef.h>
#include "parameters.h"
#include "display.h"
#include "digipot.h"
#include "subcontrol.h"
#include "balance.h"

static bool balanceWasCentered = false;

Parameter_t volumeKnob        = { -325, -810,  155,   5,  25, false, false, false, DisplayVolume,           UpdateVolumeWipers,      PARAM_STORAGE_2_BYTES};
Parameter_t balanceKnob       = { BAL_START, BAL_MIN, BAL_MAX, 1, 1, false, false, false, DisplayBalance, UpdateOutputWipers,       PARAM_STORAGE_1_BYTE};
Parameter_t lfBoostKnob       = {    0,  -90,   90,   1,   1, true,  false, false, DisplayBoostCut,         UpdateLFBoostWipers,     PARAM_STORAGE_1_BYTE};
Parameter_t hfBoostKnob       = {    0,  -90,   90,   1,   1, true,  false, false, DisplayBoostCut,         UpdateHFBoostWipers,     PARAM_STORAGE_1_BYTE};
Parameter_t frequencyKnobLow  = {  511,   22,  999,   4,   4, true,  false, false, DisplayFreqLow,          UpdateLFFrequencyWipers, PARAM_STORAGE_2_BYTES};
Parameter_t frequencyKnobHigh = {   85,   10,  160,   1,   2, true,  false, false, DisplayFreqHigh,         UpdateHFFrequencyWipers, PARAM_STORAGE_1_BYTE};
Parameter_t QKnobLow          = {   60,   10,  100,   1,   1, true,  false, false, DisplayQ,                UpdateLFQWipers,         PARAM_STORAGE_1_BYTE};
Parameter_t QKnobHigh         = {   60,   10,  100,   1,   1, true,  false, false, DisplayQ,                UpdateHFQWipers,         PARAM_STORAGE_1_BYTE};
// Sub
Parameter_t subPhaseKnob      = {    0,    0, SUB_PHASE_MAX_VALUE, 1, 1, false, false, false, DisplaySubEnableDisable, UpdateSubEnable, PARAM_STORAGE_1_BYTE};
Parameter_t subEqKnob         = {    0,    0,    SUB_EQ_MAX_VALUE,   1,   1, false, false, false, DisplaySubEQ,            UpdateSubEQ,             PARAM_STORAGE_1_BYTE};
Parameter_t subLevelKnob       = {    0,  -60,   60,   1,   2, false, false, false, DisplaySubLevel,        UpdateSubLevelWipers,    PARAM_STORAGE_1_BYTE};
Parameter_t subOuputKnob      = {    5,    5,   25,   1,   1, false, false, false, DisplayOutputGain,       UpdateOutputWipers,      PARAM_STORAGE_1_BYTE};
// Inputs
Parameter_t inputOneOnKnob    = {    0,    0,   30,   1,   1, false, false, false, DisplayPowerDelayOn,     NULL,                   PARAM_STORAGE_1_BYTE};
Parameter_t inputOneOffKnob   = {    0,    0,  100,   1,   1, false, false,  true, DisplayPowerDelayOff,    NULL,                   PARAM_STORAGE_1_BYTE};
Parameter_t inputOneGainKnob  = {   15,    5,   25,   1,   1, false, false, false, DisplayInputGain,        UpdateInputGainWipers,  PARAM_STORAGE_1_BYTE};
Parameter_t inputTwoOnKnob    = {    0,    0,   30,   1,   1, false, false, false, DisplayPowerDelayOn,     NULL,                   PARAM_STORAGE_1_BYTE};
Parameter_t inputTwoOffKnob   = {    0,    0,  100,   1,   1, false, false,  true, DisplayPowerDelayOff,    NULL,                   PARAM_STORAGE_1_BYTE};
Parameter_t inputTwoGainKnob  = {   15,    5,   25,   1,   1, false, false, false, DisplayInputGain,        UpdateInputGainWipers,  PARAM_STORAGE_1_BYTE};
Parameter_t inputThreeOnKnob  = {    0,    0,   30,   1,   1, false, false, false, DisplayPowerDelayOn,     NULL,                   PARAM_STORAGE_1_BYTE};
Parameter_t inputThreeOffKnob = {    0,    0,  100,   1,   1, false, false,  true, DisplayPowerDelayOff,    NULL,                   PARAM_STORAGE_1_BYTE};
Parameter_t inputThreeGainKnob= {   15,    5,   25,   1,   1, false, false, false, DisplayInputGain,        UpdateInputGainWipers,  PARAM_STORAGE_1_BYTE};
Parameter_t inputBtOnKnob     = {    0,    0,   30,   1,   1, false, false, false, DisplayPowerDelayOn,     NULL,                   PARAM_STORAGE_1_BYTE};
Parameter_t inputBtOffKnob    = {    0,    0,  100,   1,   1, false, false,  true, DisplayPowerDelayOff,    NULL,                   PARAM_STORAGE_1_BYTE};
Parameter_t inputBtGainKnob   = {   15,    5,   25,   1,   1, false, false, false, DisplayInputGain,        UpdateInputGainWipers,  PARAM_STORAGE_1_BYTE};

// The Master Array for looping
Parameter_t* allParameters[] = {
    &volumeKnob, &balanceKnob, &lfBoostKnob, &frequencyKnobHigh, &QKnobHigh,
    &frequencyKnobLow, &QKnobLow, &hfBoostKnob, &subPhaseKnob, &subEqKnob,
    &subLevelKnob, &subOuputKnob, &inputOneOnKnob, &inputOneOffKnob, &inputOneGainKnob,
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
    if (Balance_Offset(balanceKnob.value) == 0)
        balanceKnob.value = BAL_START;
    for(int i = 0; i < PARAM_COUNT; i++)
    {
        Parameter_Update(allParameters[i]);
    }
}
// Balance: landing in the center hold from outside jumps to the middle of it
static int16_t Balance_Snap(int16_t oldValue, int16_t newValue)
{
    if (Balance_Offset(oldValue) != 0 && Balance_Offset(newValue) == 0)
        return BAL_START;
    return newValue;
}

void Parameter_Adjust(Parameter_t *param, int8_t direction, bool fast)
{
    int     stepSize = fast ? param->fastStep : param->slowStep;
    int32_t newValue = (int32_t)param->value + (direction * stepSize);
    int16_t oldValue = param->value;

    if (newValue > param->maxValue)
        param->value = param->isLooping ? param->minValue : param->maxValue;
    else if (newValue < param->minValue)
        param->value = param->isLooping ? param->maxValue : param->minValue;
    else
        param->value = (int16_t)newValue;

    if (param == &balanceKnob)
        param->value = Balance_Snap(oldValue, param->value);
}