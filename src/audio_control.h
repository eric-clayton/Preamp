#ifndef AUDIO_CONTROL_H
#define AUDIO_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

// Logic-level controls. Callers here don't need to know whether a feature
// is backed by the 74HC595 or the ADG1414 -- that detail lives entirely
// in shift_register.h/.c.

void DV1_Toggle(void);
void DV2_Toggle(void);
void DV3_Toggle(void);
void DVBT_Toggle(void);

void SetInputState(uint8_t ISB, uint8_t ISA);

void BluetoothPrev(void);
void BluetoothPause(void);
void BluetoothNext(void);

void AudioControl_SetTone(uint8_t tone);   // was Digipot_SetTone -- renamed,
                                            // this drives the 74HC595, not a digipot
void SetIODisabled(bool disabled);
void SetSubEn(bool enabled);
void SetSubEQ(bool enabled);
void SetSubPhase(bool inverted);
void SetPhaseCorrect(bool phaseCorrect);
void SetSubMute(bool muted);

bool IsInputOneExpanderBitSet(void);
bool IsInputTwoExpanderBitSet(void);
bool IsInputThreeExpanderBitSet(void);
bool IsInputBTExpanderBitSet(void);

#endif
