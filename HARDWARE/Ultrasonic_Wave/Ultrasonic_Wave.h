#ifndef __ULRASONIC_WAVE_H__
#define __ULRASONIC_WAVE_H__


#include "headfile.h"

#define Ttig_1 					GPIO_Pin_10
#define Echo_1 					GPIO_Pin_11
#define Echo_PORT_1 		GPIOB
#define Trig_Clock_1  	RCC_APB2Periph_GPIOB



void UltrasonicWave_Init(void);
float Get_Distance(void );

float aaa(void);
float bbb(void);


#endif //__ULRASONIC_WAVE_H__
