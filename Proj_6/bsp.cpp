#include "bsp.hpp"
#include <stdint.h>
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <unistd.h>
#include <softPwm.h>
#include <signal.h>

#define DIVISOR 1

void bspInit()
{
	wiringPiSetup();
    pinMode(GPIO_BEEP, PWM_OUTPUT);
	pwmSetClock(DIVISOR);
	pwmSetMode(PWM_MODE_MS);
    delay(100);
}

void bspSetFreq(int _freq)
{
	printf("Set Freq!! ");
	int range = 19200000/DIVISOR/_freq;
	pwmSetRange(range);
	pwmWrite(GPIO_BEEP, range/2);
}
