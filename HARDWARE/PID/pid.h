/*****************************************************
 * 山东科技大学智能车协会
 * 作者：周宏
 * 日期2021.8.24
 *****************************************************/

#ifndef __PID_H__
#define __PID_H__

#include "headfile.h"

typedef struct
{
    float Set_Vaule;     //用户设定值
    float present_Vaule; //当前值

    float P; //比例控制
    float I; //积分控制
    float D; //微分控制

    float Ek;   //本次偏差
    float Ek_1; //上次偏差
    float SEK;  //历史偏差之和
    float NEK;

    int OUT;

} PID;

extern PID pid;
void PID_init(void);
void pid_calc(void);

#endif //__PID_H__
