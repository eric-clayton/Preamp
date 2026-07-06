#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H

#include <stdint.h>

// 74HC595 (digital output expander) and ADG1414 (SSWCS, analog switch
// cascade). Both are full-word shift registers: there is no per-bit
// addressing on the wire, so "not affecting other bits" is enforced in
// software via a shadow register + mask, then the ENTIRE word is shifted
// out and latched. See apply_bits().

// ---- 74HC595 output expander bit masks ----
#define IO_DIS_MASK    ((uint16_t)0x0002U)
#define DV1_MASK      ((uint16_t)0x0020U)
#define DV2_MASK      ((uint16_t)0x0040U)
#define DV3_MASK      ((uint16_t)0x0080U)
#define SUBEN_MASK    ((uint16_t)0x0100U)
#define PP_MASK       ((uint16_t)0x0200U)
#define NEXT_MASK     ((uint16_t)0x0400U)
#define PREV_MASK     ((uint16_t)0x0800U)
#define ISA_MASK      ((uint16_t)0x1000U)
#define ISB_MASK      ((uint16_t)0x2000U)
#define DVBT_MASK     ((uint16_t)0x4000U)
#define TONE_MASK     ((uint16_t)0x8000U)

// ---- ADG1414 (SSWCS) switch bit assignments ----
// NOTE: confirm these against actual S1..S8 PCB wiring before relying on them.
#define BIT(n) (1u << (n))
#define S1AB BIT(0)
#define S2AB BIT(1)
#define S3AB BIT(2)
#define S4AB BIT(3)
#define S5AB BIT(4)
#define S6AB BIT(5)
#define S7AB BIT(6)
#define S8AB BIT(7)

typedef struct {
    uint16_t mask;
    uint16_t value;
} switch_condition_t;

// Sub-control conditions, per SSWCS truth table
extern const switch_condition_t SUB_EQ_ENA;
extern const switch_condition_t SUB_EQ_DIS;
extern const switch_condition_t PHASE_180;
extern const switch_condition_t PHASE_0;
extern const switch_condition_t PHASE_CORRECT;
extern const switch_condition_t PHASE_INCORRECT;
extern const switch_condition_t SUB_MUTE;
extern const switch_condition_t SUB_UNMUTE;

// Shadow registers -- single source of truth for output state. Hardware
// can't be read back; these in-RAM copies are authoritative.
extern uint16_t hc595_shadow;   // 74HC595 cascade (digital)
extern uint16_t sswcs_shadow;   // ADG1414 cascade (analog switches)

// Apply a masked update without touching unrelated bits in a shadow word.
void apply_bits(uint16_t *shadow, uint16_t mask, uint16_t value);

// Push the full shadow word out over SPI and latch it.
void WriteRegister(void);        // flushes hc595_shadow  -> output expander
void WriteRegisterAnalog(void);  // flushes sswcs_shadow   -> SSWCS / ADG1414

// Convenience wrappers: modify shadow bit(s) then flush.
void SetExpanderRegister(uint16_t bitMask, uint8_t value);
void ToggleExpanderRegister(uint16_t bitMask);

#endif
