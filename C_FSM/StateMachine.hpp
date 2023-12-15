#ifndef StateMachine_HPP
#define StateMachine_HPP

#include "State.hpp"

template<typename controller>
class StateMachine
{
    protected:
    controller* p_FSM_owner;
    State *p_current_state;
    
    public:
    StateMachine(controller* _FSM_Owner) : _FSM_Owner(_FSM_Owner),p_current_state(nullptr)
    {}

    void setCurrentState(State *p_state)
	{
		p_current_state = p_state;
		p_current_state->Enter(p_FSM_owner);
	}
    void Update()
    {
        if(p_current_state != nullptr)
        {
            p_current_state->Execute(p_FSM_owner);
        }
    }
    void ChangeState(State *p_next_state)
    {
        if(p_next_state != nullptr && p_current_state != p_next_state)
        {
            p_current_state->Exit(p_FSM_owner);
            p_current_state = p_next_state;
            p_current_state->Enter(p_FSM_owner);
        }
    }
    virtual void Init() = 0;
    void HandleInput() = 0;
};

#endif
