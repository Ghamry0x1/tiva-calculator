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
            state = keypad_getkey();
            SysCtlDelay(300);
            keyPressed = 0;

            if(state == 1) {
                // rtc
                LCD_reset();
                //rtc_init();
            }
            else if(state == 2) {
                // calc
                LCD_reset();
                if(keyPressed == 1) {
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
                // calc_hist();
            }
        }
    }
}
