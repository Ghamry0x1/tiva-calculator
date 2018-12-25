#include "keypad_driver.h"
#include "lcd_driver.h"
#include "parser_module.h"

char x[16] = "";

void keypad_init(void) {
    SysCtlClockSet(SYSCTL_SYSDIV_2_5| SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE) && !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)) {}
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
    GPIO_PORTC_PUR_R |= 0xF0;

    GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_FALLING_EDGE);
    GPIOIntRegister(GPIO_PORTC_BASE, keypad_isr_handler);
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
    IntMasterEnable();
}

void keypad_isr_handler(void) {
    uint32_t status = 0;
    status = GPIOIntStatus(GPIO_PORTC_BASE, true);
    GPIOIntClear(GPIO_PORTC_BASE, status);

    unsigned char key;
    key = keypad_getkey();

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

    SysCtlDelay(7000000);
}

unsigned char keypad_getkey(void) {
    const unsigned char keymap[4][4] = {
        {'1','2','3','+'},
        {'4','5','6','-'},
        {'7','8','9','*'},
        {'C','0','=','/'},
    };

    int row, col;
    GPIO_PORTE_DATA_R = 0;
    col = GPIO_PORTC_DATA_R & 0xF0;
    if(col == 0xF0)
        return 0;
    
    while(1) {
        row = 0;
        GPIO_PORTE_DATA_R = 0x0E; //row 0
        delayUs(2);
        col = GPIO_PORTC_DATA_R & 0xF0;
        if(col != 0xF0)
            break;

        row = 1;
        GPIO_PORTE_DATA_R = 0x0D; //row 1
        delayUs(2);
        col = GPIO_PORTC_DATA_R & 0xF0;
        if(col != 0xF0)
          break;

        row = 2;
        GPIO_PORTE_DATA_R = 0x0B; //row 2
        delayUs(2);
        col = GPIO_PORTC_DATA_R & 0xF0;
        if(col != 0xF0)
          break;

        row = 3;
        GPIO_PORTE_DATA_R = 0x07; //row 3
        delayUs(2);
        col = GPIO_PORTC_DATA_R & 0xF0;
        if(col != 0xF0)
          break;

        return 0;
    }
  
    if(col == 0xE0)
        return keymap[row][0]; //col 0
    if(col == 0xD0)
        return keymap[row][1]; //col 1
    if(col == 0xB0)
        return keymap[row][2]; //col 2
    if(col == 0x70)
        return keymap[row][3]; //col 3

    return 0;
}
