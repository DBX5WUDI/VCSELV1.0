#ifndef DELAY_H
#define DELAY_H

#include "stm32f4xx.h"	

#define SYSTEM_SUPPORT_OS		0		            //定义系统文件夹是否支持UCOS

void System_Timer_Init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);
#endif
