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

typedef struct
{
  __IO uint32_t SSCONR;     //0
	__IO uint32_t STMG0R;     //4
	__IO uint32_t STMG1R;     //8
	__IO uint32_t SCTLR;      //c
	__IO uint32_t SREFR;      //10
	__IO uint32_t SCSLR0_LOW; //14
	__IO uint32_t SCSLR1_LOW; //18
	__IO uint32_t SCSLR2_LOW; //1c
	__IO uint32_t SCSLR3_LOW; //20
	__IO uint32_t SCSLR4_LOW; //24
	__IO uint32_t SCSLR5_LOW; //28
	__IO uint32_t SCSLR6_LOW; //2c
	__IO uint32_t SCSLR7_LOW; //30
	__IO uint32_t RESERVED0;  //34
	__IO uint32_t RESERVED1;  //38
	__IO uint32_t RESERVED2;  //3c
	__IO uint32_t RESERVED3;  //40
	__IO uint32_t RESERVED4;  //44
	__IO uint32_t RESERVED5;  //48
	__IO uint32_t RESERVED6;  //4c
	__IO uint32_t RESERVED7;  //50
	__IO uint32_t SMSKR0;     //54
	__IO uint32_t SMSKR1;     //58
	__IO uint32_t SMSKR2;     //5c
	__IO uint32_t SMSKR3;     //60
	__IO uint32_t SMSKR4;     //64
	__IO uint32_t SMSKR5;     //68
	__IO uint32_t SMSKR6;     //6c
	__IO uint32_t SMSKR7;     //70
	__IO uint32_t CSALIAS0_LOW;  //74
	__IO uint32_t CSALIAS1_LOW;  //78
	__IO uint32_t RESERVED8;     //7c
	__IO uint32_t RESERVED9;     //80
	__IO uint32_t CSREMAP0_LOW;  //84
	__IO uint32_t CSREMAP1_LOW;  //88
	__IO uint32_t RESERVED10;    //8c
	__IO uint32_t RESERVED11;    //90
	__IO uint32_t SMTMGR_SET0;   //94
	__IO uint32_t SMTMGR_SET1;   //98
	__IO uint32_t SMTMGR_SET2;   //9c
	__IO uint32_t FLASH_TRPDR;   //a0
	__IO uint32_t SMCTLR;        //a4
	__IO uint32_t RESERVED17;    //a8
	__IO uint32_t EXN_MODE_REG;  //ac	
} FSMC_TypeDef;
//#define FSMC_R_BASE           (0xA0000000)
#define FSMC                 ((FSMC_TypeDef *) FSMC_R_BASE)
void FSMC_Init(void)
{

	//  tBTA[18:16]  tWP[15:10] tWR[9:8] tAS[7:6] tRC[5:0]
	FSMC->SMTMGR_SET0 = 0x0<<16|0x30<<10|0x1<<8|0x1<<6|0x1<<0;    //时间设置
//	*((volatile unsigned int*)0x40010000) &= 0xffffffff; 
//	 *((volatile unsigned int*)0x40010000) = (0x2<<29);  //moto680
	*((volatile unsigned int*)0x40010000) = (0x1<<29); //TK80        //模式设置
//	*((volatile unsigned int*)0x40010000) = (0x0<<29);
	//FSMC->SMTMGR_SET2 = 0x1bc4;     
//	temp = FSMC->SMTMGR_SET0;
	 //FSMC->SMTMGR_SET0 = 0x1<<16|0x10<<10|0x2<<8|0x1<<6|0x1f<<0;    //时间设置
	FSMC->SMCTLR =0x0<<13 | 0x0<<10 | 0x0<<7;            //data width
////	temp = FSMC->SMTMGR_SET2;
//	// reg_select[10:8] mem_type[7:5]  mem_size[4:0]
	FSMC->SMSKR0 = 0x0<<8 | 0x1<<5 | 0x4; //select register set 0 sram 512KB
//	temp = FSMC->SMSKR0;
	FSMC->SCSLR0_LOW = 0x00020000;//有疑问  写数据 读数据寄存器  地址如何给
//	temp = FSMC->SMCTLR;
	
}


int main(void)
{
 //   unsigned char str[]="Hello!";
//    u8 x=0;
    u8 t=0;	
//    u16 color;
    delay_init();

    RCC->AHB3ENR |= 0x01; //enable FSMCEN
	RCC->APB2ENR |= 0x1<<14;//open sys_cfg clk
    FSMC_Init();
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