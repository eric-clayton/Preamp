#include "storage.h"
#include "mcc_generated_files\nvm\nvm.h"
#include "parameters.h"
#include "systick.h"
#include "input.h"
#include "tone.h"
#include "power.h"

#define WRITE_DELAY 500
#define BLOCK_METADATA_BYTES 4

eeprom_address_t currentBlockAddress = EEPROM_START_ADDRESS;
uint8_t currentSequence = 0;
static bool isStorageOutOfSync = false;
static uint32_t lastDataUpdateTime = 0;

static void EEPROM_Write_Reliable(eeprom_address_t address, uint8_t data);

static uint16_t ParameterDataSize(void)
{
    uint16_t size = 0;
    for (uint8_t i = 0; i < PARAM_COUNT; i++)
        size += allParameters[i]->storageBytes;
    return size;
}

static uint16_t StorageBlockSize(void)
{
    return BLOCK_METADATA_BYTES + ParameterDataSize();
}

static eeprom_address_t ParameterAddress(eeprom_address_t blockAddress, uint8_t parameterIndex)
{
    eeprom_address_t address = blockAddress + 1;
    for (uint8_t i = 0; i < parameterIndex; i++)
        address += allParameters[i]->storageBytes;
    return address;
}

static eeprom_address_t ExtrasAddress(eeprom_address_t blockAddress)
{
    return blockAddress + 1 + ParameterDataSize();
}

static int16_t ReadParameter(eeprom_address_t address, const Parameter_t *parameter)
{
    uint8_t lowByte = EEPROM_Read(address);
    if (parameter->storageBytes == PARAM_STORAGE_1_BYTE)
        return (int16_t)(parameter->minValue + lowByte);

    uint16_t value = lowByte | ((uint16_t)EEPROM_Read(address + 1) << 8);
    return (int16_t)value;
}

static void WriteParameter(eeprom_address_t address, const Parameter_t *parameter)
{
    if (parameter->storageBytes == PARAM_STORAGE_1_BYTE) {
        EEPROM_Write_Reliable(address, (uint8_t)(parameter->value - parameter->minValue));
        return;
    }

    uint16_t value = (uint16_t)parameter->value;
    EEPROM_Write_Reliable(address, (uint8_t)(value & 0xFF));
    EEPROM_Write_Reliable(address + 1, (uint8_t)(value >> 8));
}

void Storage_MarkDirty(void) {
    isStorageOutOfSync = true;
    lastDataUpdateTime = SysTick_Now();
}

static void EEPROM_Write_Reliable(eeprom_address_t address, uint8_t data)
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
    uint16_t blockSize = StorageBlockSize();
    uint16_t maxBlocks = EEPROM_SIZE / blockSize;

    for (uint16_t i = 0; i < maxBlocks; i++) {
        eeprom_address_t addr = i * blockSize + EEPROM_START_ADDRESS;
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
    if (!foundAny)
    {
        Storage_MarkDirty(); // no data found save in storage
        Input_LoadSettings(0);
        Tone_LoadSettings(0);
        Power_LoadSettings(0);
        return;
    }

    currentBlockAddress = foundAddr;
    currentSequence = maxSeq;

    // Load actual data (offset by 1 because index 0 is the sequence byte)
    for (uint8_t i = 0; i < PARAM_COUNT; i++) {
        Parameter_t *p = allParameters[i];
        eeprom_address_t a = ParameterAddress(currentBlockAddress, i);
        int16_t v = ReadParameter(a, p);
        if (v < p->minValue) v = p->minValue;
        if (v > p->maxValue) v = p->maxValue;
        p->value = v;
    }
    eeprom_address_t extrasAddress = ExtrasAddress(currentBlockAddress);
    Input_LoadSettings(EEPROM_Read(extrasAddress));
    Tone_LoadSettings (EEPROM_Read(extrasAddress + 1));
    Power_LoadSettings(EEPROM_Read(extrasAddress + 2));
}

void SyncStorage(void) {
    if (!isStorageOutOfSync) return;
    if ((SysTick_Now() - lastDataUpdateTime) < WRITE_DELAY) return;

    uint16_t blockSize = StorageBlockSize();
    eeprom_address_t nextBlockAddr = currentBlockAddress + blockSize;
    if (nextBlockAddr + blockSize > EEPROM_START_ADDRESS + EEPROM_SIZE)
        nextBlockAddr = EEPROM_START_ADDRESS;

    currentSequence++;
    if (currentSequence == 0xFF) currentSequence = 0;

    EEPROM_Write_Reliable(nextBlockAddr, currentSequence);

    for (uint8_t i = 0; i < PARAM_COUNT; i++) {
        Parameter_t *parameter = allParameters[i];
        WriteParameter(ParameterAddress(nextBlockAddr, i), parameter);
        parameter->isDirty = false;
    }
    eeprom_address_t extrasAddress = ExtrasAddress(nextBlockAddr);
    EEPROM_Write_Reliable(extrasAddress,     (uint8_t)GetInputType());
    EEPROM_Write_Reliable(extrasAddress + 1, GetToneValue());
    EEPROM_Write_Reliable(extrasAddress + 2, GetPowerState());

    currentBlockAddress = nextBlockAddr;
    isStorageOutOfSync = false;
}
void Storage_ForceSync(void) {
    if (!isStorageOutOfSync) return;
    lastDataUpdateTime = SysTick_Now() - WRITE_DELAY; // satisfy the delay check
    SyncStorage();
}