#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H

#include <stdint.h>

// The 74HC595 output expander is a full-word shift register: there is no
// per-bit addressing on the wire, so "not affecting other bits" is enforced
// in software via a shadow register + mask, then the entire word is shifted
// out and latched. See apply_bits().

// ---- 74HC595 output expander bit masks ----
#define OUT_DIS_MASK   ((uint16_t)0x0002U)
#define PHADJ_MASK     ((uint16_t)0x0004U)
#define SEQ_MASK       ((uint16_t)0x0008U)
#define PHINV_MASK     ((uint16_t)0x0010U)
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

// Shadow registers -- single source of truth for output state. Hardware
// can't be read back; these in-RAM copies are authoritative.
extern uint16_t hc595_shadow;   // 74HC595 output expander
extern uint16_t led595_shadow;

// Apply a masked update without touching unrelated bits in a shadow word.
void apply_bits(uint16_t *shadow, uint16_t mask, uint16_t value);

// Push the full shadow word out over SPI and latch it.
void WriteRegister(void);     // flushes hc595_shadow -> output expander

// Convenience wrappers: modify shadow bit(s) then flush.
void SetExpanderRegister(uint16_t bitMask, uint8_t value);
void ToggleExpanderRegister(uint16_t bitMask);
void SetExpanderBits(uint16_t mask, uint16_t bits);

void WriteRegisterLED(void);
void SetLEDRegister(uint16_t bitMask, uint8_t value);
void ToggleLEDRegister(uint16_t bitMask);
void SetLEDBits(uint16_t mask, uint16_t bits);
#endif
