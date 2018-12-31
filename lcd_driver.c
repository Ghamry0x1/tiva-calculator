#include "lcd_driver.h"

void LCD_init(void)
{
  SYSCTL_RCGCGPIO_R |= 0x03; // Enable clock for GPIOA GPIOB
  
  GPIO_PORTA_DEN_R |= 0xE0;
  GPIO_PORTA_DIR_R |= 0xE0; // pins 5->7 output
  
  GPIO_PORTB_DEN_R |= 0xFF;
  GPIO_PORTB_DIR_R |= 0xFF; //pins output
  
  //initialization 
  delayMs(20);
  LCD_command(0x30);
  delayMs(5);
  LCD_command(0x30);
  delayUs(100);
  LCD_command(0x30);
  
  LCD_command(0x38);
  LCD_command(0x06);
  LCD_command(0x01); //clear
  LCD_command(0x0F); //display on
}

void LCD_reset(void)
{
   LCD_command(0x80);
   LCD_command(0x01);
}

void LCD_data(unsigned char data)
{
  GPIO_PORTA_DATA_R = 0x20; //RS = 1
  GPIO_PORTB_DATA_R = data;
  GPIO_PORTA_DATA_R = 0xA0;
  GPIO_PORTA_DATA_R = 0;
  delayUs(40);
}

void LCD_command(unsigned char command)
{
  GPIO_PORTA_DATA_R = 0; // RS = 0
  GPIO_PORTB_DATA_R = command;
  GPIO_PORTA_DATA_R = 0x80;
  GPIO_PORTA_DATA_R = 0;
  if (command < 4)
    delayMs(2);
  else
    delayUs(40);
}

void LCD_home(void)
{
    LCD_data('1');
    delayMs(4);
    LCD_data('-');
    delayMs(4);
    LCD_data('R');
    delayMs(4);
    LCD_data('T');
    delayMs(4);
    LCD_data('C');
    delayMs(4);

    LCD_data(' ');
    delayMs(4);
    LCD_data(' ');
    delayMs(4);

    LCD_data('2');
    delayMs(4);
    LCD_data('-');
    delayMs(4);
    LCD_data('C');
    delayMs(4);
    LCD_data('A');
    delayMs(4);
    LCD_data('L');
    delayMs(4);
    LCD_data('C');
    delayMs(4);

    LCD_command(0xC0);
    delayMs(4);

    LCD_data('3');
    delayMs(4);
    LCD_data('-');
    delayMs(4);
    LCD_data('H');
    delayMs(4);
    LCD_data('I');
    delayMs(4);
    LCD_data('S');
    delayMs(4);
    LCD_data('T');
    delayMs(4);
    LCD_data('O');
    delayMs(4);
    LCD_data('R');
    delayMs(4);
    LCD_data('Y');
    delayMs(4);
}

void delayMs(int n) // 16 MHz CPU Clock
{
    int i, j;
        for(i=0; i<n; i++) {
            for(j=0; j < 3180; j++) {}
        }
}

void delayUs(int n)
{
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j < 3; j++) {}
    }
}
