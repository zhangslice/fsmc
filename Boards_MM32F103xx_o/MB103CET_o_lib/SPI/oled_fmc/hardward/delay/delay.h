#ifndef __DELAY_H
#define __DELAY_H
//#include "sys.h"

#include "HAL_conf.h"
#include "HAL_device.h"
//////////////////////////////////////////////////////////////////////////////////
//开发板
//使用SysTick的普通计数模式对延迟进行管理
//包括delay_us,delay_ms

//////////////////////////////////////////////////////////////////////////////////
extern u32 SystemCoreClock;

void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif





























