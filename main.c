#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/eeprom.h"
#include "lcd_driver.h"
#include "keypad_driver.h"
#include "parser_module.h"

int row, keyPressed;
char state;
unsigned char key;

int main() {
    LCD_init(); // home
    keypad_init();

    SysCtlDelay(300);

    LCD_home();

    while(1) {
        if(keyPressed == 1) {
            state = keypad_getkey();

            GPIOIntDisable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
            SysCtlDelay(3000);

            keyPressed = 0;

            if(state == '1') {
                // RTC
                LCD_reset();
                GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);

                if(keyPressed == 1) {
                    GPIOIntDisable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
                    SysCtlDelay(3000);
                    //rtc_init();
                }
            }
            else if(state == '2') {
                // CALC
                LCD_reset();
                GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
                SysCtlDelay(300);

                if(keyPressed == 1) {
                    key = keypad_getkey();

                    GPIOIntDisable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
                    SysCtlDelay(3000);

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
            else if(state == '3') {
                // EEPROM
                LCD_reset();
                GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
                if(keyPressed == 1) {
                    GPIOIntDisable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
                    SysCtlDelay(3000);

                    keyPressed = 0;

                    uint32_t eeprom_status = EEPROMInit();
                    if(eeprom_status == 1) {

                    }
                }
            }
        }
    }
}
