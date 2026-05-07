#include <stdint.h>
#include <stdbool.h>
#include "mcc_generated_files\nvm\nvm.h"
#include "parameters.h"
#include "systick.h"

#define WRITE_DELAY 500
#define DATA_SIZE PARAM_COUNT  // Your PARAM_COUNT
#define BLOCK_SIZE (DATA_SIZE + 1) // 20 data bytes + 1 sequence byte
#define MAX_BLOCKS (EEPROM_SIZE / BLOCK_SIZE)

eeprom_address_t currentBlockAddress = EEPROM_START_ADDRESS;
uint8_t currentSequence = 0;
static bool isParamDirty = false;
static uint32_t lastParamUpdateTime = 0;

void Storage_MarkDirty(void) {
    isParamDirty = true;
    lastParamUpdateTime = systemTicks;
}
void EEPROM_Write_Reliable(eeprom_address_t address, uint8_t data)
{
    uint8_t gie_save = INTCON0bits.GIE;
    INTCON0bits.GIE = 0;

    NVMADRH = (uint8_t)(address >> 8);
    NVMADRL = (uint8_t)address;
    NVMDAT  = data;

    NVMCON1bits.NVMREG = 0;     // Select Data EEPROM
    NVMCON1bits.WREN   = 1;     // Enable writes

    // Strict unlock sequence - critical part
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;         // Start self-timed write

    while (NVMCON1bits.WR);     // Wait until hardware clears WR bit

    NVMCON1bits.WREN = 0;       // Disable writes
    INTCON0bits.GIE  = gie_save;
}
void GrabDataFromEEPROM(void) {
    uint8_t maxSeq = 0;
    eeprom_address_t foundAddr = 0;
    bool foundAny = false;

    for (eeprom_address_t i = 0; i < MAX_BLOCKS; i++) {
        eeprom_address_t addr = i * BLOCK_SIZE + EEPROM_START_ADDRESS;
        uint8_t seq = EEPROM_Read(addr);
        
        // 0xFF usually means uninitialized/erased
        if (seq != 0xFF) {
            // Logic to handle 8-bit rollover (e.g., 255 -> 0)
            if (!foundAny || (uint8_t)(seq - maxSeq) < 128) {
                maxSeq = seq;
                foundAddr = addr;
                foundAny = true;
            }
        }
    }
    if(!foundAny)
        return;

    currentBlockAddress = foundAddr;
    currentSequence = maxSeq;

    // Load actual data (offset by 1 because index 0 is the sequence byte)
    for (eeprom_address_t i = 0; i < DATA_SIZE; i++) {
        allParameters[i]->value = EEPROM_Read(currentBlockAddress + 1 + i);
    }
}

void SyncDirtyParameters(void) {
    if (!isParamDirty)
        return;
    if ((systemTicks - lastParamUpdateTime) < WRITE_DELAY)
        return;
    // 1. Move to next block
    eeprom_address_t nextBlockAddr = currentBlockAddress + BLOCK_SIZE;
    if (nextBlockAddr + BLOCK_SIZE > EEPROM_START_ADDRESS + EEPROM_SIZE) {
        nextBlockAddr = EEPROM_START_ADDRESS;
    }

    // 2. Increment sequence
    currentSequence++;
    if (currentSequence == 0xFF) currentSequence = 0; // Avoid FF to stay clear of "empty" marker

    // 3. Write sequence byte first
    EEPROM_Write_Reliable(nextBlockAddr, currentSequence);
    
    // 4. Write data bytes
    for (eeprom_address_t i = 0; i < PARAM_COUNT; i++) {
        EEPROM_Write_Reliable(nextBlockAddr + 1 + i, allParameters[i]->value);
        allParameters[i]->isDirty = false;
    }

    currentBlockAddress = nextBlockAddr;
    isParamDirty = false;
}