#include "ELectronStateDefine.hpp"

#define EXC_X_VELO_COE 1.3f
#define EXC_Y_VELO_COE 1.3f
#define EXC_IMPACT_RADIUS 7.0f
#define GND_IMPACT_RADIUS 3.0f

void RedGroundState::Init(GameController* _FSM_Owner)
{
    x_velo_coe = 1.0f;
    y_velo_coe = 1.0f;
    impact_radius = GND_IMPACT_RADIUS;
    chartlet.Init(RedElectron.GetInstance(), &gnd_aprnc_1, &gnd_aprnc_1_Xofst, &gnd_aprnc_1_Yofst, gnd_aprnc_1_length);
}
void RedGroundState::Enter(GameController* _FSM_Owner)
{ 
;
}
void RedGroundState::Execute(GameController* _FSM_Owner)
{;
}
void RedGroundState::Exit(GameController* _FSM_Owner)
{
;
}

void RedExcitedState::Init(GameController* _FSM_Owner)
{
    state_entering_tick = 0;
    state_remain_ms = 0;
    x_velo_coe = EXC_X_VELO_COE;
    y_velo_coe = EXC_Y_VELO_COE;
    impact_radius = EXC_IMPACT_RADIUS;
    chartlet.Init(RedElectron.GetInstance(), &exc_aprnc_1, &exc_aprnc_1_Xofst, &exc_aprnc_1_Yofst, exc_aprnc_1_length);
}
void RedExcitedState::Enter(GameController* _FSM_Owner)
{ 
    state_entering_tick = millis();
    //TODO:将基态电子某个方向速度设为两倍
}
void RedExcitedState::Execute(GameController* _FSM_Owner)
{
    state_remain_ms = EXCITED_STATE_LAST - (millis() - state_entering_tick);
    if(state_remain_ms <= 0)
    {
        _FSM_Owner->red_electron.ChangeState(RedGroundState::GetInstance());
    }
}
void RedExcitedState::Exit(GameController* _FSM_Owner)
{
    state_remain_ms = 0;
}


void RedGroundState::Init(GameController* _FSM_Owner)
{
    x_velo_coe = 1.0f;
    y_velo_coe = 1.0f;
    impact_radius = GND_IMPACT_RADIUS;
    chartlet.Init(BlueElectron.GetInstance(), &gnd_aprnc_2, &gnd_aprnc_2_Xofst, &gnd_aprnc_2_Yofst, gnd_aprnc_2_length);
}
void BlueGroundState::Enter(GameController* _FSM_Owner)
{ 
;
}
void BlueGroundState::Execute(GameController* _FSM_Owner)
{;
}
void BlueGroundState::Exit(GameController* _FSM_Owner)
{
;
}

void BlueExcitedState::Init(GameController* _FSM_Owner)
{
    state_entering_tick = 0;
    state_remain_ms = 0;
    x_velo_coe = EXC_X_VELO_COE;
    y_velo_coe = EXC_Y_VELO_COE;
    impact_radius = EXC_IMPACT_RADIUS;
    chartlet.Init(BlueElectron.GetInstance(), &exc_aprnc_2, &exc_aprnc_2_Xofst, &exc_aprnc_2_Yofst, exc_aprnc_2_length);
}
void BlueExcitedState::Enter(GameController* _FSM_Owner)
{ 
    state_entering_tick = millis();
    //TODO:将基态电子某个方向速度设为两倍
}
void BlueExcitedState::Execute(GameController* _FSM_Owner)
{
    state_remain_ms = EXCITED_STATE_LAST - (millis() - state_entering_tick);
    if(state_remain_ms <= 0)
    {
        _FSM_Owner->blue_electron.ChangeState(BlueGroundState::GetInstance());
    }
}
void BlueExcitedState::Exit(GameController* _FSM_Owner)
{
    state_remain_ms = 0;
}