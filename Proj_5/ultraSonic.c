#include <wiringPi.h>
#include <stdint.h>
#include <stdio.h>

#define GPIO_TRIG 28
#define GPIO_ECHO 29

int main()
{
	//初始化连接失败时，将消息打印到屏幕
	if(wiringPiSetup() == -1)
	{
		printf("setup wiringPi failed !");
		return 1;
	}

	pinMode(GPIO_TRIG, OUTPUT);
	digitalWrite(GPIO_TRIG, LOW);

	pinMode(GPIO_ECHO, INPUT);
	pullUpDnControl(GPIO_ECHO, PUD_OFF);

    delay(100);

	while(1)
	{
		//输入一个短脉冲
		int tick = 0;
		digitalWrite(GPIO_TRIG, HIGH);
		delayMicroseconds(20);
		digitalWrite(GPIO_TRIG, LOW);

		//测量折返时间
		while(digitalRead(GPIO_ECHO) == LOW){;}
		tick = micros();
		while(digitalRead(GPIO_ECHO) == HIGH){;}
		int time = micros() - tick;

		float distance = (float)time * 0.0001f  * 170.0f;
		printf("The distance is %.5f cm\n", distance);
		
		delay(200);
	}

	return 0;
}
