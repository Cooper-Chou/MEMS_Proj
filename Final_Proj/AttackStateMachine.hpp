#ifndef AttackStateMachine_HPP
#define AttackStateMachine_HPP

#include <StateMachine.hpp>
#include "AttackStateDefine.hpp"

class AttackStateMachine : public StateMachine
{
    public:
        AttackStateMachine():StateMachine()
        {
            this->Init();
        }
        
        virtual void Init();
};

#endif