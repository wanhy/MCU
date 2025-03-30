#include "usart1.h"

u8 str_usart1_rex[USART_LENGTH];
uint8_t flag_usart1 = 0;
uint8_t index_usart1 = 0;

/**
  *@brief   串口1初始化
  *@param   Baud_Rate：波特率 
  *@retval  无
  */

void USART1_Init(uint32_t Baud_Rate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = Baud_Rate;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  *@brief   串口1发送函数，最好配合sprintf函数使用
  *@param   str：要发送字符串的地址
  *@retval  无
  */

void SendStr(u8 *str)
{
    u8 i = 0;
    while (str[i] != 0)
    {
        USART_SendData(USART1, str[i++]);
        while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE))
            ;
    }
}

/**
  *@brief   串口1中断函数，不用管
  *@param   无
  *@retval  无
  */
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE))
    {
        flag_usart1 = 1;
        str_usart1_rex[index_usart1++] = USART_ReceiveData(USART1);
        ;
    }
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

/**
  *@brief   串口1接收函数，接收到的字符串一定要在这里处理，其他地方不会显示，接收到的字符串首地址是str_usart1_rex
  *@param   无
  *@retval  无
  */
void USART1_Receive_Str(void)
{
    if (flag_usart1 == 1)
    {
        TIM3_delay_ms(20);
        flag_usart1 = 0;
        /***********这里处理接收到的字符串***********/

        /******************************************/
        for (index_usart1 = 0; index_usart1 < USART_LENGTH; index_usart1++)
            str_usart1_rex[index_usart1] = 0;
    }
}
