#include "PhotonStateDefine.hpp"
#include <wiringPi.h>


void PhotonExistState::Init(GameController* _FSM_Owner)
{
    impact_radius = PHOTON_IMPACT_RADIUS;
}
void PhotonExistState::Enter(GameController* _FSM_Owner)
{ 
    state_entering_tick = millis();
}
void PhotonExistState::Execute(GameController* _FSM_Owner)
{
}
void PhotonExistState::Exit(GameController* _FSM_Owner)
{
;
}

//TODO:光子转换逻辑，然后就要开始尝试编译了！祝我成功！

void PhotonGoneState::Init(GameController* _FSM_Owner)
{
    impact_radius = PHOTON_IMPACT_RADIUS;
}
void PhotonGoneState::Enter(GameController* _FSM_Owner)
{ 
    state_entering_tick = millis();
}
void PhotonGoneState::Execute(GameController* _FSM_Owner)
{
}
void PhotonGoneState::Exit(GameController* _FSM_Owner)
{
;
}
