#ifndef PhotonStateDefine_HPP
#define PhotonStateDefine_HPP

#include <State.hpp>
#include "GameController.hpp"


class PhotonState : public State<GameController>
{
    public:
    unsigned int state_entering_tick;
    unsigned int state_remaining_ms;
};

class PhotonExistState : public PhotonState
{
    public:
        //如果要将父类的纯虚函数实现, 就要在实现的那一级声明!
        virtual void Init(GameController* _FSM_Owner){;}
        virtual void Enter(GameController* _FSM_Owner){;}
        virtual void Execute(GameController* _FSM_Owner){;}
        virtual void Exit(GameController* _FSM_Owner){;}
};

class PhotonGoneState : public PhotonState
{
    public:
        //如果要将父类的纯虚函数实现, 就要在实现的那一级声明!
        virtual void Init(GameController* _FSM_Owner){;}
        virtual void Enter(GameController* _FSM_Owner){;}
        virtual void Execute(GameController* _FSM_Owner){;}
        virtual void Exit(GameController* _FSM_Owner){;}
};

#endif