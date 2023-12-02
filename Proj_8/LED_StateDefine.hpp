#ifndef LED_StateDefine_HPP
#define LED_StateDefine_HPP

#include <State.hpp>
#include <stdint.h>
#include <wiringPi.h>

#define LED_BLINK_PERIOD 300 /*ms*/

void ledBlink(int _led_pin, State *_blinking_state);

class State_RedBlink : public State
{
    private:
        static State_RedBlink *m_pInstance;

    public:
        unsigned int blink_period = LED_BLINK_PERIOD;

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

class State_RedOn : public State
{
    private:
        static State_RedOn *m_pInstance;
    
    public:    
        virtual void Init();
        virtual void Enter();
        virtual void Execute();
        virtual void Exit();

        static State_RedOn* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new State_RedOn();
            }
            return m_pInstance;
        }
};

class State_GreenBlink : public State
{
    private:
        static State_GreenBlink *m_pInstance;
        
    public:    
        unsigned int blink_period = LED_BLINK_PERIOD;

        virtual void Init();
        virtual void Enter();
        virtual void Execute();
        virtual void Exit();

        static State_GreenBlink* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new State_GreenBlink();
            }
            return m_pInstance;
        }
};

class State_GreenOn : public State
{
    private:
        static State_GreenOn *m_pInstance;
    
    public:    
        virtual void Init();
        virtual void Enter();
        virtual void Execute();
        virtual void Exit();

        static State_GreenOn* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new State_GreenOn();
            }
            return m_pInstance;
        }
};

class State_BlueBlink : public State
{
    private:
        static State_BlueBlink *m_pInstance;
        
    public:    
        unsigned int blink_period = LED_BLINK_PERIOD;

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

class State_BlueOn : public State
{
    private:
        static State_BlueOn *m_pInstance;
    
    public:    
        virtual void Init();
        virtual void Enter();
        virtual void Execute();
        virtual void Exit();

        static State_BlueOn* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new State_BlueOn();
            }
            return m_pInstance;
        }
};

#endif
