#include "HintStateDefine.hpp"
#include "../BSP/bsp.hpp"
#include <stdio.h>
#include "GameController.hpp"

void ledBlink(int _led_pin, unsigned int _blink_period, unsigned int _last_tick)
{
    unsigned int current_tick = millis();
   if(current_tick - _last_tick >= _blink_period / 2)
    {
        _last_tick = current_tick;
        bspLedToggle(_led_pin);
    }
}

void PeaceState::Init(GameController* _FSM_Owner)
{
    p_music = p_peace;
}
void PeaceState::Enter(GameController* _FSM_Owner)
{ 
    bspLedOn(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOn(GPIO_BLUE);
}
void PeaceState::Execute(GameController* _FSM_Owner)
{
    p_music->play();
}
void PeaceState::Exit(GameController* _FSM_Owner)
{
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}


void BattleState::Init(GameController* _FSM_Owner)
{
    p_music = p_battle;
    led_blink_period = MAX_LED_BLINK_PERIOD;
    last_led_tick = 0;
}
void BattleState::Enter(GameController* _FSM_Owner)
{
    bspLedOn(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOn(GPIO_BLUE);
}
void BattleState::Execute(GameController* _FSM_Owner)
{
    p_music->play();

    led_blink_period = ((MAX_LED_BLINK_PERIOD-MIN_LED_BLINK_PERIOD)/LED_BLINK_PERIOD_LEVEL)
                        *(_FSM_Owner->battle_state_remain_ms/(EXCITED_STATE_LAST/LED_BLINK_PERIOD_LEVEL) + 1) 
                        + MIN_LED_BLINK_PERIOD;
    if(_FSM_Owner->game_state_color == Color::RED)
    {
        ledBlink(GPIO_RED, led_blink_period, last_led_tick);
    }
    else if(_FSM_Owner->game_state_color == Color::BLUE)
    {
        ledBlink(GPIO_BLUE, led_blink_period, last_led_tick);
    }
}
void BattleState::Exit(GameController* _FSM_Owner)
{
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}


void EndState::Init(GameController* _FSM_Owner)
{
    red_win_p_music = p_redWin;
    blue_win_p_music = p_blueWin;
    led_blink_period = 300;
    last_led_tick_green = 0;
    last_led_tick_winner = 0;
}
void EndState::Enter(GameController* _FSM_Owner)
{ 
	last_led_tick_green = millis();
    last_led_tick_winner = last_led_tick_green;
    bspLedOff(GPIO_RED);
    bspLedOn(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}
void EndState::Execute(GameController* _FSM_Owner)
{
    if(_FSM_Owner->game_state_color == Color::RED)
    {
        red_win_p_music->play();
        ledBlink(GPIO_RED, led_blink_period, last_led_tick_winner);
        ledBlink(GPIO_GREEN, led_blink_period, last_led_tick_green);
    }
    else if(_FSM_Owner->game_state_color == Color::BLUE)
    {
        blue_win_p_music->play();
        ledBlink(GPIO_BLUE, led_blink_period, last_led_tick_winner);
        ledBlink(GPIO_GREEN, led_blink_period, last_led_tick_green);
    }
}
void EndState::Exit(GameController* _FSM_Owner)
{
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}