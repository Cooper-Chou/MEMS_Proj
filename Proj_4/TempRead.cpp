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

#define R0 10000.0f /*Ohm*/
#define T0 298.15f /*Kelvin*/
#define B 3950.0f /*Kelvin*/
#define VCC 3.3f 


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
	float Vtemp = 0.0f;
	float Rtemp = 0.0f;
	float Temp = 0.0f;

	while(1)
	{
		//scanf("%d", &output);
		Vtemp = VCC * (((float)analogRead(AI3))/255.0f);
		Rtemp = R0 * Vtemp / (VCC - Vtemp);
		Temp = 1/(log(Rtemp/R0)/B + 1/T0) - T0 + 25.0f;

		printf("Temperature: %f°C\n", Temp);
		analogWrite(BASE, (int)(200.0f*(Temp-20.0f)/20.0f));
		delay(200);
	} 
	return 0 ;
}
