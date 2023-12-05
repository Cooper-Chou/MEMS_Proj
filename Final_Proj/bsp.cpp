#include "bsp.hpp"
#include <stdint.h>
#include <stdio.h>

#define DIVISOR 1

void bspInit()
{
    //初始化连接失败时，将消息打印到屏幕
	if(wiringPiSetup() == -1)
	{
		printf("setup wiringPi failed !");
	}

	pinMode(GPIO_RED, OUTPUT);
	digitalWrite(GPIO_RED, LOW);
	pinMode(GPIO_GREEN, OUTPUT);
	digitalWrite(GPIO_GREEN, LOW);
	pinMode(GPIO_BLUE, OUTPUT);
	digitalWrite(GPIO_BLUE, LOW);

	pinMode(GPIO_BUTTON, INPUT);
	pullUpDnControl(GPIO_BUTTON, PUD_OFF);

    pinMode(GPIO_BEEP, PWM_OUTPUT); 
	pwmWrite(GPIO_BEEP, 512);
	pwmSetClock(DIVISOR);
	pwmSetMode(PWM_MODE_MS);

    pcf8591Setup(BASE, ADDRESS);
    
    delay(100);
}

void bspLedOn(int _led_pin)
{
	digitalWrite(_led_pin, HIGH);
}

void bspLedOff(int _led_pin)
{
	digitalWrite(_led_pin, LOW);
}

void bspLedToggle(int _led_pin)
{
    if(digitalRead(_led_pin) == HIGH)
    {
        //printf("LED HIGH! To LOW!\n");
        digitalWrite(_led_pin, LOW);
    }
    else
    {
        //printf("LED LOW! To HIGH!\n");
        digitalWrite(_led_pin, HIGH);
    }
}

float bspReadBarVolt(BARS _barPort)
{
    return VCC * ((float)analogRead(_barPort)/255.0f);
}
