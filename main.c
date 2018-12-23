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

char x[16] = "";
unsigned char key;
uint32_t pressedFlag;

int main() {
    LCD_init();
    keypad_init();

    while(1) {

        if(pressedFlag == 1){
            if (key != 0 && key != '=' && key != 'C') {
                append(x, key);
                LCD_data(key);
                pressedFlag = 0;
                SysCtlDelay(150);
            }
            else if(key != 0 && key == '=') {
                parser(x);
                memset(x, 0, 255);
                pressedFlag = 0;
                SysCtlDelay(150);
            }
            else if(key == 'C') {
                LCD_reset();
                memset(x, 0, 255);
                pressedFlag = 0;
                SysCtlDelay(150);
            }
        }

        //SysCtlDelay(7000000);
    }
}
