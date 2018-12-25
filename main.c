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

int row;

int main() {
    LCD_init();
    keypad_init();

    while(1) {
        ;
    }
}
