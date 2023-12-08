#include "ELectronStateDefine.hpp"


void ExcitedState::Init(GameController* _FSM_Owner)
{
    state_entering_tick = 0;
    state_remain_ms = 0;
}
void ExcitedState::Enter(GameController* _FSM_Owner)
{ 
    state_entering_tick = millis();
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