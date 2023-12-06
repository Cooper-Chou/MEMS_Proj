#ifndef HintStateMachine_HPP
#define HintStateMachine_HPP

#include <StateMachine.hpp>
#include "HintStateDefine.hpp"

class HintStateMachine : public StateMachine
{
    public:
        HintStateMachine():StateMachine()
        {
            this->Init();
        }
        
        virtual void Init();
};

#endif