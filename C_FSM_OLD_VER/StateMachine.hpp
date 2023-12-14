#ifndef StateMachine_HPP
#define StateMachine_HPP

#include "State.hpp"

class StateMachine
{
    protected:
    State *p_current_state;
    
    public:
    StateMachine():p_current_state(nullptr)
    {}

    void setCurrentState(State *p_state)
	{
		p_current_state = p_state;
		p_current_state->Enter();
	}
    void Update()
    {
        if(p_current_state != nullptr)
        {
            p_current_state->Execute();
        }
    }
    void ChangeState(State *p_next_state)
    {
        if(p_next_state != nullptr && p_current_state != p_next_state)
        {
            p_current_state->Exit();
            p_current_state = p_next_state;
            p_current_state->Enter();
        }
    }
    virtual void Init() = 0;
};

#endif
