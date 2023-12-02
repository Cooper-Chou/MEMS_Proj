#include "bsp.hpp"
#include <stdint.h>
#include <stdio.h>

void bspInit()
{
	pinMode(GPIO_RED, OUTPUT);
	digitalWrite(GPIO_RED, LOW);
	pinMode(GPIO_GREEN, OUTPUT);
	digitalWrite(GPIO_GREEN, LOW);
	pinMode(GPIO_BLUE, OUTPUT);
	digitalWrite(GPIO_BLUE, LOW);

	pinMode(GPIO_IR, INPUT);
	pullUpDnControl(GPIO_IR, PUD_OFF);
    
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
//        printf("LED HIGH! To LOW!\n");
        digitalWrite(_led_pin, LOW);
    }
    else
    {
//        printf("LED LOW! To HIGH!\n");
        digitalWrite(_led_pin, HIGH);
    }
}

uint8_t bspReadIR(int _IR_pin)
{
    if(digitalRead(_IR_pin) == HIGH)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}
