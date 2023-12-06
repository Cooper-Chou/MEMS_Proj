#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <pcf8591.h>
#include <math.h>

#define BASE  64
#define ADDRESS 0x48
#define AI0 BASE+0
#define AI1 BASE+1
#define AI2 BASE+2
#define AI3 BASE+3

#define VCC 5.0f
#define VBAR VCC
#define EMOJI_WIDTH 5 /* Should be ODD !!!*/
#define EMOJI_HEIGHT 3 /* Should be ODD !!!*/
#define HALF_EMOJI_WIDTH ((EMOJI_WIDTH - 1)/2)
#define HALF_EMOJI_HEIGHT ((EMOJI_HEIGHT - 1)/2)
#define CONVAS_WIDTH (232)
#define CONVAS_HEIGHT (56)

static int x_coor = CONVAS_WIDTH / 2;
static int y_coor = CONVAS_HEIGHT / 2; 

void paint()         
{
	if(x_coor < 1 + HALF_EMOJI_WIDTH)
	{
		x_coor = 1 + HALF_EMOJI_WIDTH;
	}
	else if(x_coor > CONVAS_WIDTH - HALF_EMOJI_WIDTH)
	{
		x_coor = CONVAS_WIDTH - HALF_EMOJI_WIDTH;
	}
	if(y_coor < 1 + HALF_EMOJI_HEIGHT)
	{
		y_coor = 1 + HALF_EMOJI_HEIGHT;
	}
	else if(y_coor > CONVAS_HEIGHT - HALF_EMOJI_HEIGHT)
	{
		y_coor = CONVAS_HEIGHT - HALF_EMOJI_HEIGHT;
	}

	for(int i = 0; i < y_coor - 1 - HALF_EMOJI_HEIGHT; i++)
	{
		printf("\n");
	}

	for(int i = 0; i < x_coor - HALF_EMOJI_WIDTH - 1; i++){printf(" ");}printf("\\-|-/\n");
	for(int i = 0; i < x_coor - HALF_EMOJI_WIDTH - 1; i++){printf(" ");}printf("*TAT*\n");
	for(int i = 0; i < x_coor - HALF_EMOJI_WIDTH - 1; i++){printf(" ");}printf("/-|-\\\n");

	for(int i = 0; i < CONVAS_HEIGHT - HALF_EMOJI_HEIGHT - y_coor; i++)
	{
		printf("\n");
	}
}


	

// 主函数
int main ()
{
	//初始化连接失败时，将消息打印到屏幕
	if(wiringPiSetup() == -1)
	{
		printf("setup wiringPi failed !");
		return 1; 
	}

	pcf8591Setup(BASE, ADDRESS);
    // 在基本引脚64上设置pcf8591，地址0x48
	float Vbar_x = 0.0f;
	float Vbar_y = 0.0f;
	static unsigned int count = millis();

	while(1)
	{
		if(millis() - count >= 100)
		{
			count = millis();
			Vbar_x = VCC * ((float)analogRead(AI0)/255.0f);
			Vbar_y = VCC * ((float)analogRead(AI1)/255.0f);

			x_coor += (int)(8.0f*(Vbar_x - 0.5f*VBAR) / (0.5*VBAR));
			y_coor += (int)(-4.0f*(0.5f*VBAR - Vbar_y) / (0.5*VBAR));
			//printf("x = %d, y = %d \n", x_coor, y_coor);
			//printf("Vx = %0.2f, Vy = %0.2f \n", Vbar_x, Vbar_y);
			paint();
		}
	}
	return 0 ;
}
