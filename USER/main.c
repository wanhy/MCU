
#include "headfile.h"

//Ttig  ---> PB10

//Echo  ---> PB11


int main(void)
{
		unsigned char str[20];
		float distance = 0;
		
    delay_init();
    delay_ms(20);
	
		OLED_Init();
		delay_ms(20);
		OLED_ColorTurn(0);//0正常显示，1 反色显示
		OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
		OLED_Refresh();
	
		//超声波初始化
		UltrasonicWave_Init();
	
    while (1)
    {
			distance = Get_Distance();
			sprintf(str,"distance :%3.3f",distance);
			OLED_ShowString(0,12,str,12);
			OLED_Refresh();
			delay_ms(100);
			
    }
}







