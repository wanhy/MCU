#include "Ultrasonic_Wave.h"



void UltrasonicWave_Gpio_Init(void)
{
	GPIO_init(Echo_PORT_1, Ttig_1, GPIO_Mode_Out_PP); 
	GPIO_init(Echo_PORT_1, Echo_1, GPIO_Mode_IN_FLOATING); 
	GPIO_WriteBit(Echo_PORT_1, Ttig_1, Bit_RESET);
}


void UltrasonicWave_Init(void)
{
	
	
	UltrasonicWave_Gpio_Init();
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 71;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
  TIM_Cmd(TIM1, DISABLE);


}

float Get_Distance(void )
{
	
	
		float distance;
		TIM1->CNT = 0; 
		GPIO_WriteBit(Echo_PORT_1, Ttig_1, Bit_SET);
		delay_us(30);
		GPIO_WriteBit(Echo_PORT_1, Ttig_1, Bit_RESET);
		while(!GPIO_ReadInputDataBit(Echo_PORT_1,Echo_1));
		TIM_Cmd(TIM1, ENABLE);
		while(GPIO_ReadInputDataBit(Echo_PORT_1,Echo_1));
		TIM_Cmd(TIM1, DISABLE);
		distance = TIM1->CNT*0.034/2;	
		return distance;
}





