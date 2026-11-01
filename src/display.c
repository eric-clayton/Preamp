#include "display.h"
#include "as1115.h"
#include "shift_register.h"      // SetExpanderRegister / SetExpanderBits / ToggleExpanderRegister
#include <stdbool.h>
#include "mcc_generated_files\system\clock.h"

/* ============================================================================
 *  PANEL LAYOUT
 *
 *  AS1115 register N drives digit N-1. Register 1 (DIG0) is the RIGHTMOST
 *  character on the panel, so text is written right-to-left.
 *
 *    reading order:  reg7  reg6  reg5  reg4 | reg3  reg2  reg1 |  reg8
 *                    DIG6  DIG5  DIG4  DIG3 | DIG2  DIG1  DIG0 |  DIG7
 *                    <------- LEFT --------->|<---- RIGHT ----->|  (LED bank)
 *
 *  LEFT  zone (DIG3-DIG6): tone parameters - boost/cut, frequency, Q
 *  RIGHT zone (DIG0-DIG2): volume / balance / gains
 *
 *  Sign handling
 *    RIGHT zone: decimal point of DIG0 (bit 7 of the byte written to reg 1).
 *                Stateless - it is written together with the digit, so any
 *                later write to reg 1 clears it automatically.
 *    LEFT  zone: "neg" LED on the DIG7 LED bank (reg 8).
 * ========================================================================== */
#define REG_DIG0        1       // rightmost digit / LSD of the right zone
#define REG_DIG3        4       // LSD of the left zone

// Decode-mode bit for a register: reg 1 -> bit 0 ... reg 7 -> bit 6
#define DEC(reg)        (1u << ((reg) - 1))
#define ZONE_RIGHT      (DEC(1) | DEC(2) | DEC(3))
#define ZONE_LEFT       (DEC(4) | DEC(5) | DEC(6) | DEC(7))
#define ZONE_ALL        (ZONE_RIGHT | ZONE_LEFT)

// Code-B (decode mode) special codes
#define CODE_B_DASH     0x0A
#define CODE_B_BLANK    0x0F

/* ============================================================================
 *  GLYPH TABLE  (no-decode mode:  DP=b7  A=b6  B=b5  C=b4  D=b3  E=b2  F=b1  G=b0)
 *  Every character is defined once, from its segments, and reused below.
 * ========================================================================== */
#define SEG_DP  0x80
#define SEG_A   0x40
#define SEG_B   0x20
#define SEG_C   0x10
#define SEG_D   0x08
#define SEG_E   0x04
#define SEG_F   0x02
#define SEG_G   0x01

#define CH_BLANK 0x00
#define CH_DASH  (SEG_G)
#define CH_0     (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F)
#define CH_1     (SEG_B | SEG_C)
#define CH_8     (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define CH_A     (SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G)
#define CH_b     (SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define CH_d     (SEG_B | SEG_C | SEG_D | SEG_E | SEG_G)
#define CH_E     (SEG_A | SEG_D | SEG_E | SEG_F | SEG_G)
#define CH_F     (SEG_A | SEG_E | SEG_F | SEG_G)
#define CH_H     (SEG_B | SEG_C | SEG_E | SEG_F | SEG_G)
#define CH_h     (SEG_C | SEG_E | SEG_F | SEG_G)
#define CH_i     (SEG_C)
#define CH_L     (SEG_D | SEG_E | SEG_F)
#define CH_n     (SEG_C | SEG_E | SEG_G)
#define CH_o     (SEG_C | SEG_D | SEG_E | SEG_G)
#define CH_P     (SEG_A | SEG_B | SEG_E | SEG_F | SEG_G)
#define CH_Q     (CH_0 | SEG_DP)            // "0" with its point lit
#define CH_r     (SEG_E | SEG_G)
#define CH_S     (SEG_A | SEG_C | SEG_D | SEG_F | SEG_G)
#define CH_t     (SEG_D | SEG_E | SEG_F | SEG_G)
#define CH_u     (SEG_C | SEG_D | SEG_E)
#define CH_O     CH_0                       // same shapes, different names
#define CH_I     CH_1

/* ============================================================================
 *  MESSAGES - written exactly as they read, LEFT to right.
 *  WriteText() takes care of the right-to-left register order.
 *    7 chars = whole panel, 4 chars = left zone (DIG3-DIG6), 3 chars = right zone
 * ========================================================================== */
static const uint8_t TXT_SUB_DISABLED[] = { CH_BLANK, CH_S, CH_u, CH_b, CH_d, CH_I, CH_S };
static const uint8_t TXT_PHASE_0[]      = { CH_P, CH_H, CH_A, CH_S, CH_BLANK, CH_BLANK, CH_0 };
static const uint8_t TXT_PHASE_180[]    = { CH_P, CH_H, CH_A, CH_S, CH_1, CH_8, CH_0 };
static const uint8_t TXT_SUB_EQ_IN[]    = { CH_S, CH_DASH, CH_E, CH_Q, CH_BLANK, CH_I, CH_n };
static const uint8_t TXT_SUB_EQ_OUT[]   = { CH_S, CH_DASH, CH_E, CH_Q, CH_O, CH_u, CH_t };

static const uint8_t TXT_SUB_LVL_R[]    = { CH_S, CH_DASH, CH_L, CH_r };
static const uint8_t TXT_SUB_LVL_L[]    = { CH_S, CH_DASH, CH_L, CH_L };
static const uint8_t TXT_OUT_L[]        = { CH_o, CH_u, CH_t, CH_L };
static const uint8_t TXT_INP_L[]        = { CH_I, CH_n, CH_P, CH_L };
static const uint8_t TXT_ON[]           = { CH_BLANK, CH_BLANK, CH_O, CH_n };
static const uint8_t TXT_OFF[]          = { CH_BLANK, CH_O, CH_F, CH_F };

static const uint8_t TXT_INF[]          = { CH_i, CH_n, CH_F };
static const uint8_t TXT_DB[]           = { CH_d, CH_b };      // regs 4-5 next to the number

// Balance: left-to-right "9-1" ... "1-9"; stored LSD first for DisplayDataPartition
const uint8_t balanceLevels[9][3] = {
    {1, CODE_B_DASH, 9}, {2, CODE_B_DASH, 8}, {3, CODE_B_DASH, 7},
    {4, CODE_B_DASH, 6}, {5, CODE_B_DASH, 5}, {6, CODE_B_DASH, 4},
    {7, CODE_B_DASH, 3}, {8, CODE_B_DASH, 2}, {9, CODE_B_DASH, 1}
};

/* ============================================================================
 *  LEDs
 *
 *    AS1115 reg 8 (DIG7) : left-zone NEG LED only
 *    74HC595 chain       : every button LED (power, tone, inputs, BT status),
 *                          written through shift_register.c
 *
 *  The right-side NEG LED is retired: DIG0's decimal point carries that sign.
 *
 *  74HC595 bit map (low byte = first chip in the chain). Bit 0 and the whole
 *  high byte are NOT LEDs, so only BTN_LED_ALL is ever touched from here.
 * ========================================================================== */
#ifndef BTN_LED_ALL
#define BTN_LED_POWER   0x0002u
#define BTN_LED_TONE    0x0004u
#define BTN_LED_IN1     0x0008u
#define BTN_LED_IN2     0x0010u
#define BTN_LED_IN3     0x0020u
#define BTN_LED_IN4BT   0x0040u
#define BTN_LED_BTSTAT  0x0080u
#define BTN_LED_ALL     0x00FEu
#endif
#define BTN_LED_INPUTS  (BTN_LED_IN1 | BTN_LED_IN2 | BTN_LED_IN3 | BTN_LED_IN4BT)

// ---- AS1115 reg 8: NEG LED -------------------------------------------------
static uint8_t lightMap = 0x00;
#define LED_NEG_LEFT_BIT  0x80

void Display_WriteLEDs(void) {
    AS1115_Write(0x08, lightMap);
}
void Display_SetNegLeftLED(uint8_t enabled) {
    uint8_t temp = lightMap;
    if (enabled) lightMap |=  LED_NEG_LEFT_BIT;
    else         lightMap &= ~LED_NEG_LEFT_BIT;

    if (lightMap != temp)
        Display_WriteLEDs();
}

// ---- 74HC595: button LEDs --------------------------------------------------
#define LED_BITS_SIZE 8
static const uint16_t led595[LED_BITS_SIZE] = {
    [LED_INPUT_ONE]   = BTN_LED_IN1,
    [LED_INPUT_TWO]   = BTN_LED_IN2,
    [LED_INPUT_THREE] = BTN_LED_IN3,
    [LED_INPUT_BT]    = BTN_LED_IN4BT,
    [LED_TONE]        = BTN_LED_TONE,
    [LED_NEG_LEFT]    = 0,                  // lives on the AS1115, not the 595
    [LED_NONE]        = 0
};

static uint16_t Led595Mask(LEDType ledType)
{
    return ((unsigned)ledType < LED_BITS_SIZE) ? led595[ledType] : 0;
}

LEDType LEDBlinkType = LED_NONE;
static uint16_t blinkMask595 = 0;
static uint16_t standbyLEDs = 0;

void Display_SetToneLED(uint8_t enabled) {
    SetLEDRegister(BTN_LED_TONE, enabled);
}
void Display_SetInputLED(LEDType ledType) {
    // Replaces the input LED bits only, so the other input LEDs go off
    SetLEDBits(BTN_LED_INPUTS, Led595Mask(ledType));
}
void Display_BlinkLED(void) {
    if (blinkMask595)
       ToggleLEDRegister(blinkMask595);
}
void Display_SetBlinkBitIndex(LEDType ledType)
{
    LEDBlinkType = ledType;
    blinkMask595 = Led595Mask(ledType);
}

// Standby: remember the pattern, then darken every button LED (one write)
void Display_LEDsStandby(void)
{
    standbyLEDs = led595_shadow & BTN_LED_ALL;
    SetLEDBits(BTN_LED_ALL, 0);
}

// Wake: restore the pattern and light the power LED in the same write
void Display_LEDsWake(void)
{
    SetLEDBits(BTN_LED_ALL, standbyLEDs | BTN_LED_POWER);
}
void Display_SetBTStatusLED(uint8_t enabled) {
    SetLEDRegister(BTN_LED_BTSTAT, enabled);
}

/* ============================================================================
 *  INTERNAL HELPERS
 * ========================================================================== */

// Decode mode is tracked per zone so a left-zone screen (boost/cut, freq, Q)
// never disturbs how the right zone (e.g. volume, DIG0 raw) is configured.
// Power-up assumption: volume layout on the right (DIG1-DIG2 decoded, DIG0 raw).
static uint8_t decodeShadow = DEC(2) | DEC(3);

static void SetDecode(uint8_t zones, uint8_t bits)
{
    decodeShadow = (uint8_t)((decodeShadow & ~zones) | (bits & zones));
    AS1115_Write(AS1115_REG_DECODE_MODE, decodeShadow);
}

// Writes a message that is listed left-to-right; 'rightmostReg' is where its
// last character lands.
static void WriteText(const uint8_t *text, uint8_t len, uint8_t rightmostReg)
{
    for (uint8_t i = 0; i < len; i++)
        AS1115_Write(rightmostReg + i, text[len - 1 - i]);
}
#define WRITE_TEXT(msg, reg)  WriteText((msg), (uint8_t)sizeof(msg), (reg))

static uint16_t Magnitude(int16_t v)
{
    return (v < 0) ? (uint16_t)(-(int32_t)v) : (uint16_t)v;
}

// Writes an unsigned value into numDigits decoded digits, LSD at startReg.
//   decimal        : point after the 2nd digit, at least 2 digits shown ("0.5")
//   negativeOnDig0 : light DIG0's decimal point if this loop writes reg 1
static void WriteNumber(uint16_t value, uint8_t startReg, uint8_t numDigits,
                        bool decimal, bool negativeOnDig0)
{
    const uint8_t minDigits = decimal ? 2 : 1;

    for (uint8_t i = 0; i < numDigits; i++)
    {
        uint8_t reg  = startReg + i;
        uint8_t data = CODE_B_BLANK;

        if (i < minDigits || value > 0)
        {
            data = (uint8_t)(value % 10);
            value /= 10;
            if (decimal && i == 1)
                data |= SEG_DP;
        }
        if (reg == REG_DIG0 && negativeOnDig0)
            data |= SEG_DP;

        AS1115_Write(reg, data);
    }
}

// Signed number in either zone. Right zone sign -> DIG0 DP, left zone sign -> LED.
static void ShowSigned(int16_t number, uint8_t startReg, uint8_t numDigits, bool decimal)
{
    bool     negative = number < 0;
    uint16_t mag      = Magnitude(number);

    if (startReg < REG_DIG3)
    {
        WriteNumber(mag, startReg, numDigits, decimal, negative);
    }
    else
    {
        WriteNumber(mag, startReg, numDigits, decimal, false);
        Display_SetNegLeftLED(negative);
    }
}

// Right zone = number (DIG0-DIG2), left zone = 4-character label (DIG3-DIG6)
static void ShowLabeledValue(int16_t value, bool decimal, const uint8_t *label, uint8_t labelLen)
{
    SetDecode(ZONE_ALL, ZONE_RIGHT);            // numbers decoded right, raw text left
    ShowSigned(value, REG_DIG0, 3, decimal);
    WriteText(label, labelLen, REG_DIG3);
    Display_SetNegLeftLED(false);               // left zone is text, clear any stale sign
}
#define SHOW_LABELED(value, decimal, label) \
    ShowLabeledValue((value), (decimal), (label), (uint8_t)sizeof(label))

/* ============================================================================
 *  PUBLIC PARTITION HELPERS (same signatures as before)
 * ========================================================================== */

// Number constrained to part of the display, no decimal point
void AS1115_DisplayPartition(int16_t number, uint8_t startReg, uint8_t numDigits) {
    ShowSigned(number, startReg, numDigits, false);
}

// Same, with a decimal point after the 2nd digit ("1.0", "12.5")
void AS1115_DisplayPartitionDecimal(int16_t number, uint8_t startReg, uint8_t numDigits) {
    ShowSigned(number, startReg, numDigits, true);
}

// Raw data array (LSD first) written to consecutive registers
void AS1115_DisplayDataPartition(const uint8_t* data, uint8_t len, uint8_t startReg) {
    for (uint8_t i = 0; i < len; i++) {
        AS1115_Write(startReg + i, data[i]);
    }
}

/* ============================================================================
 *  SCREENS
 * ========================================================================== */

// ---- Subwoofer ------------------------------------------------------------
void DisplaySubEnableDisable(int16_t value)
{
    SetDecode(ZONE_ALL, 0);
    switch (value) {
        case 1:  WRITE_TEXT(TXT_PHASE_0,      REG_DIG0); break;
        case 2:  WRITE_TEXT(TXT_PHASE_180,    REG_DIG0); break;
        default: WRITE_TEXT(TXT_SUB_DISABLED, REG_DIG0); break;
    }
    Display_SetNegLeftLED(false);
}

void DisplaySubEQ(int16_t value)
{
    SetDecode(ZONE_ALL, 0);
    if (value == 1) WRITE_TEXT(TXT_SUB_EQ_OUT, REG_DIG0);
    else            WRITE_TEXT(TXT_SUB_EQ_IN,  REG_DIG0);
    Display_SetNegLeftLED(false);
}

void DisplaySubLevelRight(int16_t value)
{
    SHOW_LABELED(value, false, TXT_SUB_LVL_R);
}

void DisplaySubLevelLeft(int16_t value)
{
    SHOW_LABELED(value, false, TXT_SUB_LVL_L);
}

// ---- Gains / power delay (label left, number right) ------------------------
void DisplayOutputGain(int16_t value)
{
    SHOW_LABELED(value, true, TXT_OUT_L);
}

void DisplayInputGain(int16_t value)
{
    SHOW_LABELED(value, true, TXT_INP_L);
}

void DisplayPowerDelayOn(int16_t value)
{
    SHOW_LABELED(value, false, TXT_ON);
}

void DisplayPowerDelayOff(int16_t value)
{
    if (value == 100)
    {
        // "OFF" left, "inF" right - everything raw
        SetDecode(ZONE_ALL, 0);
        WRITE_TEXT(TXT_OFF, REG_DIG3);
        WRITE_TEXT(TXT_INF, REG_DIG0);
        Display_SetNegLeftLED(false);
    }
    else
    {
        SHOW_LABELED(value, false, TXT_OFF);
    }
}

// ---- Volume / balance (right zone, DIG0-DIG2) --------------------------------
// value = dB x 10 (e.g. -815 = -81.5 dB). Shown as whole dB: "-80d" ... "15d"
//   DIG0      raw 'd', its decimal point = negative sign
//   DIG1-DIG2 decoded digits
void DisplayVolume(int16_t value)
{
    bool     negative = value < 0;
    uint16_t dB       = (Magnitude(value) + 5) / 10;    // round to whole dB

    if (dB > 99)  dB = 99;                              // only two digits available
    if (dB == 0)  negative = false;                     // never show "-0"

    SetDecode(ZONE_RIGHT, DEC(2) | DEC(3));
    WriteNumber(dB, 2, 2, false, false);
    AS1115_Write(REG_DIG0, negative ? (CH_d | SEG_DP) : CH_d);
}

// value = balance index 0..8, shown "9-1" ... "1-9"
void DisplayBalance(int16_t value)
{
    if (value < 0) value = 0;
    if (value > 8) value = 8;

    SetDecode(ZONE_RIGHT, ZONE_RIGHT);
    AS1115_DisplayDataPartition(balanceLevels[value], 3, REG_DIG0);
}

// ---- Tone parameters (left zone, DIG3-DIG6; right zone left untouched) --------
// "x.xdb"  value = dB x 10, sign on the left NEG LED
void DisplayBoostCut(int16_t value)
{
    SetDecode(ZONE_LEFT, DEC(6) | DEC(7));      // regs 4-5 raw ("db"), 6-7 digits
    WRITE_TEXT(TXT_DB, REG_DIG3);
    ShowSigned(value, 6, 2, true);
}

// "22h" ... "999h"
void DisplayFreqLow(int16_t value)
{
    SetDecode(ZONE_LEFT, DEC(5) | DEC(6) | DEC(7));
    AS1115_Write(REG_DIG3, CH_h);
    ShowSigned(value, 5, 3, false);
}

// "1.0H" ... "16.0H"  (value = kHz x 10)
void DisplayFreqHigh(int16_t value)
{
    SetDecode(ZONE_LEFT, DEC(5) | DEC(6) | DEC(7));
    AS1115_Write(REG_DIG3, CH_H);
    ShowSigned(value, 5, 3, true);
}

// Q 1..10, right-aligned in DIG3-DIG6
// (if Q is stored in tenths, use ShowSigned(value, 4, 3, true) for "1.0".."10.0")
void DisplayQ(int16_t value)
{
    SetDecode(ZONE_LEFT, ZONE_LEFT);
    ShowSigned(value, REG_DIG3, 4, false);
}

/* ============================================================================
 *  TEST
 * ========================================================================== */
void Display_TestButtons(void)
{
    SetDecode(ZONE_RIGHT, ZONE_RIGHT);

    while (true)
    {
        for (uint8_t bit = 0; bit < 8; bit++)
        {
            // Show the bit INDEX (0-7) while walking a single bit through reg 8
            AS1115_DisplayPartition(bit, REG_DIG0, 3);
            AS1115_Write(0x08, (uint8_t)(1u << bit));
            __delay_ms(1000);
        }
    }
}

// Walks one 74HC595 LED bit at a time (bits 1-7 = 0x0002 .. 0x0080) and shows
// the bit index, so the physical LED can be matched to the table.
// Bit 0 and the high byte are never touched.
void Display_TestLEDs595(void)
{
    SetDecode(ZONE_RIGHT, ZONE_RIGHT);

    while (true)
    {
        for (uint8_t bit = 1; bit <= 7; bit++)
        {
            AS1115_DisplayPartition(bit, REG_DIG0, 3);
            SetExpanderBits(BTN_LED_ALL, (uint16_t)(1u << bit));
            __delay_ms(1000);
        }
    }
}