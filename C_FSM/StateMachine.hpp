#ifndef StateMachine_HPP
#define StateMachine_HPP

#include "State.hpp"

template<typename controller>
class StateMachine
{
    protected:
    controller* FSM_Owner;
    State *p_current_state;
    
    public:
    StateMachine(controller* _FSM_Owner) : _FSM_Owner(_FSM_Owner),p_current_state(nullptr)
    {}

    void setCurrentState(State *p_state)
	{
		p_current_state = p_state;
		p_current_state->Enter(FSM_Owner);
	}
    void Update()
    {
        if(p_current_state != nullptr)
        {
            p_current_state->Execute(FSM_Owner);
        }
    }
    void ChangeState(State *p_next_state)
    {
        if(p_next_state != nullptr && p_current_state != p_next_state)
        {
            p_current_state->Exit(FSM_Owner);
            p_current_state = p_next_state;
            p_current_state->Enter(FSM_Owner);
        }
    }
    virtual void Init() = 0;
    void HandleInput() = 0;
};

#endif
