# Preamp Project

A microcontroller-based preamplifier with digital signal processing, multi-input selection, subwoofer management, and full remote/encoder control.

---

## Table of Contents

- [Overview](#overview)
- [Logic Flow](#logic-flow)
- [Hardware](#hardware)
  - [Inputs](#inputs)
  - [Encoders](#encoders)
  - [Digital Potentiometers](#digital-potentiometers)
  - [Display](#display)
  - [Pin Reference](#pin-reference)
- [Firmware Behaviour](#firmware-behaviour)
  - [Power Up](#power-up)
  - [User Input Scanning](#user-input-scanning)
  - [Volume & Balance](#volume--balance)
  - [Tone Controls](#tone-controls)
  - [Sub Settings](#sub-settings)
  - [Device Power Management](#device-power-management)
- [Data Sheet References](#data-sheet-references)

---

## Overview

This project implements the control logic for a hi-fi preamplifier. It manages:

- Four selectable inputs (1, 2, 3, Bluetooth)
- Volume control with left/right balance
- Low-frequency (LF) and high-frequency (HF) parametric filter bands — each with independent boost/cut, frequency, and Q adjustment
- Subwoofer enable/disable, phase, EQ, and independent left/right level control
- IR remote receiver and i2c keypad input in addition to rotary encoders
- Per-input device power-on delay and power-off settings
- All encoder positions and switch states persisted to EEPROM

---

## Logic Flow

The diagram below describes the complete firmware control flow.

![Preamp Logic Flow](Flowcharts.pdf)

> See `Flowcharts.pdf` for the full-resolution diagram.

### Summary

```
Power up → restore state from EEPROM
    │
    └─► Scan for user input
            ├── i2c keys
            ├── IR receiver  (IO_IRDA / RC1)
            └── Rotary encoders
                    ├── Volume + acceleration  →  digipots over SPI
                    ├── Balance                →  L/R volume offset
                    ├── LF boost/cut           →  dLFBCpots (SPI)
                    ├── HF boost/cut           →  dHFBCpots (SPI)
                    ├── Frequency (LF or HF)   →  dLFFpots / dHFFpots (SPI)
                    └── Q (LF or HF)           →  dLFQpots / dHFQpots (SPI)
```

---

## Hardware

### Inputs

| Input | IO_ISA | IO_ISB | Device Power Pin |
|-------|--------|--------|-----------------|
| 1     | 0      | 0      | IO_DV1 (RD0)   |
| 2     | 0      | 1      | IO_DV2 (RC0)   |
| 3     | 1      | 0      | IO_DV3 (RA6)   |
| BT    | 1      | 1      | IO_DVBT (RA4)  |

Input selection uses a 2-pin, 2-bit scheme. Each input has configurable power-on delay (1–30 s) and power-off delay (1–99 min, or `InF` for always-on), accessible via a long press on the corresponding input button.

A 2-second mute (`IO_MUTE`, active high) is applied between input changes.

---

### Encoders

**Bourns PEC11R-4015F-N0024**  
Datasheet: [www.bourns.com](https://www.bourns.com)

| Function          | Pin A      | Pin B      |
|-------------------|------------|------------|
| Volume            | IO_VOLA    | IO_VOLB    |
| Balance           | IO_BALA    | IO_BALB    |
| Frequency (LF/HF) | IO_FREQA   | IO_FREQB   |
| LF Boost/Cut      | IO_LFA     | IO_LFB     |
| HF Boost/Cut      | IO_HFA     | IO_HFB     |
| Q (LF/HF)         | IO_RQA     | IO_RQB     |

Encoder focus is maintained for a configurable timeout after the last active input.

---

### Digital Potentiometers

#### Volume — MCP4262T-503E/UN
- Datasheet: microchip.com, page 27
- SPI CS: `IO_VOLCS`
- W0 → Right channel
- W1 → Left channel

#### LF Filter — MCP4351T-103E/ST
- Datasheet: microchip.com, page 52
- SPI CS: `IO_LFACS` (right), `IO_LFBCS` (left)
- W0, W1 → Frequency
- W2 → Q
- W3 → Boost/Cut

#### HF Filter — MCP4351T-103E/ST
- Datasheet: microchip.com, page 52
- SPI CS: `IO_HFACS` (right), `IO_HFBCS` (left)
- W0, W1 → Frequency
- W2 → Q
- W3 → Boost/Cut

#### Sub Level — MCP4232-502E/UN
- SPI CS: `IO_SLCS`
- P0W → Right sub level
- P1W → Left sub level

Global reset pin for all digipots: `IO_RSET`

---

### Display

- 7-segment display; digit 8 segments A–E (no decode mode) used for button LEDs
- Sub settings use a 7-digit display

| UI Context         | Display Text    |
|--------------------|-----------------|
| Sub enable         | `5ub dI5`       |
| Sub phase          | `PHA5 0 / 180`  |
| Sub EQ             | `S-E0. In/out`  |
| Sub level (L/R)    | `S-Lr/L 0–99`   |
| Volume             | `0–100`         |
| Balance            | `0-9 --- 9-0`   |
| LF frequency range | `22h–999h`      |
| HF frequency range | `1.0H–16H`      |
| Q range            | `1–10`          |
| Power delay on     | `xx 5Ec`        |
| Power delay off    | `xx nn` / `InF` |

---

## Firmware Behaviour

### Power Up

1. Restore all encoder positions and switch states from EEPROM
2. Enter main input scan loop

### User Input Scanning

The firmware polls three input sources each cycle:

- **i2c keys** — filter enable/disable (long press enters filter settings); tone button (long press enters Sub settings, blinks Tone LED)
- **IR receiver** — decoded via `IO_IRDA` (RC1, reassigned)
- **Rotary encoders** — handled with per-encoder focus timeout

### Volume & Balance

- Encoder range: 0–254 → scaled to 0–100 for display
- Left/right volume variables set to 0–245 range
- Balance encoder: 0–254 range split as Left 0↔+127 (Lvol) and Right 0↔+127 (Rvol); displayed as `0-9 --- 9-0`
- Balance offset added to volume L/R variables
- Inverse log applied to both variables before writing to `dvolpots` over SPI
- Volume encoder value (0–254) also written to VRAM

### Tone Controls

Each filter band (LF and HF) exposes three parameters:

| Parameter   | Display Range          | VRAM Range | Digipot Wipers |
|-------------|------------------------|------------|----------------|
| Boost/Cut   | ±6 dB                  | 0–254      | W3             |
| Frequency   | 22 Hz–999 Hz / 1–16 kHz | 0–254     | W0, W1         |
| Q           | 1–10                   | 0–254      | W2             |

All values written to the appropriate digipot CS over SPI and mirrored to VRAM.

### Sub Settings

Accessed via long press on the Tone button. Uses a 7-digit display.

| Setting      | Encoder       | Control Pin  |
|--------------|---------------|--------------|
| Enable/Disable | Q encoder   | IO_SUBEN     |
| Phase (0/180°) | Q encoder   | IO_PHASE     |
| EQ In/Out    | Frequency encoder | IO_LFEQ  |
| L/R Level    | LF/HF encoders | IO_SLCS (digipot) |

### Device Power Management

Accessible via long press on any input button (blinks that input's LED).

- **Display input**: `PCx`
- **Balance UI**
- **Power-on delay**: 1–30 s (display: `xx 5Ec`)
- **Power-off delay**: 1–99 min or `InF` for always-on (display: `oFF on / xx nn`)
- Press the same input to loop through settings; press a different input to configure that input instead; press same input a final time to exit.

---

## Pin Reference

| Pin Name  | Function                          |
|-----------|-----------------------------------|
| IO_IRDA   | IR receiver input (RC1 reassigned)|
| IO_PSW    | Power button                      |
| IO_SUBEN  | Sub enable/disable                |
| IO_POWER  | Power state output                |
| IO_DVSA   | Device select A                   |
| IO_DVSB   | Device select B                   |
| IO_ISA    | Input select A                    |
| IO_ISB    | Input select B                    |
| IO_FEN    | Filter enable                     |
| IO_MUTE   | Mute (active high)                |
| IO_PHASE  | Sub phase control                 |
| IO_SLCS   | Sub level digipot SPI CS          |
| IO_LFEQ   | Sub LF EQ enable                  |
| IO_RSET   | Global digipot reset              |
| IO_DV1    | Input 1 device power (RD0)        |
| IO_DV2    | Input 2 device power (RC0)        |
| IO_DV3    | Input 3 device power (RA6)        |
| IO_DVBT   | Bluetooth device power (RA4)      |

---

## Data Sheet References

| Component            | Part Number          | Source                     |
|----------------------|----------------------|----------------------------|
| Rotary Encoder       | PEC11R-4015F-N0024   | www.bourns.com             |
| Volume Digipot       | MCP4262T-503E/UN     | microchip.com (p. 27)      |
| LF/HF Filter Digipot | MCP4351T-103E/ST     | microchip.com (p. 52)      |
| Sub Level Digipot    | MCP4232-502E/UN      | microchip.com              |
