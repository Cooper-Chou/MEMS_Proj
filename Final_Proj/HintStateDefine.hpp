#ifndef HintStateDefine_HPP
#define HintStateDefine_HPP

#include <State.hpp>
#include <stdint.h>
#include <wiringPi.h>
#include "bsp.hpp"

#define MAX_LED_BLINK_PERIOD 500 /*ms*/
#define MIN_LED_BLINK_PERIOD 100 /*ms*/
#define BEAT 300 /* ms */

void ledBlink(int _led_pin, unsigned int _blink_period, unsigned int _last_tick)
{
    unsigned int current_tick = millis();
   if(current_tick - _last_tick >= _blink_period / 2)
    {
        _last_tick = current_tick;
        bspLedToggle(_led_pin);
    }
}

class State_RedBlink : public State
{
    private:
        static State_RedBlink *m_pInstance;

    public:
        unsigned int blink_period;
        unsigned int last_tick;

        virtual void Init();
        virtual void Enter();
        virtual void Execute();
        virtual void Exit();

        static State_RedBlink* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new State_RedBlink();
            }
            return m_pInstance;
        }
};

class State_BlueBlink : public State
{
    private:
        static State_BlueBlink *m_pInstance;
        
    public:    
        unsigned int blink_period;
        unsigned int last_tick;

        virtual void Init();
        virtual void Enter();
        virtual void Execute();
        virtual void Exit();

        static State_BlueBlink* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new State_BlueBlink();
            }
            return m_pInstance;
        }
};

class State_Off : public State
{
    private:
        static State_Off *m_pInstance;
    
    public:    
        virtual void Init();
        virtual void Enter();
        virtual void Execute();
        virtual void Exit();

        static State_Off* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new State_Off();
            }
            return m_pInstance;
        }
};

class State_PurpleOn : public State
{
    private:
        static State_PurpleOn *m_pInstance;
    
    public:    
        virtual void Init();
        virtual void Enter();
        virtual void Execute();
        virtual void Exit();

        static State_PurpleOn* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new State_PurpleOn();
            }
            return m_pInstance;
        }
};

class State_GameEnding : public State
{
    private:
        static State_GameEnding *m_pInstance;

    public:
        unsigned int blink_period;
        unsigned int last_tick;
        int songIndex;
        int winner_led_pin;

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
