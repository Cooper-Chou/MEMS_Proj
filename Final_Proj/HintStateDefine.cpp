#include "HintStateDefine.hpp"
#include "GameController.hpp"
#include "bsp.hpp"
#include "lyrics.hpp"
#include <stdio.h>


void State_Peace::Init()
{
    music = new Music(peaceSong, getLength(peaceSong));
}
void State_Peace::Enter()
{ 
    bspLedOn(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOn(GPIO_BLUE);
}
void State_Peace::Execute()
{
    music.play();
}
void State_Peace::Exit()
{
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}


void State_Battle::Init()
{
    music = new Music(battleSong, getLength(battleSong));
    led_blink_period = MAX_LED_BLINK_PERIOD;
    last_led_tick = 0;
    state_entering_tick = 0;
    Attacking_color = Color::NULL;
}
void State_Battle::Enter()
{
    state_entering_tick = millis();
    bspLedOn(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOn(GPIO_BLUE);
}
void State_Battle::Execute()
{
    music.play();

    led_blink_period = MAX_LED_BLINK_PERIOD*(millis() - state_entering_tick)/(EXCITED_STATE_LAST/LED_BLINK_PERIOD_LEVEL)
    if(Attacking_color == Color::RED)
    {
        ledBlink(GPIO_RED, led_blink_period);
    }
    else if(Attacking_color == Color::BLUE)
    {
        ledBlink(GPIO_BLUE, led_blink_period);
    }
}
void State_Battle::Exit()
{
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}


void State_GameEnding::Init()
{
    red_win_music = new Music(redWinSong, getLength(redWinSong));
    blue_win_music = new Music(blueWinSong, getLength(blueWinSong));
    led_blink_period = 300;
    last_led_tick_green = 0;
    last_led_tick_winner = 0;
    winner_color = Color::NULL;
}
void State_GameEnding::Enter()
{ 
	last_led_tick_green = millis();
    last_led_tick_winner = last_led_tick_green;
    bspLedOff(GPIO_RED);
    bspLedOn(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}
void State_GameEnding::Execute()
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
void State_GameEnding::Exit()
{
    bspLedOff(GPIO_RED);
    bspLedOff(GPIO_GREEN);
    bspLedOff(GPIO_BLUE);
}