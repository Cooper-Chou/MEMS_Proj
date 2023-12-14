#include "HintStateDefine.hpp"
#include "bsp.hpp"
#include "lyrics.hpp"
#include <stdio.h>


void State_Peace::Init(GameController* _FSM_Owner)
{
    music = new Music(peaceSong, getLength(peaceSong));
}
void State_Peace::Enter(GameController* _FSM_Owner)
{ 
    bspLedOn(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOn(GPIO_BLUE);
}
void State_Peace::Execute(GameController* _FSM_Owner)
{
    music.play();
}
void State_Peace::Exit(GameController* _FSM_Owner)
{
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}


void State_Battle::Init(GameController* _FSM_Owner)
{
    music = new Music(battleSong, getLength(battleSong));
    led_blink_period = MAX_LED_BLINK_PERIOD;
    last_led_tick = 0;
    Attacking_color = Color::NULL;
}
void State_Battle::Enter(GameController* _FSM_Owner)
{
    bspLedOn(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOn(GPIO_BLUE);
}
void State_Battle::Execute(GameController* _FSM_Owner)
{
    music.play();

    led_blink_period = ((MAX_LED_BLINK_PERIOD-MIN_LED_BLINK_PERIOD)/LED_BLINK_PERIOD_LEVEL)
                        *(RedExcitedState::GetInstance()->state_remain_ms/(EXCITED_STATE_LAST/LED_BLINK_PERIOD_LEVEL) + 1) 
                        + MIN_LED_BLINK_PERIOD;
    if(Attacking_color == Color::RED)
    {
        ledBlink(GPIO_RED, led_blink_period);
    }
    else if(Attacking_color == Color::BLUE)
    {
        ledBlink(GPIO_BLUE, led_blink_period);
    }
}
void State_Battle::Exit(GameController* _FSM_Owner)
{
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}


void State_GameEnding::Init(GameController* _FSM_Owner)
{
    red_win_music = new Music(redWinSong, getLength(redWinSong));
    blue_win_music = new Music(blueWinSong, getLength(blueWinSong));
    led_blink_period = 300;
    last_led_tick_green = 0;
    last_led_tick_winner = 0;
    winner_color = Color::NULL;
}
void State_GameEnding::Enter(GameController* _FSM_Owner)
{ 
	last_led_tick_green = millis();
    last_led_tick_winner = last_led_tick_green;
    bspLedOff(GPIO_RED);
    bspLedOn(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}
void State_GameEnding::Execute(GameController* _FSM_Owner)
{
    if(winner_color == Color::RED)
    {
        red_win_music.play();
        ledBlink(GPIO_RED, led_blink_period, last_led_tick_winner);
        ledBlink(GPIO_GREEN, led_blink_period, last_led_tick_green);
    }
    else if(winner_color == Color::BLUE)
    {
        blue_win_music.play();
        ledBlink(GPIO_BLUE, led_blink_period, last_led_tick_winner);
        ledBlink(GPIO_GREEN, led_blink_period, last_led_tick_green);
    }
}
void State_GameEnding::Exit(GameController* _FSM_Owner)
{
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}