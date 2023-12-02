#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <pcf8591.h>

#define BASE  64
#define ADDRESS 0x48
#define AI0 BASE+0
#define AI1 BASE+1
#define AI2 BASE+2
#define AI3 BASE+3

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
	int output = 0;

	while(1)
	{
		//scanf("%d", &output);
		output = analogRead(AI1);
		printf("Read: %d\n", output);
		analogWrite(BASE+0,output+50);
	} 
	return 0 ;
}
