#ifndef State_HPP
#define State_HPP

class State
{
    public:
    //The "=0" at the end means the function is purely virtual, that must not be defined in this class.
        virtual void Init() = 0;
        virtual void Enter() = 0;
        virtual void Execute() = 0;
        virtual void Exit() = 0;
};

#endif
