#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include <stdbool.h>

typedef enum {
    BT_DISCONNECTED,
    BT_CONNECTED,
    BT_PLAYING
} BtLinkState;

void Bluetooth_Init(void);
void Bluetooth_Update(void);
BtLinkState Bluetooth_GetState(void);

#endif