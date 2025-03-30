#ifndef __USART1_H__
#define __USART1_H__

#include "stm32f10x.h"
#include "delay.h"
#include "stdio.h"

#include "led.h"
#include "tim.h"
#include "usart1.h"

#define USART_LENGTH 20 //字符串最大接收长度

extern u8 str_usart1_rex[20];
extern uint8_t flag_usart1;
extern uint8_t index_usart1;

void USART1_Init(uint32_t Baud_Rate);
void SendStr(u8 *str);

#endif //__USART1_H__
