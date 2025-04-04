/*****************************************************
 * 山东科技大学智能车协会
 * 作者：周宏
 * 日期2021.8.24
 *****************************************************/

#include "oled.h"
#include "oledfont.h"
u8 OLED_GRAM[144][8];

//反显函数
void OLED_ColorTurn(u8 i)
{
    if (i == 0)
    {
        OLED_WR_Byte(0xA6, OLED_CMD); //正常显示
    }
    if (i == 1)
    {
        OLED_WR_Byte(0xA7, OLED_CMD); //反色显示
    }
}

//屏幕旋转180度
void OLED_DisplayTurn(u8 i)
{
    if (i == 0)
    {
        OLED_WR_Byte(0xC8, OLED_CMD); //正常显示
        OLED_WR_Byte(0xA1, OLED_CMD);
    }
    if (i == 1)
    {
        OLED_WR_Byte(0xC0, OLED_CMD); //反转显示
        OLED_WR_Byte(0xA0, OLED_CMD);
    }
}

#if OLED_MOED

void OLED_WR_Byte(u8 dat, u8 cmd)
{
    u8 i;
    if (cmd)
        OLED_DC_Set();
    else
        OLED_DC_Clr();
    OLED_CS_Clr();
    for (i = 0; i < 8; i++)
    {
        OLED_SCLK_Clr();
        if (dat & 0x80)
            OLED_SDIN_Set();
        else
            OLED_SDIN_Clr();
        OLED_SCLK_Set();
        dat <<= 1;
    }
    OLED_CS_Set();
    OLED_DC_Set();
}

#else

void OLED_IIC_Start()
{

    OLED_SCLK_Set();
    OLED_SDIN_Set();
    OLED_SDIN_Clr();
    OLED_SCLK_Clr();
}

void OLED_IIC_Stop()
{
    OLED_SCLK_Set();
    //	OLED_SCLK_Clr();
    OLED_SDIN_Clr();
    OLED_SDIN_Set();
}

void OLED_IIC_Wait_Ack()
{

    //GPIOB->CRH &= 0XFFF0FFFF;	//����PB12Ϊ��������ģʽ
    //GPIOB->CRH |= 0x00080000;
    //	OLED_SDA = 1;
    //	delay_us(1);
    //OLED_SCL = 1;
    //delay_us(50000);
    /*	while(1)
	{
		if(!OLED_SDA)				//�ж��Ƿ���յ�OLED Ӧ���ź�
		{
			//GPIOB->CRH &= 0XFFF0FFFF;	//����PB12Ϊͨ���������ģʽ
			//GPIOB->CRH |= 0x00030000;
			return;
		}
	}
*/
    OLED_SCLK_Set();
    OLED_SCLK_Clr();
}

void OLED_Write_IIC_Byte(unsigned char IIC_Byte)
{
    unsigned char i;
    unsigned char m, da;
    da = IIC_Byte;
    OLED_SCLK_Clr();
    for (i = 0; i < 8; i++)
    {
        m = da;
        //	OLED_SCLK_Clr();
        m = m & 0x80;
        if (m == 0x80)
        {
            OLED_SDIN_Set();
        }
        else
            OLED_SDIN_Clr();
        da = da << 1;
        OLED_SCLK_Set();
        OLED_SCLK_Clr();
    }
}

void OLED_Write_IIC_Command(unsigned char IIC_Command)
{
    OLED_IIC_Start();
    OLED_Write_IIC_Byte(0x78); //Slave address,SA0=0
    OLED_IIC_Wait_Ack();
    OLED_Write_IIC_Byte(0x00); //write command
    OLED_IIC_Wait_Ack();
    OLED_Write_IIC_Byte(IIC_Command);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
}

void OLED_Write_IIC_Data(unsigned char IIC_Data)
{
    OLED_IIC_Start();
    OLED_Write_IIC_Byte(0x78); //D/C#=0; R/W#=0
    OLED_IIC_Wait_Ack();
    OLED_Write_IIC_Byte(0x40); //write data
    OLED_IIC_Wait_Ack();
    OLED_Write_IIC_Byte(IIC_Data);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
}

void OLED_WR_Byte(unsigned dat, unsigned cmd)
{
    if (cmd)
    {
        OLED_Write_IIC_Data(dat);
    }
    else
    {
        OLED_Write_IIC_Command(dat);
    }
}

#endif

//开启OLED显示
void OLED_DisPlay_On(void)
{
    OLED_WR_Byte(0x8D, OLED_CMD); //��ɱ�ʹ��
    OLED_WR_Byte(0x14, OLED_CMD); //������ɱ�
    OLED_WR_Byte(0xAF, OLED_CMD); //������Ļ
}

//关闭OLED显示
void OLED_DisPlay_Off(void)
{
    OLED_WR_Byte(0x8D, OLED_CMD); //��ɱ�ʹ��
    OLED_WR_Byte(0x10, OLED_CMD); //�رյ�ɱ�
    OLED_WR_Byte(0xAF, OLED_CMD); //�ر���Ļ
}

//更新显存到OLED
void OLED_Refresh(void)
{
    u8 i, n;
    for (i = 0; i < 8; i++)
    {
        OLED_WR_Byte(0xb0 + i, OLED_CMD); //��������ʼ��ַ
        OLED_WR_Byte(0x00, OLED_CMD);     //���õ�����ʼ��ַ
        OLED_WR_Byte(0x10, OLED_CMD);     //���ø�����ʼ��ַ
        for (n = 0; n < 128; n++)
            OLED_WR_Byte(OLED_GRAM[n][i], OLED_DATA);
    }
}
//清屏函数
void OLED_Clear(void)
{
    u8 i, n;
    for (i = 0; i < 8; i++)
    {
        for (n = 0; n < 128; n++)
        {
            OLED_GRAM[n][i] = 0; //�����������
        }
    }
    OLED_Refresh(); //������ʾ
}

//画点
//x:0~127
//y:0~63
void OLED_DrawPoint(u8 x, u8 y)
{
    u8 i, m, n;
    i = y / 8;
    m = y % 8;
    n = 1 << m;
    OLED_GRAM[x][i] |= n;
}

//清除一个点
//x:0~127
//y:0~63
void OLED_ClearPoint(u8 x, u8 y)
{
    u8 i, m, n;
    i = y / 8;
    m = y % 8;
    n = 1 << m;
    OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
    OLED_GRAM[x][i] |= n;
    OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
}

//画线
//x:0~128
//y:0~64
void OLED_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2)
{
    u8 i, k, k1, k2;//y0;
    if ((x1 <= 0) || (x2 > 128) || (y1 <= 0) || (y2 > 64) || (x1 > x2) || (y1 > y2))
        return;
    if (x1 == x2) //������
    {
        for (i = 0; i < (y2 - y1); i++)
        {
            OLED_DrawPoint(x1, y1 + i);
        }
    }
    else if (y1 == y2) //������
    {
        for (i = 0; i < (x2 - x1); i++)
        {
            OLED_DrawPoint(x1 + i, y1);
        }
    }
    else //��б��
    {
        k1 = y2 - y1;
        k2 = x2 - x1;
        k = k1 * 10 / k2;
        for (i = 0; i < (x2 - x1); i++)
        {
            OLED_DrawPoint(x1 + i, y1 + i * k / 10);
        }
    }
}
//x,y:圆心坐标
//r:圆的半径
void OLED_DrawCircle(u8 x, u8 y, u8 r)
{
    int a, b, num;
    a = 0;
    b = r;
    while (2 * b * b >= r * r)
    {
        OLED_DrawPoint(x + a, y - b);
        OLED_DrawPoint(x - a, y - b);
        OLED_DrawPoint(x - a, y + b);
        OLED_DrawPoint(x + a, y + b);

        OLED_DrawPoint(x + b, y + a);
        OLED_DrawPoint(x + b, y - a);
        OLED_DrawPoint(x - b, y - a);
        OLED_DrawPoint(x - b, y + a);

        a++;
        num = (a * a + b * b) - r * r; //���㻭�ĵ���Բ�ĵľ���
        if (num > 0)
        {
            b--;
            a--;
        }
    }
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//size:选择字体 12/16/24
//取模方式 逐列式
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size1)
{
    u8 i, m, temp, size2, chr1;
    u8 y0 = y;
    size2 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * (size1 / 2); //�õ�����һ���ַ���Ӧ������ռ���ֽ���
    chr1 = chr - ' ';                                          //����ƫ�ƺ��ֵ
    for (i = 0; i < size2; i++)
    {
        if (size1 == 12)
        {
            temp = asc2_1206[chr1][i];
        } //����1206����
        else if (size1 == 16)
        {
            temp = asc2_1608[chr1][i];
        } //����1608����
        else if (size1 == 24)
        {
            temp = asc2_2412[chr1][i];
        } //����2412����
        else
            return;
        for (m = 0; m < 8; m++) //д������
        {
            if (temp & 0x80)
                OLED_DrawPoint(x, y);
            else
                OLED_ClearPoint(x, y);
            temp <<= 1;
            y++;
            if ((y - y0) == size1)
            {
                y = y0;
                x++;
                break;
            }
        }
    }
}

//显示字符串
//x,y:起点坐标
//size1:字体大小
//*chr:字符串起始地址
void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 size1)
{
    while ((*chr >= ' ') && (*chr <= '~')) //�ж��ǲ��ǷǷ��ַ�!
    {
        OLED_ShowChar(x, y, *chr, size1);
        x += size1 / 2;
        if (x > 128 - size1) //����
        {
            x = 0;
            y += 2;
        }
        chr++;
    }
}

//m^n
u32 OLED_Pow(u8 m, u8 n)
{
    u32 result = 1;
    while (n--)
    {
        result *= m;
    }
    return result;
}

////显示2个数字
////x,y :起点坐标
////len :数字的位数
////size:字体大小
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size1)
{
    u8 t, temp;
    for (t = 0; t < len; t++)
    {
        temp = (num / OLED_Pow(10, len - t - 1)) % 10;
        if (temp == 0)
        {
            OLED_ShowChar(x + (size1 / 2) * t, y, '0', size1);
        }
        else
        {
            OLED_ShowChar(x + (size1 / 2) * t, y, temp + '0', size1);
        }
    }
}

//显示汉字
//x,y:起点坐标
//num:汉字对应的序号
//取模方式 列行式
void OLED_ShowChinese(u8 x, u8 y, u8 num, u8 size1)
{
    u8 i, m, n = 0, temp, chr1;
    u8 x0 = x, y0 = y;
    u8 size3 = size1 / 8;
    while (size3--)
    {
        chr1 = num * size1 / 8 + n;
        n++;
        for (i = 0; i < size1; i++)
        {
            if (size1 == 16)
            {
                temp = Hzk1[chr1][i];
            } //����16*16����
            else if (size1 == 24)
            {
                temp = Hzk2[chr1][i];
            } //����24*24����
            else if (size1 == 32)
            {
                temp = Hzk3[chr1][i];
            } //����32*32����
            else if (size1 == 64)
            {
                temp = Hzk4[chr1][i];
            } //����64*64����
            else
                return;

            for (m = 0; m < 8; m++)
            {
                if (temp & 0x01)
                    OLED_DrawPoint(x, y);
                else
                    OLED_ClearPoint(x, y);
                temp >>= 1;
                y++;
            }
            x++;
            if ((x - x0) == size1)
            {
                x = x0;
                y0 = y0 + 8;
            }
            y = y0;
        }
    }
}

//num 显示汉字的个数
//space 每一遍显示的间隔
void OLED_ScrollDisplay(u8 num, u8 space)
{
    u8 i, n, t = 0, m = 0, r;
    while (1)
    {
        if (m == 0)
        {
            OLED_ShowChinese(128, 24, t, 16); //д��һ�����ֱ�����OLED_GRAM[][]������
            t++;
        }
        if (t == num)
        {
            for (r = 0; r < 16 * space; r++) //��ʾ���
            {
                for (i = 0; i < 144; i++)
                {
                    for (n = 0; n < 8; n++)
                    {
                        OLED_GRAM[i - 1][n] = OLED_GRAM[i][n];
                    }
                }
                OLED_Refresh();
            }
            t = 0;
        }
        m++;
        if (m == 16)
        {
            m = 0;
        }
        for (i = 0; i < 144; i++) //ʵ������
        {
            for (n = 0; n < 8; n++)
            {
                OLED_GRAM[i - 1][n] = OLED_GRAM[i][n];
            }
        }
        OLED_Refresh();
    }
}

//配置写入数据的起始位置
void OLED_WR_BP(u8 x, u8 y)
{
    OLED_WR_Byte(0xb0 + y, OLED_CMD); //��������ʼ��ַ
    OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
    OLED_WR_Byte((x & 0x0f), OLED_CMD);
}

//x0,y0：起点坐标
//x1,y1：终点坐标
//BMP[]：要写入的图片数组
void OLED_ShowPicture(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[])
{
    u32 j = 0;
    u8 x = 0, y = 0;
    if (y % 8 == 0)
        y = 0;
    else
        y += 1;
    for (y = y0; y < y1; y++)
    {
        OLED_WR_BP(x0, y);
        for (x = x0; x < x1; x++)
        {
            OLED_WR_Byte(BMP[j], OLED_DATA);
            j++;
        }
    }
}
//OLED的初始化
void OLED_Init(void)
{

#if OLED_MOED
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(SPI_RCC_APBxPeriph_GPIOx, ENABLE); //ʹ��A�˿�ʱ��
    GPIO_InitStructure.GPIO_Pin = OLED_SCLK | OLED_SDIN | OLED_RST | OLED_DC | OLED_CS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ�50MHz
    GPIO_Init(GPIO_SPI, &GPIO_InitStructure);         //��ʼ��GPIOD3,6
    GPIO_SetBits(GPIO_SPI, OLED_SCLK | OLED_SDIN | OLED_RST | OLED_DC | OLED_CS);

    OLED_RST_Set();
    delay_ms(100);
    OLED_RST_Clr(); //��λ
    delay_ms(200);
    OLED_RST_Set();

#else

    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(I2C_RCC_APBxPeriph_GPIOx, ENABLE);
    //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    GPIO_InitStructure.GPIO_Pin = I2C_SCL | I2C_SDA;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_I2C, &GPIO_InitStructure);

    GPIO_SetBits(GPIO_I2C, I2C_SCL | I2C_SDA);

    //	GPIO_InitTypeDef  GPIO_InitStructure;
    //	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	 //ʹ��B�˿�ʱ��
    //	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    //	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
    // 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    //	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
    // 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOB8,9
    // 	GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);

#endif

    OLED_WR_Byte(0xAE, OLED_CMD); //--turn off oled panel
    OLED_WR_Byte(0x00, OLED_CMD); //---set low column address
    OLED_WR_Byte(0x10, OLED_CMD); //---set high column address
    OLED_WR_Byte(0x40, OLED_CMD); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_Byte(0x81, OLED_CMD); //--set contrast control register
    OLED_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
    OLED_WR_Byte(0xA1, OLED_CMD); //--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
    OLED_WR_Byte(0xC8, OLED_CMD); //Set COM/Row Scan Direction   0xc0���·��� 0xc8����
    OLED_WR_Byte(0xA6, OLED_CMD); //--set normal display
    OLED_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3f, OLED_CMD); //--1/64 duty
    OLED_WR_Byte(0xD3, OLED_CMD); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_Byte(0x00, OLED_CMD); //-not offset
    OLED_WR_Byte(0xd5, OLED_CMD); //--set display clock divide ratio/oscillator frequency
    OLED_WR_Byte(0x80, OLED_CMD); //--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_Byte(0xD9, OLED_CMD); //--set pre-charge period
    OLED_WR_Byte(0xF1, OLED_CMD); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_Byte(0xDA, OLED_CMD); //--set com pins hardware configuration
    OLED_WR_Byte(0x12, OLED_CMD);
    OLED_WR_Byte(0xDB, OLED_CMD); //--set vcomh
    OLED_WR_Byte(0x40, OLED_CMD); //Set VCOM Deselect Level
    OLED_WR_Byte(0x20, OLED_CMD); //-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WR_Byte(0x02, OLED_CMD); //
    OLED_WR_Byte(0x8D, OLED_CMD); //--set Charge Pump enable/disable
    OLED_WR_Byte(0x14, OLED_CMD); //--set(0x10) disable
    OLED_WR_Byte(0xA4, OLED_CMD); // Disable Entire Display On (0xa4/0xa5)
    OLED_WR_Byte(0xA6, OLED_CMD); // Disable Inverse Display On (0xa6/a7)
    OLED_WR_Byte(0xAF, OLED_CMD);
    OLED_Clear();
}
