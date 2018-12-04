#include "tm4c123gh6pm.h"
#ifndef __LCD_DRIVER_H__
#define __LCD_DRIVER_H__

void LCD_init(void);
void LCD_data(unsigned char data);
void LCD_reset(void);
void LCD_command(unsigned char command);
void delayMs(int n);
void delayUs(int n);

#endif // __LCD_DRIVER_H__