#include "keypad_driver.h"
#include "lcd_driver.h"

void keypad_init(void) {
    SYSCTL_RCGCGPIO_R |= 0x14; //GPIO C | GPIO E

    GPIO_PORTC_DEN_R |= 0xF0;
    GPIO_PORTC_DIR_R &= ~0xF0; //pins 4->7 as input
    GPIO_PORTC_PUR_R |= 0xF0;

    GPIO_PORTE_DEN_R |= 0x0F;
    GPIO_PORTE_DIR_R |= 0x0F; //pins 0->3 as output
}

unsigned char keypad_getkey(void) {
    const unsigned char keymap[4][4] = {
        {'1','2','3','+'},
        {'4','5','6','-'},
        {'7','8','9','C'},
        {'*','0','#','='},
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

unsigned char keypad_getchar(void) {
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
}
