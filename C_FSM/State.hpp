#ifndef State_HPP
#define State_HPP

template<typename controller>
class State
{
    public:
    //The "=0" at the end means the function is purely virtual, that must not be defined in this class.
    virtual void Init(controller* _FSM_Owner) = 0;
    virtual void Enter(controller* _FSM_Owner) = 0;
    virtual void Execute(controller* _FSM_Owner) = 0;
    virtual void Exit(controller* _FSM_Owner) = 0;
};

#endif
