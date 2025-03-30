/******************************************************
	void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1);
	void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2);
	void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16_t Compare3);
	void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare4);
	*@brief   设置定时器通道一到通道四的比较值
  *@param   TIMx : 							TIM2、TIM3、TIM4
            Compare1(2,3,4) : 	定时器的比较值	
  *@retval  无	
******************************************************/

#include "tim.h"

/**
  *@brief   定时器2输出PWM波初始化
  *@param   fre ：频率 
            zkb : 占空比 0-1000
            gpio_tim2_x : 引脚
  *@retval  无
  */

void TIM2_PWM_init(uint16_t fre, uint16_t zkb, uint16_t gpio_tim2_x)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 999; //
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72000000 / (fre * 1000) - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    TIM_Cmd(TIM2, ENABLE);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_Pulse = zkb;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

    if ((gpio_tim2_x & GPIO_TIM2_A0) == GPIO_TIM2_A0)
        TIM_OC1Init(TIM2, &TIM_OCInitStructure);
    if ((gpio_tim2_x & GPIO_TIM2_A1) == GPIO_TIM2_A1)
        TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    if ((gpio_tim2_x & GPIO_TIM2_A2) == GPIO_TIM2_A2)
        TIM_OC3Init(TIM2, &TIM_OCInitStructure);
    if ((gpio_tim2_x & GPIO_TIM2_A3) == GPIO_TIM2_A3)
        TIM_OC4Init(TIM2, &TIM_OCInitStructure);

    GPIO_InitStructure.GPIO_Pin = gpio_tim2_x;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  *@brief   定时器3输出PWM波初始化
  *@param   fre ：频率 
            zkb : 占空比 
            gpio_tim2_x : 引脚
  *@retval  无
  */

void TIM3_PWM_init(uint16_t fre, uint16_t zkb, uint16_t gpio_tim3_x)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    if (((gpio_tim3_x & GPIO_TIM3_A6) == GPIO_TIM3_A6) || ((gpio_tim3_x & GPIO_TIM3_A7) == GPIO_TIM3_A7))
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    if (((gpio_tim3_x & GPIO_TIM3_B0) == GPIO_TIM3_B0) || ((gpio_tim3_x & GPIO_TIM3_B1) == GPIO_TIM3_B1))
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 999; //
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72000000 / (fre * 1000) - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
    TIM_Cmd(TIM3, ENABLE);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_Pulse = zkb;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

    if ((gpio_tim3_x & GPIO_TIM3_A6) == GPIO_TIM3_A6)
        TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    if ((gpio_tim3_x & GPIO_TIM3_A7) == GPIO_TIM3_A7)
        TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    if ((gpio_tim3_x & GPIO_TIM3_B0) == GPIO_TIM3_B0)
        TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    if ((gpio_tim3_x & GPIO_TIM3_B1) == GPIO_TIM3_B1)
        TIM_OC4Init(TIM3, &TIM_OCInitStructure);

    GPIO_InitStructure.GPIO_Pin = gpio_tim3_x;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    if (((gpio_tim3_x & GPIO_TIM3_A6) == GPIO_TIM3_A6) || ((gpio_tim3_x & GPIO_TIM3_A7) == GPIO_TIM3_A7))
        GPIO_Init(GPIOA, &GPIO_InitStructure);

    if (((gpio_tim3_x & GPIO_TIM3_B0) == GPIO_TIM3_B0) || ((gpio_tim3_x & GPIO_TIM3_B1) == GPIO_TIM3_B1))
        GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  *@brief   定时器4输出PWM波初始化
  *@param   fre ：频率 
            zkb : 占空比 
            gpio_tim2_x : 引脚
  *@retval  无
  */

void TIM4_PWM_init(uint16_t fre, uint16_t zkb, uint16_t gpio_tim4_x)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 999; //
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72000000 / (fre * 1000) - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
    TIM_Cmd(TIM4, ENABLE);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_Pulse = zkb;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    if ((gpio_tim4_x & GPIO_TIM4_B6) == GPIO_TIM4_B6)
        TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    if ((gpio_tim4_x & GPIO_TIM4_B7) == GPIO_TIM4_B7)
        TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    if ((gpio_tim4_x & GPIO_TIM4_B8) == GPIO_TIM4_B8)
        TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    if ((gpio_tim4_x & GPIO_TIM4_B9) == GPIO_TIM4_B9)
        TIM_OC4Init(TIM4, &TIM_OCInitStructure);

    GPIO_InitStructure.GPIO_Pin = gpio_tim4_x;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  *@brief   定时器2初始化，定时时间=a*b/72000000
  *@param   a,b都不能超过65535 
  *@retval  无
  */

void TIM2_init(uint16_t a, uint16_t b)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = a;
    TIM_TimeBaseInitStructure.TIM_Prescaler = b;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  *@brief   定时器2的中断程序，定时器3计时满后自动跳转到这个程序，需要自己写定时器中断的内容
  *@param   无
  *@retval  无
  */

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {
        //pid_calc();
        /****************自己在这写代码***************/

        /****************************************/

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

/**
  *@brief   定时器3初始化，定时时间=a*b/72000000
  *@param   a,b都不能超过65535 
  *@retval  无
  */

void TIM3_init(uint16_t a, uint16_t b)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = a;
    TIM_TimeBaseInitStructure.TIM_Prescaler = b;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  *@brief   定时器3的中断程序，定时器3计时满后自动跳转到这个程序，需要自己写定时器中断的内容
  *@param   无
  *@retval  无
  */

void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update))
    {
        //pid_calc();
        /****************自己在这写代码***************/

        /****************************************/

        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

/**
  *@brief   定时器4初始化，定时时间=a*b/72000000
  *@param   a,b都不能超过65535 
  *@retval  无
  */

void TIM4_init(uint16_t a, uint16_t b)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = a;
    TIM_TimeBaseInitStructure.TIM_Prescaler = b;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  *@brief   定时器3的中断程序，定时器3计时满后自动跳转到这个程序，需要自己写定时器中断的内容
  *@param   无
  *@retval  无
  */

void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update))
    {
        //pid_calc();
        /****************自己在这写代码***************/

        /****************************************/

        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}

/**
  *@brief   把TIM2初始化为编码器接口模式
  *@param   无
  *@retval  无
  */

void Encoder_Init_TIM2(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能定时器4的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PB端口时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
  TIM_TimeBaseStructure.TIM_Period = 65535; //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM2,0);
  TIM_Cmd(TIM2, ENABLE); 
}

/**
  *@brief   把TIM4初始化为编码器接口模式
  *@param   无
  *@retval  无
  */

void Encoder_Init_TIM4(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器4的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PB端口时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
  TIM_TimeBaseStructure.TIM_Period = 65535; //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4, ENABLE); 
}

/**
  *@brief   单位时间读取编码器计数
  *@param   定时器（数字）
  *@retval  速度值
  */


int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		 default: Encoder_TIM=0;
	 }
		return Encoder_TIM;
}


