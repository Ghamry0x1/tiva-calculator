#include "keypad_isr.h"
#include "keypad_driver.h"
#include "lcd_driver.h"

void keypad_isr_init(void) {
    GPIOIntEnable(GPIO_PORTE_BASE, GPIO_INT_PIN_0);
    GPIOIntEnable(GPIO_PORTE_BASE, GPIO_INT_PIN_1);
    GPIOIntEnable(GPIO_PORTE_BASE, GPIO_INT_PIN_2);
    GPIOIntEnable(GPIO_PORTE_BASE, GPIO_INT_PIN_3);

    GPIOIntRegisterPin(GPIO_PORTE_BASE, GPIO_INT_PIN_0, keypad_isr_handler);
    GPIOIntRegisterPin(GPIO_PORTE_BASE, GPIO_INT_PIN_1, keypad_isr_handler);
    GPIOIntRegisterPin(GPIO_PORTE_BASE, GPIO_INT_PIN_2, keypad_isr_handler);
    GPIOIntRegisterPin(GPIO_PORTE_BASE, GPIO_INT_PIN_3, keypad_isr_handler);
}

void keypad_isr_handler(void) {
    unsigned char key;
    key = keypad_getchar();
    if(key != 0)
        LCD_data(key);
}


