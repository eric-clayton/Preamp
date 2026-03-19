#include "mcc_generated_files/system/system.h"
#include "as1115.h"
#include "rotoryenc.h"
#include <stdint.h>
#include <math.h>

#define vol_CS_LAT LATAbits.LATA0
#define vol_CS_TRIS TRISAbits.TRISA0

#define DISPLAY_TIMEOUT 4000
#define MUTE_TIMEOUT 2000

volatile uint32_t systemTicks = 0;

void AS1115_DisplayPartition(uint32_t number, uint8_t startReg, uint8_t numDigits);
void AS1115_DisplayDataPartition(const uint8_t* data, uint8_t len, uint8_t startReg);
void UpdateDigitalPots(void);
void MCP4262_WriteWiper(uint8_t wiperAddr, uint8_t data);

// Encoders
Encoder_t volumeKnob = {0, 254, 1, 0, 0, 5, 1};
Encoder_t balanceKnob = {127, 254, 1, 0, 0, 4, 4}; 
Encoder_t lfBoostKnob = {127, 254, 1, 0, 0, 4, 4}; // Low-freq boost/cut
Encoder_t frequencyKnob = {127, 254, 1, 0, 0, 4, 4}; // Freq boost/cut
Encoder_t QKnob = {127, 254, 1, 0, 0, 4, 4}; // Q
Encoder_t hfBoostKnob = {127, 254, 1, 0, 0, 4, 4}; // Hi-freq boost/cut


Encoder_t* activeDisplay2Encoder = &volumeKnob;
uint32_t display2Timer = 0;

const uint8_t balanceLevels[9][3] = {
    {1, 10, 9}, {2, 10, 8}, {3, 10, 7}, 
    {4, 10, 6}, {5, 10, 5}, {6, 10, 4}, 
    {7, 10, 3}, {8, 10, 2}, {9, 10, 1}
};


void MyTimerCallback(void) {
    systemTicks++; 
}    

void DisplayVolume() {
    uint8_t displayVol = (uint8_t)roundf((volumeKnob.value / 254.0) * 100);
    
    // Write the volume strictly to Digits 1-3 (Regs 1, 2, 3)
    AS1115_DisplayPartition(displayVol, 1, 3);
    
    activeDisplay2Encoder = &volumeKnob;
}

int main(void) {
    SYSTEM_Initialize();
    
    // SPI & CS Setup (Ensure TRIS is configured in MCC or here)
    vol_CS_TRIS = 0; 
    vol_CS_LAT = 1;

    INTERRUPT_GlobalInterruptEnable(); 
    TMR0_Start();
    TMR0_OverflowCallbackRegister(MyTimerCallback);

    __delay_ms(100);
    AS1115_Init();
    __delay_ms(100);
    AS1115_Write(AS1115_REG_SCAN_LIMIT, AS1115_DISPLAY_DIGITS_0_6); 
    AS1115_Write(AS1115_REG_DECODE_MODE, AS1115_DECODE_DIGIT_0_6); 
    AS1115_Write(AS1115_FEATURE, AS1115_DECODE_SEL_CODE_B); 
    
    DisplayVolume();
    UpdateDigitalPots(); // Initial push to SPI

    while(1) {
        // --- 1. USER INPUT: BUTTON SCANNING (Placeholder for flowchart logic) ---
        // if (PORT_IO_PSW == PRESSED) { Trigger 2s mute, toggle IO_POWER state }
        // if (PORT_IO_INPUT_SEL == PRESSED) { Trigger 2s mute, toggle IO_ISA/ISB }

        // --- 2. ENCODER SCANNING ---
        // Display 2
        if (ROTARYENC_Process(&volumeKnob, IO_VOLA_PORT, IO_VOLB_PORT, &systemTicks)) {
            DisplayVolume();
            UpdateDigitalPots(); // Push new volume to hardware
        } 
        if (ROTARYENC_Process(&balanceKnob, IO_BALA_PORT, IO_BALB_PORT, &systemTicks)) {
            uint8_t balIndex = (uint8_t)roundf((balanceKnob.value / 254.0) * 8);
            
            // Write array strictly to Digits 1-3 (Regs 1, 2, 3)
            AS1115_DisplayDataPartition(balanceLevels[balIndex], 3, 1);
            
            activeDisplay2Encoder = &balanceKnob;
            display2Timer = systemTicks; 
            UpdateDigitalPots(); 
        }
        // Display 1
        // Low Frequency boost cut
        if (ROTARYENC_Process(&lfBoostKnob, IO_LFA_PORT, IO_LFB_PORT, &systemTicks)) {
            
            // Map 0-254 to -6 to +6 dB (example math based on flowchart)
            // Note: BCD mode on AS1115 handles 0-9, -, E, H, L, P, blank. 
            // You may need custom decode logic if you want to show a "-" sign, 
            // but for raw numbers, we send it to Digits 4-7 (Regs 4, 5, 6, 7)
            AS1115_DisplayPartition(lfBoostKnob.value, 4, 4); 
            
            // Notice we DO NOT change activeDisplayEncoder or displayTimer here.
            // This allows the EQ knobs to stay on screen permanently or have their 
            // own separate timeout without reverting the Volume side.
        }
        // Frequency
        if (ROTARYENC_Process(&frequencyKnob, IO_FREQA_PORT, IO_FREQB_PORT, &systemTicks)) {
            
            AS1115_DisplayPartition(frequencyKnob.value, 4, 4); 
        }
        // Q
        if (ROTARYENC_Process(&QKnob, IO_RQA_PORT, IO_RQB_PORT, &systemTicks)) {
            
            AS1115_DisplayPartition(QKnob.value, 4, 4); 
        }
        // High frequency boost cut
        if (ROTARYENC_Process(&hfBoostKnob, IO_HFA_PORT, IO_HFB_PORT, &systemTicks)) {
            
            AS1115_DisplayPartition(hfBoostKnob.value, 4, 4); 
        }
        

        // --- 3. TIMEOUT LOGIC ---
        // If we are showing anything other than Volume, check the clock
        if (activeDisplay2Encoder != &volumeKnob) {
            if ((systemTicks - display2Timer) >= DISPLAY_TIMEOUT) {
                DisplayVolume(); // Revert to volume
            }
        }
    }
}

// Calculates Left/Right channels based on flowchart and pushes via SPI
void UpdateDigitalPots(void) {
    int16_t baseVol = volumeKnob.value;
    int16_t bal = balanceKnob.value; // 0 to 254, center is 127

    int16_t leftVol = baseVol;
    int16_t rightVol = baseVol;

    // Apply Balance Logic (Attenuate the opposite channel)
    if (bal < 127) {
        // Panning Left: Reduce Right channel
        rightVol -= (127 - bal); 
    } else if (bal > 127) {
        // Panning Right: Reduce Left channel
        leftVol -= (bal - 127);
    }

    // Clamp values to valid 0-254 range
    if (leftVol < 0) leftVol = 0;
    if (rightVol < 0) rightVol = 0;
    if (leftVol > 254) leftVol = 254;
    if (rightVol > 254) rightVol = 254;

    // Apply Inverse Log Taper (Linear to Audio taper)
    // uint8_t finalLeft = audioTaper[leftVol];
    // uint8_t finalRight = audioTaper[rightVol];
    uint8_t finalLeft = (uint8_t)leftVol;   // Remove this once lookup table is ready
    uint8_t finalRight = (uint8_t)rightVol; // Remove this once lookup table is ready

    // Write to MCP4262T Digital Pots
    // Wiper 0 = Left, Wiper 1 = Right
    //MCP4262_WriteWiper(0x00, finalLeft);
    //MCP4262_WriteWiper(0x01, finalRight);
}

// SPI Protocol for MCP4262T (16-bit transfer: [4-bit Addr | 2-bit Cmd | 2-bit Data(MSB)] + [8-bit Data(LSB)])
void MCP4262_WriteWiper(uint8_t wiperAddr, uint8_t data) {
    vol_CS_LAT = 0; // CS low
    
    // Command Byte: Address (upper 4) + Write Command (00) + Data MSBs (00 for 8-bit pot)
    uint8_t cmdByte = (wiperAddr << 4) | 0x00; 
    
    SPI1_ByteExchange(cmdByte); 
    SPI1_ByteExchange(data);    
    
    vol_CS_LAT = 1; // CS high
}

// Displays a number constrained to a specific section of the 7-segment display
void AS1115_DisplayPartition(uint32_t number, uint8_t startReg, uint8_t numDigits) {
    uint32_t temp = number;

    for (uint8_t i = 0; i < numDigits; i++) {
        // Always display at least one digit (e.g., '0'), otherwise display if we still have values
        if (i == 0 || temp > 0) {
            AS1115_Write(startReg + i, temp % 10);
            temp /= 10;
        } else {
            // Fill remaining assigned digits with BLANK (0xF in BCD mode)
            AS1115_Write(startReg + i, 0xF); 
        }
    }
}

// Writes raw data arrays (like your Balance visualization) to a specific section
void AS1115_DisplayDataPartition(const uint8_t* data, uint8_t len, uint8_t startReg) {
    for(uint8_t i = 0; i < len; i++) {
        AS1115_Write(startReg + i, data[i]); 
    }
}