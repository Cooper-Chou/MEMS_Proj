#ifndef AttackStateDefine_HPP
#define AttackStateDefine_HPP

#include <State.hpp>
#include <stdint.h>
#include <wiringPi.h>

class State_Ground : public State
{
    private:
        static State_Ground *m_pInstance;

    public:
        unsigned int blink_period;
        unsigned int last_tick;

        virtual void Init();
        virtual void Enter();
        virtual void Execute();
        virtual void Exit();

        static State_Ground* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new State_Ground();
            }
            return m_pInstance;
        }
};

class State_Excited : public State
{
    private:
        static State_Excited *m_pInstance;

    public:
        unsigned int blink_period;
        unsigned int last_tick;

        virtual void Init();
        virtual void Enter();
        virtual void Execute();
        virtual void Exit();

        static State_Excited* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new State_Excited();
            }
            return m_pInstance;
        }
};


#endif
