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
    LCD_data('-');
    LCD_data('R');
    LCD_data('T');
    LCD_data('C');

    LCD_data(' ');
    LCD_data(' ');

    LCD_data('2');
    LCD_data('-');
    LCD_data('C');
    LCD_data('A');
    LCD_data('L');
    LCD_data('C');

    LCD_command(0xC0);

    LCD_data('3');
    LCD_data('-');
    LCD_data('H');
    LCD_data('I');
    LCD_data('S');
    LCD_data('T');
    LCD_data('O');
    LCD_data('R');
    LCD_data('Y');

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
