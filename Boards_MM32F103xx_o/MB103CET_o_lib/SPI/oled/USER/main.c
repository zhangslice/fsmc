#include "HAL_conf.h"
#include "HAL_device.h"
#include "stdio.h"
#include "string.h"
#include "oled.h"
#include "delay.h"

#include "font.h"

#define WIDTH       320                 /* Screen Width (in pixels)           */
#define HEIGHT      240                 /* Screen Hight (in pixels)           */
#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255, 0   */
#define White           0xFFFF      /* 255, 255, 255 */



void OLED_SetPos(unsigned char x, unsigned char y) //设置起始点坐标
{ 
	//WriteCmdStart();
    OLED_WR_Byte(0x80,OLED_CMD);
   // WriteCmd(0xb0+(y&0x0f));
    OLED_WR_Byte(0xb0+(y&0x0f),OLED_DATA);
	//WriteEnd();	
	//WriteCmdStart();
    OLED_WR_Byte(0x80,OLED_CMD);
   // WriteCmd(((x&0xf0)>>4)|0x10);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_DATA);
	//WriteEnd();	
	//WriteCmdStart();
    OLED_WR_Byte(0x80,OLED_CMD);
    //WriteCmd((x&0x0f)|0x01);
    OLED_WR_Byte((x&0x0f)|0x01,OLED_DATA);
	//WriteEnd();	
}

int OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
    unsigned char c = 0,i = 0,j = 0;
    switch(TextSize)
    {
        case 1:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                OLED_SetPos(x,y);
				//WriteDataStart();
                for(i=0;i<8;i++)
                    OLED_WR_Byte(Font_6x8_h[c*8+i],OLED_DATA);
				//WriteEnd();	
                y--;
                j++;
            }
        }break;
		
		case 2:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                OLED_SetPos(x,y);
				//WriteDataStart();
                for(i=0;i<12;i++)
                    OLED_WR_Byte(Font_8x12_h[c*12+i],OLED_DATA);
				//WriteEnd();	
                y--;
                j++;
            }
        }break;
		
        case 3:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                OLED_SetPos(x,y);
				//WriteDataStart();
                for(i=0;i<16;i++)
                    OLED_WR_Byte(Font_8x16_h[c*16+i],OLED_DATA);
				//WriteEnd();	
                y--;
                j++;
            }
        }break;
		
		
		default:
			return 1;
    }
	return 0;
}


int main(void)
{
    unsigned char str[]="Hello!";
    u8 x=0;
    u8 t=0;	
    u16 color;
    delay_init();
    OLED_Init();		//初始化OLED

    OLED_Fill(0,0,127,63,0xFF);
   OLED_Clear(); 
    
  	OLED_ShowString(5,0,"Mindmotion",16);  
	OLED_ShowString(5,24, "0.96' OLED TEST",16);  
 	OLED_ShowString(5,40,"ATOM 2020/7/10",12);  
 	OLED_ShowString(0,52,"ASCII:",12);  
 	OLED_ShowString(64,52,"CODE:",12);  
	OLED_Refresh_Gram();//更新显示到OLED	 
	t=' ';  
	while(1) 
	{		
       // OLED_Fill(0,0,100,60,1);
		OLED_ShowChar(36,52,t,12,1);//显示ASCII字符	
		OLED_ShowNum(94,52,t,3,12);	//显示ASCII字符的码值    
		OLED_Refresh_Gram();//更新显示到OLED
		t++;
		if(t>'~')t=' ';  
		delay_ms(500);
	}	 

}