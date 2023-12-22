#ifndef ELectronStateDefine_HPP
#define ELectronStateDefine_HPP

#include <wiringPi.h>
#include "XonStateMachineDefine.hpp"

#define EXCITED_STATE_LAST 7000 /* ms */
#define EXC_X_VELO_COE 1.3f
#define EXC_Y_VELO_COE 1.3f
#define BATTLE_GND_MAX_VELO_COE 1.8f
#define EXC_IMPACT_RADIUS 7.0f
#define GND_IMPACT_RADIUS 3.0f


class ElectronGroundState : public XonState
{
    public:
    //如果要将父类的纯虚函数实现, 就要在实现的那一级声明成虚函数!
    ElectronGroundState(Chartlet* _chartlet):XonState(_chartlet){}
    virtual void Init(GameController* _FSM_Owner);
    virtual void Enter(GameController* _FSM_Owner);
    virtual void Execute(GameController* _FSM_Owner);
    virtual void Exit(GameController* _FSM_Owner);
};

class ElectronExcitedState : public XonState
{
    public:
    //如果要将父类的纯虚函数实现, 就要在实现的那一级声明成虚函数!
    ElectronExcitedState(Chartlet* _chartlet):XonState(_chartlet){}
    virtual void Init(GameController* _FSM_Owner);
    virtual void Enter(GameController* _FSM_Owner);
    virtual void Execute(GameController* _FSM_Owner);
    virtual void Exit(GameController* _FSM_Owner);
};

int GetRandomYVeloCoe(int _random_index);
int GetRandomXVeloCoe(int _random_index);

#endif