#ifndef HintStateDefine_HPP
#define HintStateDefine_HPP

#include <State.hpp>
#include <stdint.h>
#include <wiringPi.h>
#include "bsp.hpp"
#include "Music.hpp"
#include "Electron.hpp"
#include "ElectronStateDefine.hpp"

#define MAX_LED_BLINK_PERIOD 1000 /* ms */
#define MIN_LED_BLINK_PERIOD 100 /* ms */
#define BEAT 300 /* ms */
#define LED_BLINK_PERIOD_LEVEL 5

void ledBlink(int _led_pin, unsigned int _blink_period, unsigned int _last_tick)
{
    unsigned int current_tick = millis();
   if(current_tick - _last_tick >= _blink_period / 2)
    {
        _last_tick = current_tick;
        bspLedToggle(_led_pin);
    }
}

class State_Peace : public State
{
    private:
        static State_Peace *m_pInstance;
    
    public:    
        Music music;

        virtual void Init();
        virtual void Enter();
        virtual void Execute();
        virtual void Exit();

        static State_Peace* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new State_Peace();
            }
            return m_pInstance;
        }
};

class State_Battle : public State
{
    private:
        static State_Battle *m_pInstance;
    
    public:    
        Music music;
        Color Attacking_color;

        unsigned int state_entering_tick;
        unsigned int led_blink_period;
        unsigned int last_led_tick;

        virtual void Init();
        virtual void Enter();
        virtual void Execute();
        virtual void Exit();

        static State_Battle* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new State_Battle();
            }
            return m_pInstance;
        }
};

class State_GameEnding : public State
{
    private:
        static State_GameEnding *m_pInstance;

    public:
        Music red_win_music;
        Music blue_win_music;

        unsigned int led_blink_period;
        unsigned int last_led_tick_green;
        unsigned int last_led_tick_winner;
        Color winner_color;

        virtual void Init();
        virtual void Enter();
        virtual void Execute();
        virtual void Exit();

        static State_GameEnding* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new State_GameEnding();
            }
            return m_pInstance;
        }
};

#endif
