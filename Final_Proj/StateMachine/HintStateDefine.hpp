#ifndef HintStateDefine_HPP
#define HintStateDefine_HPP

#include <State.hpp>
#include <stdint.h>
#include <wiringPi.h>
#include "bsp.hpp"
#include "Music.hpp"
#include "ELectronStateDefine.hpp"
#include "GameController.hpp"

#define MAX_LED_BLINK_PERIOD 800 /* ms */
#define MIN_LED_BLINK_PERIOD 100 /* ms */
#define BEAT 300 /* ms */
#define LED_BLINK_PERIOD_LEVEL 5 //LED闪烁频率分成五个档次


void ledBlink(int _led_pin, unsigned int _blink_period, unsigned int _last_tick)
{
    unsigned int current_tick = millis();
   if(current_tick - _last_tick >= _blink_period / 2)
    {
        _last_tick = current_tick;
        bspLedToggle(_led_pin);
    }
}

class PeaceState : public State
{
    private:
        static PeaceState *m_pInstance;
    
    public:    
        Music *music;

        virtual void Init(GameController* _FSM_Owner);
        virtual void Enter(GameController* _FSM_Owner);
        virtual void Execute(GameController* _FSM_Owner);
        virtual void Exit(GameController* _FSM_Owner);

        static PeaceState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new PeaceState();
            }
            return m_pInstance;
        }
};

class BattleState : public State
{
    private:
        static BattleState *m_pInstance;
    
    public:    
        Music *music;
        Color Attacking_color;

        unsigned int led_blink_period;
        unsigned int last_led_tick;

        virtual void Init(GameController* _FSM_Owner);
        virtual void Enter(GameController* _FSM_Owner);
        virtual void Execute(GameController* _FSM_Owner);
        virtual void Exit(GameController* _FSM_Owner);

        static BattleState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new BattleState();
            }
            return m_pInstance;
        }
};

class EndingState : public State
{
    private:
        static EndingState *m_pInstance;

    public:
        Music *red_win_music;
        Music *blue_win_music;

        unsigned int led_blink_period;
        unsigned int last_led_tick_green;
        unsigned int last_led_tick_winner;
        Color winner_color;

        virtual void Init(GameController* _FSM_Owner);
        virtual void Enter(GameController* _FSM_Owner);
        virtual void Execute(GameController* _FSM_Owner);
        virtual void Exit(GameController* _FSM_Owner);

        static EndingState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new EndingState();
            }
            return m_pInstance;
        }
};

#endif
