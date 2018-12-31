#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "lcd_driver.h"
#include "keypad_driver.h"
#include "parser_module.h"

int row, keyPressed, state;
unsigned char key;

int main() {
    LCD_init(); // home
    keypad_init();

    LCD_home();

    while(1) {
        if(keyPressed == 1) {
            GPIOIntDisable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
            state = keypad_getkey();
            SysCtlDelay(300);
            keyPressed = 0;

            if(state == 1) {
                // rtc
                LCD_reset();
                GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
                if(keyPressed == 1) {
                    GPIOIntDisable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
                }
                //rtc_init();
            }
            else if(state == 2) {
                // calc
                LCD_reset();
                GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
                if(keyPressed == 1) {
                    GPIOIntDisable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
                    key = keypad_getkey();
                    SysCtlDelay(300);
                    keyPressed = 0;

                    if (key != 0 && key != '=' && key != 'C') {
                        append(x, key);
                        LCD_data(key);
                        SysCtlDelay(150);
                    }
                    else if(key != 0 && key == '=') {
                        parser(x);
                        memset(x, 0, 255);
                        SysCtlDelay(150);
                    }
                    else if(key == 'C') {
                        LCD_reset();
                        memset(x, 0, 255);
                        SysCtlDelay(150);
                    }
                }
            }
            else if(state == 3) {
                // calc history
                LCD_reset();
                GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
                // calc_hist();
                if(keyPressed == 1) {
                    GPIOIntDisable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
                }
            }
        }
    }
}
