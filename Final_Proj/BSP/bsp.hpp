#ifndef bsp_HPP
#define bsp_HPP

#include <wiringPi.h> 
#include <stdint.h>
#include <pcf8591.h>

#define BASE  64
#define ADDRESS 0x48
#define AI0 BASE+0
#define AI1 BASE+1
#define AI2 BASE+2
#define AI3 BASE+3

#define VCC 5.0f

#define GPIO_IR 4
#define GPIO_RED 29
#define GPIO_GREEN 28
#define GPIO_BLUE 27
#define GPIO_BUTTON 5
#define GPIO_BEEP 1

/*
Bar1X --> AIN0
Bar1Y --> AIN1
Bar2X --> AIN2
Bar2Y --> AIN3
*/

enum BARS
{
    Bar1X = AI0,
    Bar1Y = AI1,
    Bar2X = AI2,
    Bar2Y = AI3
};

void bspInit(void);
void bspLedOn(int _led_pin);
void bspLedOff(int _led_pin);
void bspLedToggle(int _led_pin);
void bspSetFreq(int _freq);
float bspReadBarVolt(BARS _barPort);
int bspReadIR();

template <class T>
int getLength(T& array)
{
 	return (sizeof(array) / sizeof(array[0]));
}

#endif
