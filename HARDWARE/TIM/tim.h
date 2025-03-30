/*****************************************************
 * 山东科技大学智能车协会
 * 作者：周宏
 * 日期2021.8.24
 *****************************************************/

#ifndef __TIM_H__
#define __TIM_H__

#include "headfile.h"

#define GPIO_TIM2_A0 GPIO_Pin_0
#define GPIO_TIM2_A1 GPIO_Pin_1
#define GPIO_TIM2_A2 GPIO_Pin_2
#define GPIO_TIM2_A3 GPIO_Pin_3

#define GPIO_TIM3_A6 GPIO_Pin_6
#define GPIO_TIM3_A7 GPIO_Pin_7
#define GPIO_TIM3_B0 GPIO_Pin_0
#define GPIO_TIM3_B1 GPIO_Pin_1

#define GPIO_TIM4_B6 GPIO_Pin_6
#define GPIO_TIM4_B7 GPIO_Pin_7
#define GPIO_TIM4_B8 GPIO_Pin_8
#define GPIO_TIM4_B9 GPIO_Pin_9

void TIM2_init(uint16_t a, uint16_t b);
void TIM3_init(uint16_t a, uint16_t b);
void TIM4_init(uint16_t a, uint16_t b);
void TIM2_PWM_init(uint16_t fre, uint16_t zkb, uint16_t gpio_tim2_x);
void TIM3_PWM_init(uint16_t fre, uint16_t zkb, uint16_t gpio_tim3_x);
void TIM4_PWM_init(uint16_t fre, uint16_t zkb, uint16_t gpio_tim4_x);
void Encoder_Init_TIM2(void);
void Encoder_Init_TIM4(void);
int Read_Encoder(u8 TIMX);

#endif //__TIM_H__
