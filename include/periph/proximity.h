#ifndef BLE_H
#define BLE_H

#include <avr/io.h>


void proximity_pins_init(void);
void proximity_timer1_init(void);

int proximity_dist();

#endif /* ble.h */
