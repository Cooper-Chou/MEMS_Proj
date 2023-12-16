#ifndef ELectronStateDefine_HPP
#define ELectronStateDefine_HPP

#include <State.hpp>
#include <wiringPi.h>
#include "StateMachineForGame.hpp"
#include "GameController.hpp"

#define EXCITED_STATE_LAST 7000 /* ms */


class ElectronState
{
    public:    
    Chartlet chartlet;
    float x_velo_coe;
    float y_velo_coe;
    float impact_radius; //碰撞半径
    ElectronState(Chartlet* _chartlet):chartlet(*_chartlet){;};
    //The "=0" at the end means the function is purely virtual, that must not be defined in this class.
    virtual void Init(GameController* _FSM_Owner) = 0;
    virtual void Enter(GameController* _FSM_Owner) = 0;
    virtual void Execute(GameController* _FSM_Owner) = 0;
    virtual void Exit(GameController* _FSM_Owner) = 0;
};


class ElectronGroundState : public ElectronState
{
    public:
        //如果要将父类的纯虚函数实现, 就要在实现的那一级声明成虚函数!
        ElectronGroundState(Chartlet* _chartlet):ElectronState(_chartlet){;};
        virtual void Init(GameController* _FSM_Owner);
        virtual void Enter(GameController* _FSM_Owner);
        virtual void Execute(GameController* _FSM_Owner);
        virtual void Exit(GameController* _FSM_Owner);
};

class ElectronExcitedState : public ElectronState
{
    public:
        //如果要将父类的纯虚函数实现, 就要在实现的那一级声明成虚函数!
        ElectronExcitedState(Chartlet* _chartlet):ElectronState(_chartlet){;};
        virtual void Init(GameController* _FSM_Owner);
        virtual void Enter(GameController* _FSM_Owner);
        virtual void Execute(GameController* _FSM_Owner);
        virtual void Exit(GameController* _FSM_Owner);
};

#endif