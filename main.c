//#include "ports.h"
#include "lcd_driver.h"
#include "keypad_driver.h"

int main()
{
  unsigned char key;
  
  keypad_init();
  LCD_init();
 
  while(1)
  { 
    
    key = keypad_getchar();
    if (key != 0)
        LCD_data(key);
    
    delayMs(20);
        
  }
  
  
  return 0;
}