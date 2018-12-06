#include "keypad_driver.h"
#include "lcd_driver.h"

void keypad_init(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE) && !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)) {}
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
    GPIO_PORTC_PUR_R |= 0xF0;

    /*GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_RISING_EDGE);
    GPIOIntRegister(GPIO_PORTC_BASE, keypad_isr_handler);
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
    IntMasterEnable();*/
}

void keypad_isr_handler(void) {
    uint32_t status = 0;
    status = GPIOIntStatus(GPIO_PORTC_BASE, true);
    GPIOIntClear(GPIO_PORTC_BASE, status);

    if((status & GPIO_INT_PIN_4) == GPIO_INT_PIN_4) {
        //Then there was a pin4 interrupt
        GPIO_PORTE_DATA_R = 0x0E; //row 0
        if(GPIO_PORTC_DATA_R == ~(GPIO_INT_PIN_4)) {
            printf("pin 0 row 4");
        }
    }

    if((status & GPIO_INT_PIN_5) == GPIO_INT_PIN_5) {
        //Then there was a pin5 interrupt
        GPIO_PORTE_DATA_R = 0x0E; //row 0
        if(GPIO_PORTC_DATA_R == ~(GPIO_INT_PIN_5)) {
            printf("pin 0 row 4");
        }
    }

    if((status & GPIO_INT_PIN_6) == GPIO_INT_PIN_6) {
        //Then there was a pin6 interrupt
        GPIO_PORTE_DATA_R = 0x0E; //row 0
        if(GPIO_PORTC_DATA_R == ~(GPIO_INT_PIN_6)) {
            printf("pin 0 row 0");
        }
    }

    if((status & GPIO_INT_PIN_7) == GPIO_INT_PIN_7) {
        //Then there was a pin7 interrupt
        GPIO_PORTE_DATA_R = 0x0E; //row 0
        if(GPIO_PORTC_DATA_R == ~(GPIO_INT_PIN_7)) {
            printf("pin 7 row 0");
        }
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
    
    int row,col;
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

/*unsigned char keypad_getchar(void) {
    unsigned char key;
    do{
        while(keypad_getkey() != 0);
            delayMs(20);
    }while(keypad_getkey() != 0);
    
    do{
        key = keypad_getkey();
        delayMs(20);
    }while(keypad_getkey() != key); 
   
    if(key == 'C') {
        LCD_reset();
        return 0;
    }

    return key;
}*/

unsigned char keypad_getchar(void) {
    unsigned char key;
    
    do{
        key = keypad_getkey();
        delayMs(20);
    }while(keypad_getkey() != key); 
   
    if(key == 'C') {
        LCD_reset();
        return 0;
    }

    return key;
}


/*If we used this version of the function 
we'll have to delay 20ms after calling LCD_data(key)
either in the main or in the interrupt*/
/*unsigned char keypad_getchar(void) {
    unsigned char key;
    
    key = keypad_getkey();
   
    if(key == 'C') {
        LCD_reset();
        return 0;
    }

    return key;
}*/




