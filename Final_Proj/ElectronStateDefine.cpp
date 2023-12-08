#include "ELectronStateDefine.hpp"


void GroundState::Init(GameController* _FSM_Owner)
{
    x_velo_coe = 1.0f;
    y_velo_coe = 1.0f;
    impact_radius = 3.0f;
}
void GroundState::Enter(GameController* _FSM_Owner)
{ 
;
}
void GroundState::Execute(GameController* _FSM_Owner)
{;
}
void GroundState::Exit(GameController* _FSM_Owner)
{
;
}


void ExcitedState::Init(GameController* _FSM_Owner)
{
    state_entering_tick = 0;
    state_remain_ms = 0;
    x_velo_coe = 1.3f;
    y_velo_coe = 1.3f;
    impact_radius = 7.0f;
}
void ExcitedState::Enter(GameController* _FSM_Owner)
{ 
    state_entering_tick = millis();
    //TODO:将基态电子某个方向速度设为两倍
}
void ExcitedState::Execute(GameController* _FSM_Owner)
{
    state_remain_ms = EXCITED_STATE_LAST - (millis() - state_entering_tick);
    if(state_remain_ms <= 0)
    {
        _FSM_Owner->Electron.ChangeState(GroundState::GetInstance());
    }
}
void ExcitedState::Exit(GameController* _FSM_Owner)
{
    state_remain_ms = 0;
}