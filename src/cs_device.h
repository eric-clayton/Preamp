#ifndef CS_DEVICE_H
#define CS_DEVICE_H

// Generic chip-select pair. Used by anything addressed over SPI with a
// dedicated CS line: true digipots (wiper-addressed) AND shift-register
// chains (74HC595 / ADG1414, full-word addressed). The write model differs
// per device type -- see digipot.h vs shift_register.h -- but the CS
// mechanics are identical, so this lives in its own leaf header.

typedef void (*CS_SetFunc)(void);

typedef struct {
    CS_SetFunc csLow;
    CS_SetFunc csHigh;
} CS_Device_t;

#endif
