#ifndef __LCD_DRIVER_H__
#define __LCD_DRIVER_H__

#include "tm4c123gh6pm.h"

void LCD_init(void);
void LCD_data(unsigned char data);
void LCD_reset(void);
void LCD_command(unsigned char command);
void LCD_home(void);
void delayMs(int n);
void delayUs(int n);

#endif // __LCD_DRIVER_H__
