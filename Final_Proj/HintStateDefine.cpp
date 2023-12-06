#include "HintStateDefine.hpp"
#include "AttackController.hpp"
#include "bsp.hpp"
#include "lyrics.hpp"
#include <stdio.h>

void State_RedBlink::Init()
{
    blink_period = MAX_LED_BLINK_PERIOD;
    last_tick = 0;
}
void State_RedBlink::Enter()
{
	last_tick = millis();
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}
void State_RedBlink::Execute()
{
    ledBlink(GPIO_RED, blink_period, last_tick);
}
void State_RedBlink::Exit(){;}


void State_BlueBlink::Init()
{
    blink_period = MAX_LED_BLINK_PERIOD;
    last_tick = 0;
}
void State_BlueBlink::Enter()
{
	last_tick = millis();
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
}
void State_BlueBlink::Execute()
{
    ledBlink(GPIO_BLUE, blink_period, last_tick);
}
void State_BlueBlink::Exit(){;}


void State_Off::Init(){;}
void State_Off::Enter()
{ 
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}
void State_Off::Execute(){;}
void State_Off::Exit(){;}


void State_PurpleOn::Init(){;}
void State_PurpleOn::Enter()
{ 
    bspLedOn(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOn(GPIO_BLUE);
}
void State_PurpleOn::Execute(){;}
void State_PurpleOn::Exit(){;}


void State_GameEnding::Init()
{
    blink_period = MAX_LED_BLINK_PERIOD;
    last_tick = 0;
}
void State_GameEnding::Enter()
{ 
	last_tick = millis();
    bspLedOff(GPIO_RED);
    bspLedOn(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}
void State_GameEnding::Execute()
{
	bspSetFreq(MySong[songIndex]);
    if(millis() - last_tick >= BEAT)
    {
        songIndex++;
        if(songIndex >= songLength)
        {
            songIndex = 0;
        }
    }
    ledBlink(winner_led_pin, BEAT, last_tick);
    ledBlink(GPIO_GREEN, BEAT, last_tick);
}
void State_GameEnding::Exit()
{
	pwmWrite(GPIO_BEEP, 0);
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}