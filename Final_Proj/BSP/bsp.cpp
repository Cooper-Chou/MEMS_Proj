#include "bsp.hpp"
#include <stdint.h>
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "Infrared.hpp"

#define DIVISOR 1

void bspInit()
{
	wiringPiSetup();

	pinMode(GPIO_RED, OUTPUT);
	digitalWrite(GPIO_RED, LOW);
	pinMode(GPIO_GREEN, OUTPUT);
	digitalWrite(GPIO_GREEN, LOW);
	pinMode(GPIO_BLUE, OUTPUT);
	digitalWrite(GPIO_BLUE, LOW);

	pinMode(GPIO_BUTTON, INPUT);
	pullUpDnControl(GPIO_BUTTON, PUD_OFF);

	//傻逼树莓派一直tmd要sudo
	/*----------------------------------*/
    pinMode(GPIO_BEEP, PWM_OUTPUT); 
	pwmSetClock(DIVISOR);
	pwmSetMode(PWM_MODE_MS);
	/*----------------------------------*/

    pinMode(GPIO_IR, INPUT);
    wiringPiISR(GPIO_IR, INT_EDGE_FALLING, &IRhandleInput);

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

float bspReadBarPerc(int _barPort)
{
    return 2.0f*(0.5 - ((float)analogRead(_barPort)/255.0f));
}

void bspSetFreq(int _freq)
{
	// printf("SET FREQ: %d Hz!!\n", _freq);
	int range = 19200000/DIVISOR/_freq;
	pwmSetRange(range);
	pwmWrite(GPIO_BEEP, range/2);
}

int bspReadIR()
{
	//读完以后立刻清除数据，不然数据会一直存在这里
	int temp = IR_true_value;
	IR_true_value = 0;
	return temp;
}
