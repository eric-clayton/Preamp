// ir.h
#ifndef IR_H
#define IR_H

#include <stdint.h>

void IR_CaptureHandler(uint16_t now);
void IR_ProcessFrame(void);

#endif