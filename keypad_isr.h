#ifndef KEYPAD_ISR_H_
#define KEYPAD_ISR_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void keypad_isr_init(void);
void keypad_isr_handler(void);

#endif /* KEYPAD_ISR_H_ */
