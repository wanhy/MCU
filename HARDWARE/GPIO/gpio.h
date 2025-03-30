/*****************************************************
 * 山东科技大学智能车协会
 * 作者：周宏
 * 日期2021.8.24
 *****************************************************/

#ifndef __GPIO_H__
#define __GPIO_H__

#include "headfile.h"

#define HIGH Bit_SET
#define LOW Bit_RESET

void GPIO_init(GPIO_TypeDef *GPIO_X, uint16_t GPIO_Pin_x, GPIOMode_TypeDef statue);

#endif
