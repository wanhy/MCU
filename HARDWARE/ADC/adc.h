/*****************************************************
 * 山东科技大学智能车协会
 * 作者：周宏
 * 日期2021.8.24
 *****************************************************/

#ifndef __ADC_H__
#define __ADC_H__
#include "headfile.h"

#define AD_LL ADC_Vaule[3]
#define AD_LV ADC_Vaule[2]
#define AD_RR ADC_Vaule[0]
#define AD_RV ADC_Vaule[1]

typedef enum
{
    GPIO_ADC1_0_A4 = GPIO_Pin_4,
    GPIO_ADC1_1_A5 = GPIO_Pin_5,
    GPIO_ADC1_2_A6 = GPIO_Pin_6,
    GPIO_ADC1_3_A7 = GPIO_Pin_7,
    GPIO_ADC1_4_B0 = GPIO_Pin_0,
    GPIO_ADC1_5_B1 = GPIO_Pin_1
} gpio_adc_x;

extern __IO uint16_t ADC_Vaule[6];

void ADC_init(uint16_t gpio_adc_x, uint8_t num);

#endif
