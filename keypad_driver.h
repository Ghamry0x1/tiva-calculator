#ifndef __KEYPAD_DRIVER_H__
#define __KEYPAD_DRIVER_H__

#include "tm4c123gh6pm.h"

void keypad_init(void);
unsigned char keypad_getkey(void);
unsigned char keypad_getchar(void);

#endif // __KEYPAD_DRIVER_H__
