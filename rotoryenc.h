/* 
 * File:   rotoryenc.h
 * Author: david
 *
 * Created on February 26, 2026, 9:45 AM
 */

#ifndef ROTORYENC_H
#define	ROTORYENC_H

#ifdef	__cplusplus
extern "C" {
#endif
typedef struct {
    uint8_t value;           // Current 0-254 value
    uint8_t maxValue;
    int8_t lastDirection;
    uint32_t lastChangeTime;
    uint8_t lastState;
    uint8_t fastStep;        // How much to jump when turning fast
    uint8_t slowStep;        // How much to jump when turning slow
} Encoder_t;
bool ROTARYENC_Process(Encoder_t *knob, uint8_t RCA, uint8_t RCB, uint32_t *systemTicks);


#ifdef	__cplusplus
}
#endif

#endif	/* ROTORYENC_H */

