#ifndef __KEYPAD_DRIVER_H__
#define __KEYPAD_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "tm4c123gh6pm.h"
#include "parser_module.h"

extern char x[16];

void keypad_init(void);
void keypad_isr_handler(void);
unsigned char keypad_getkey(void);
unsigned char keypad_getchar(void);
void Globals_reset(void);

#endif // __KEYPAD_DRIVER_H__
