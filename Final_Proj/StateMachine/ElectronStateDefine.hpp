#ifndef ELectronStateDefine_HPP
#define ELectronStateDefine_HPP

#include <wiringPi.h>
#include "XonStateMachineDefine.hpp"

#define EXCITED_STATE_LAST 7000 /* ms */
#define EXC_VELO_COE 2.0f
#define BATTLE_GND_MAX_VELO_COE 2.5f
#define EXC_IMPACT_RADIUS 5.5f
#define GND_IMPACT_RADIUS 3.0f


class ElectronGroundState : public XonState
{
    public:
    int m_random_num;
    //如果要将父类的纯虚函数实现, 就要在实现的那一级声明成虚函数!
    ElectronGroundState(Chartlet* _chartlet):XonState(_chartlet){}
    void Init(GameController* _FSM_Owner) override;
    void Enter(GameController* _FSM_Owner) override;
    void Execute(GameController* _FSM_Owner) override;
    void Exit(GameController* _FSM_Owner) override;
    void CalcXVeloCoe(GameController* _FSM_Owner, float _direct_angle) override;
    void CalcYVeloCoe(GameController* _FSM_Owner, float _direct_angle) override;
};

class ElectronExcitedState : public XonState
{
    public:
    //如果要将父类的纯虚函数实现, 就要在实现的那一级声明成虚函数!
    ElectronExcitedState(Chartlet* _chartlet):XonState(_chartlet){}
    void Init(GameController* _FSM_Owner) override;
    void Enter(GameController* _FSM_Owner) override;
    void Execute(GameController* _FSM_Owner) override;
    void Exit(GameController* _FSM_Owner) override;
    void CalcXVeloCoe(GameController* _FSM_Owner, float _direct_angle) override {;}
    void CalcYVeloCoe(GameController* _FSM_Owner, float _direct_angle) override {;}
};


#endif