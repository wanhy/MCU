/******************************************************
	void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
	*@brief   GPIO引脚置高或者置低
  *@param   GPIOx : 			GPIOA 或者 GPIOB
            GPIO_Pin : 		引脚 GPIO_Pin_0 一直到 GPIO_Pin_15
						BitVal ：			Bit_SET(高电平) Bit_RESET(低电平) 		
  *@retval  无
	
	uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
	*@brief   检测GPIO引脚状态(高电平或者低电平)
  *@param   GPIOx : 			GPIOA 或者 GPIOB
            GPIO_Pin : 		引脚 GPIO_Pin_0 一直到 GPIO_Pin_15	
  *@retval  Bit_SET(高电平) Bit_RESET(低电平) 	
	
******************************************************/



#include "gpio.h"

/**
  *@brief   GPIO引脚初始化
  *@param   GPIO_X : 			GPIOA 或者 GPIOB
            GPIO_Pin_x : 	引脚 GPIO_Pin_0 一直到 GPIO_Pin_15
						statue ： 		输出或者输入 常用的有：	GPIO_Mode_Out_PP			//普通推挽输出
																									GPIO_Mode_AF_PP				//复用推挽输出
																									GPIO_Mode_AIN   			//模拟输入
																									GPIO_Mode_IN_FLOATING	//浮空输入
																									GPIO_Mode_IPD					//下拉输入
																									GPIO_Mode_IPU					//上拉输入
  *@retval  无
  */

void GPIO_init(GPIO_TypeDef *GPIO_X, uint16_t GPIO_Pin_x, GPIOMode_TypeDef statue)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    if (GPIO_X == GPIOA)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    if (GPIO_X == GPIOB)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
    GPIO_InitStructure.GPIO_Mode = statue;
		if((statue == GPIO_Mode_Out_PP)||(statue == GPIO_Mode_AF_PP))
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIO_X, &GPIO_InitStructure);
}



