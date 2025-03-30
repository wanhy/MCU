#include "adc.h"

uint16_t __IO ADC_Vaule[6]; //ADC采集后的数据放到这个数组里面
//uint16_t ADC_V[6]
/**
  *@brief   ADC采集，通过DMA传输，读取时直接读取ADC_Vaule[]数组里面的值，
            一定要按照GPIO_ADC1_0_A4  -->  GPIO_ADC1_5_B1的顺序来用
  *@param   num ：ADC通道个数
            gpio_tim2_x : 引脚
  *@retval  无
  */
void ADC_init(uint16_t gpio_adc_x, uint8_t num)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_BufferSize = num;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_Vaule;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(ADC1->DR));
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel1, ENABLE);

    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_NbrOfChannel = num;
    ADC_Init(ADC1, &ADC_InitStructure);

    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    if ((gpio_adc_x & GPIO_Pin_4) == GPIO_Pin_4)
        ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_1Cycles5);
    if ((gpio_adc_x & GPIO_Pin_5) == GPIO_Pin_5)
        ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_1Cycles5);
    if ((gpio_adc_x & GPIO_Pin_6) == GPIO_Pin_6)
        ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_1Cycles5);
    if ((gpio_adc_x & GPIO_Pin_7) == GPIO_Pin_7)
        ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_1Cycles5);
    if ((gpio_adc_x & GPIO_Pin_0) == GPIO_Pin_0)
        ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 5, ADC_SampleTime_1Cycles5);
    if ((gpio_adc_x & GPIO_Pin_1) == GPIO_Pin_1)
        ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 6, ADC_SampleTime_1Cycles5);

    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1))
        ;
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1))
        ;
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    if ((gpio_adc_x & GPIO_Pin_4) == GPIO_Pin_4)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    if ((gpio_adc_x & GPIO_Pin_5) == GPIO_Pin_5)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    if ((gpio_adc_x & GPIO_Pin_6) == GPIO_Pin_6)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    if ((gpio_adc_x & GPIO_Pin_7) == GPIO_Pin_7)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    if ((gpio_adc_x & GPIO_Pin_0) == GPIO_Pin_0)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
    if ((gpio_adc_x & GPIO_Pin_1) == GPIO_Pin_1)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
}
