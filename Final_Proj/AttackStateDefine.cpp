#include "AttackStateDefine.hpp"
#include "bsp.hpp"
#include <stdio.h>

void State_Ground::Init()
{
    blink_period = MAX_LED_BLINK_PERIOD;
    last_tick = 0;
}
void State_Ground::Enter()
{
	last_tick = millis();
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}
void State_Ground::Execute()
{
}
void State_Ground::Exit(){;}