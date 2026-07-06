// storage.h
#ifndef STORAGE_H
#define STORAGE_H
#include <stdbool.h>

void GrabDataFromEEPROM(void);
void SyncStorage(void);
void Storage_MarkDirty(void); 
void Storage_ForceSync(void);


#endif