#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>

#define Trig_pin 1

int main(void)
{
    wiringPiSetup();
    pinMode(Trig_pin, PWM_OUTPUT); 
    pwmWrite(Trig_pin, 512);
    float range = 0;
    int freq[] = {256, 288, 320, 341, 384, 426, 480, 512};
    for (int i = 0; i < 8; i++)
    {
        pwmSetRange(192000000/freq[i]);
        delay(500);
    }
    for (int i = 7; i >=0 ; i--)
    {
        pwmSetRange(192000000/freq[i]);
        delay(500);
    }
    pwmWrite(Trig_pin, 0);
}


