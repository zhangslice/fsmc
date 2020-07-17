#include "HAL_conf.h"
#include "HAL_device.h"
#include "stdio.h"
#include "string.h"
#include "lcd.h"
#include "delay.h"



int lcd_demo()
{
    u8 x=0;
    
    
    while(1) 
	{		 
		switch(x)
		{
			case 0:
                
            LCD_Clear(WHITE);break;
			case 1:LCD_Clear(BLACK);break;
			case 2:LCD_Clear(BLUE);break;
			case 3:LCD_Clear(RED);break;
			case 4:LCD_Clear(MAGENTA);break;
			case 5:LCD_Clear(GREEN);break;
			case 6:LCD_Clear(CYAN);break;

			case 7:LCD_Clear(YELLOW);break;
			case 8:LCD_Clear(BRRED);break;
			case 9:LCD_Clear(GRAY);break;
			case 10:LCD_Clear(LGRAY);break;
			case 11:LCD_Clear(BROWN);break;
		}
		POINT_COLOR=RED;	  
   					 
	    x++;
		if(x==12)x=0;
        
        delay_ms(1000);
    }
}

int main(void)
{
    delay_init();
    LCD_Init();
    POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"Mindmotion");	
	LCD_ShowString(60,70,200,16,16,"FMSC TEST");
    

    lcd_demo();
    
    while(1) {
    }
}



