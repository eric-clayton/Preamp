#include "audio_control.h"
#include "shift_register.h"

void DV1_Toggle(void)  { ToggleExpanderRegister(DV1_MASK); }
void DV2_Toggle(void)  { ToggleExpanderRegister(DV2_MASK); }
void DV3_Toggle(void)  { ToggleExpanderRegister(DV3_MASK); }
void DVBT_Toggle(void) { ToggleExpanderRegister(DVBT_MASK); }

void SetInputState(uint8_t ISB, uint8_t ISA)
{
    apply_bits(&hc595_shadow, ISA_MASK, ISA != 0 ? ISA_MASK : 0);
    apply_bits(&hc595_shadow, ISB_MASK, ISB != 0 ? ISB_MASK : 0);
    WriteRegister();
}

void BluetoothPrev(bool pressed)
{
    SetExpanderRegister(PREV_MASK, !pressed);
}
void BluetoothPause(bool pressed)
{
    SetExpanderRegister(PP_MASK, !pressed);
}
void BluetoothNext(bool pressed)
{
    SetExpanderRegister(NEXT_MASK, !pressed);
}

void AudioControl_SetTone(uint8_t tone)
{
    SetExpanderRegister(TONE_MASK, tone);
}
void SetSubEn(bool enabled)
{
    SetExpanderRegister(SUBEN_MASK, enabled ? 1 : 0);
}
void SetSubEQ(bool enabled)
{
    SetExpanderRegister(SEQ_MASK, enabled ? 1 : 0);
}

void SetSubPhase(bool inverted)
{
    SetExpanderRegister(PHINV_MASK, inverted ? 1 : 0);
}
void SetIODisabled(bool disabled)
{
    SetExpanderRegister(OUT_DIS_MASK, disabled ? 1 : 0);
}
void SetPhaseCorrect(bool phaseCorrect)
{
    SetExpanderRegister(PHADJ_MASK, phaseCorrect ? 1 : 0);
}
void SetSubMute(bool muted)
{
    SetSubEn(!muted);
}

bool IsInputOneExpanderBitSet(void)   { return (hc595_shadow & DV1_MASK) != 0; }
bool IsInputTwoExpanderBitSet(void)   { return (hc595_shadow & DV2_MASK) != 0; }
bool IsInputThreeExpanderBitSet(void) { return (hc595_shadow & DV3_MASK) != 0; }
bool IsInputBTExpanderBitSet(void)    { return (hc595_shadow & DVBT_MASK) != 0; }
