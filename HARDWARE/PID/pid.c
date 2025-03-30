/*****************************************************
 * 山东科技大学智能车协会
 * 作者：周宏
 * 日期2021.8.24
 *****************************************************/

#include "pid.h"

float Kp = 200;
float Kd = 600;

PID pid;

void PID_init(void)
{
    pid.Set_Vaule = 0;
    pid.P = 200;
    pid.I = 0;
    pid.D = 600;
    pid.Ek = 0;
    pid.SEK = 0;
    pid.OUT = 0;
}

//float err_mohu[] = {-0.9, -0.6, -0.3, 0, 0.3, 0.6, 0.9};

void pid_calc(void)
{
    char str[8];
    double DelEk;
    double err;

    int Pout;

    int Dout;

    err = (double)((AD_LL - AD_RR) + (AD_LV - AD_RV)) / ((AD_LL + AD_RR) + (AD_LV - AD_RV));

    if (err > 1)
        err = 1;
    else if (err < -1)
        err = -1;

    pid.present_Vaule = err;

    pid.Ek_1 = pid.Ek;
    pid.Ek = pid.Set_Vaule - pid.present_Vaule; //得到当前的偏差值
    pid.SEK += pid.Ek;                          //历史偏差总和
    DelEk = pid.Ek - pid.Ek_1;                  //最近两次偏差之差

    Pout = (int)(pid.P * pid.Ek); //比例输出
    Dout = (int)(pid.D * DelEk);  //微分输出

    pid.OUT = Pout + Dout;

    TIM_SetCompare3(TIM2, 800 - pid.OUT);
    TIM_SetCompare4(TIM2, 300 - pid.OUT);

    sprintf(str, "%.2lf  %2d  %2d", err, Pout, Dout);
    // OLED_ShowString(0, 0, str, 12);
}
