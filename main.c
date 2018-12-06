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

int main() {
    unsigned char key;
    char x[16] = "";
    LCD_init();
    keypad_init();

    while(1) {
        key = keypad_getchar();

        if (key != 0 && key != '='){
            append(x, key);
            LCD_data(key);
        }
		else if(key != 0 && key == '=') 
			parser(x);
		
        delayMs(180);
    }
}
