#include "audio_control.h"
#include "shift_register.h"
#include <xc.h>
#include "mcc_generated_files\system\clock.h"

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

void BluetoothPrev(void)
{
    ToggleExpanderRegister(PREV_MASK);
    __delay_ms(10);
    ToggleExpanderRegister(PREV_MASK);
}
void BluetoothPause(void)
{
    ToggleExpanderRegister(PP_MASK);
    __delay_ms(10);
    ToggleExpanderRegister(PP_MASK);
}
void BluetoothNext(void)
{
    ToggleExpanderRegister(NEXT_MASK);
    __delay_ms(10);
    ToggleExpanderRegister(NEXT_MASK);
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
    const switch_condition_t *c = enabled ? &SUB_EQ_ENA : &SUB_EQ_DIS;
    apply_bits(&sswcs_shadow, c->mask, c->value);
    WriteRegisterAnalog();
}

void SetSubPhase(bool inverted)
{
    const switch_condition_t *c = inverted ? &PHASE_180 : &PHASE_0;
    apply_bits(&sswcs_shadow, c->mask, c->value);
    WriteRegisterAnalog();
}
void SetIODisabled(bool disabled)
{
    SetExpanderRegister(IO_DIS_MASK, disabled ? 1 : 0);
}
void SetPhaseCorrect(bool phaseCorrect)
{
    const switch_condition_t *c = phaseCorrect ? &PHASE_CORRECT : &PHASE_INCORRECT;
    apply_bits(&sswcs_shadow, c->mask, c->value);
    WriteRegisterAnalog();
}
void SetSubMute(bool muted)
{
    const switch_condition_t *c = muted ? &SUB_MUTE : &SUB_UNMUTE;
    apply_bits(&sswcs_shadow, c->mask, c->value);
    WriteRegisterAnalog();
}

bool IsInputOneExpanderBitSet(void)   { return (hc595_shadow & DV1_MASK) != 0; }
bool IsInputTwoExpanderBitSet(void)   { return (hc595_shadow & DV2_MASK) != 0; }
bool IsInputThreeExpanderBitSet(void) { return (hc595_shadow & DV3_MASK) != 0; }
bool IsInputBTExpanderBitSet(void)    { return (hc595_shadow & DVBT_MASK) != 0; }
