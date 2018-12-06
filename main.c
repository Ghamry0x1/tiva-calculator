#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "lcd_driver.h"
#include "keypad_driver.h"

int main() {
    LCD_init();
    keypad_init();

    while(1) {}
}
