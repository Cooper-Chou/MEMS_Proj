#include "LED_StateDefine.hpp"
#include "LED_Controller.hpp"
#include "bsp.hpp"
#include <stdio.h>

unsigned int IR_last_us = 0;

void ledBlink(int _led_pin, State *_blinking_state)
{
    unsigned int current_tick = millis();
	// printf("last_tick: %d current_tick: %d \n", last_tick, current_tick);
   if(current_tick - IR_last_us >= LED_BLINK_PERIOD / 2)
    {
//        printf("Toggled!!\n");
        IR_last_us = current_tick;
        bspLedToggle(_led_pin);
    }
}

State_RedBlink *State_RedBlink::m_pInstance;
State_RedOn *State_RedOn::m_pInstance;
State_GreenBlink *State_GreenBlink::m_pInstance;
State_GreenOn *State_GreenOn::m_pInstance;
State_BlueBlink *State_BlueBlink::m_pInstance;
State_BlueOn *State_BlueOn::m_pInstance;


void State_RedBlink::Init(){;}

void State_RedBlink::Enter(){//printf("Entered Red Blink!\n"); 
	IR_last_us = millis();}

void State_RedBlink::Execute()
{
    ledBlink(GPIO_RED, this);
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}

void State_RedBlink::Exit(){;}



void State_RedOn::Init(){;}

void State_RedOn::Enter(){//printf("Entered Red On!\n");
}

void State_RedOn::Execute()
{
    bspLedOn(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}

void State_RedOn::Exit(){;}



void State_GreenBlink::Init(){;}

void State_GreenBlink::Enter(){//printf("Entered Green Blink!\n");
	IR_last_us = millis();}

void State_GreenBlink::Execute()
{
    bspLedOff(GPIO_RED);
    ledBlink(GPIO_GREEN, this);
    bspLedOff(GPIO_BLUE);
}

void State_GreenBlink::Exit(){;}



void State_GreenOn::Init(){;}

void State_GreenOn::Enter(){//printf("Entered Green On!\n");
}

void State_GreenOn::Execute()
{
    bspLedOff(GPIO_RED);
    bspLedOn(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}

void State_GreenOn::Exit(){;}



void State_BlueBlink::Init(){;}

void State_BlueBlink::Enter(){//printf("Entered Blue Blink!\n");
	IR_last_us = millis();}

void State_BlueBlink::Execute()
{
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    ledBlink(GPIO_BLUE, this);
}

void State_BlueBlink::Exit(){;}



void State_BlueOn::Init(){;}

void State_BlueOn::Enter(){//printf("Entered Blue On!\n");
}

void State_BlueOn::Execute()
{
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOn(GPIO_BLUE);
}

void State_BlueOn::Exit(){;}
        

        
