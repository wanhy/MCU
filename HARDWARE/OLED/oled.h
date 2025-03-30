/*****************************************************
 * 山东科技大学智能车协会
 * 作者：周宏
 * 日期2021.8.24
 *****************************************************/

#ifndef __OLED_H
#define __OLED_H

#include "stdlib.h"
#include "headfile.h"

#define OLED_MOED 0 //1为SPI接口 0为IIC接口

//接口宏定义，只需改下面宏定义就可以
#if OLED_MOED

#define SPI_RCC_APBxPeriph_GPIOx RCC_APB2Periph_GPIOB
#define GPIO_SPI GPIOB
#define OLED_SCLK GPIO_Pin_13 //PB10
#define OLED_SDIN GPIO_Pin_15 //PB11
#define OLED_RST GPIO_Pin_10  //PB11
#define OLED_DC GPIO_Pin_11   //PB11
#define OLED_CS GPIO_Pin_12   //PB11

#else

#define I2C_RCC_APBxPeriph_GPIOx RCC_APB2Periph_GPIOB
#define GPIO_I2C GPIOB
#define I2C_SCL GPIO_Pin_8 //PB8
#define I2C_SDA GPIO_Pin_9 //PB9

#endif

//-----------------OLED端口定义----------------

#if OLED_MOED

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIO_SPI, OLED_SCLK)
#define OLED_SCLK_Set() GPIO_SetBits(GPIO_SPI, OLED_SCLK)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIO_SPI, OLED_SDIN) //DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIO_SPI, OLED_SDIN)

#define OLED_RST_Clr() GPIO_ResetBits(GPIO_SPI, OLED_RST) //RES
#define OLED_RST_Set() GPIO_SetBits(GPIO_SPI, OLED_RST)

#define OLED_DC_Clr() GPIO_ResetBits(GPIO_SPI, OLED_DC) //DC
#define OLED_DC_Set() GPIO_SetBits(GPIO_SPI, OLED_DC)

#define OLED_CS_Clr() GPIO_ResetBits(GPIO_SPI, OLED_CS) //CS
#define OLED_CS_Set() GPIO_SetBits(GPIO_SPI, OLED_CS)

#else

#define OLED_SCLK_Set() GPIO_SetBits(GPIO_I2C, I2C_SCL)
#define OLED_SCLK_Clr() GPIO_ResetBits(GPIO_I2C, I2C_SCL)

#define OLED_SDIN_Set() GPIO_SetBits(GPIO_I2C, I2C_SDA)
#define OLED_SDIN_Clr() GPIO_ResetBits(GPIO_I2C, I2C_SDA)

#endif

#if OLED_MOED

void OLED_WR_Byte(u8 dat, u8 cmd);

#else

void OLED_WR_Byte(unsigned dat, unsigned cmd);
void OLED_IIC_Start(void);
void OLED_IIC_Stop(void);
void OLED_Write_IIC_Command(unsigned char IIC_Command);
void OLED_Write_IIC_Data(unsigned char IIC_Data);
void OLED_Write_IIC_Byte(unsigned char IIC_Byte);
void OLED_IIC_Wait_Ack(void);

#endif

#define OLED_CMD 0  //写命令
#define OLED_DATA 1 //写数据
#define u8 unsigned char
#define u32 unsigned int

void OLED_ClearPoint(u8 x, u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);

void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x, u8 y);					
void OLED_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2);
void OLED_DrawCircle(u8 x, u8 y, u8 r);	
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size1);
void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 size1);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size1);
void OLED_ShowChinese(u8 x, u8 y, u8 num, u8 size1);
void OLED_ScrollDisplay(u8 num, u8 space);
void OLED_WR_BP(u8 x, u8 y);
void OLED_ShowPicture(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[]);
void OLED_Init(void);

#endif
