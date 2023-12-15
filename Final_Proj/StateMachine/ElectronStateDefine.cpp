#include "ELectronStateDefine.hpp"

#define EXC_X_VELO_COE 1.3f
#define EXC_Y_VELO_COE 1.3f
#define BATTLE_GND_MAX_VELO_COE 1.8f
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
    srand(micros());
    int random_index = rand() % 8;
    RedGroundState::GetInstance()->x_velo_coe = GetRandomXVeloCoe(random_index);
    RedGroundState::GetInstance()->y_velo_coe = GetRandomYVeloCoe(random_index);
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
    RedGroundState::GetInstance()->x_velo_coe = 1.0f;
    RedGroundState::GetInstance()->y_velo_coe = 1.0f;
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
    srand(micros());
    int random_index = rand() % 8;
    BlueGroundState::GetInstance()->x_velo_coe = GetRandomXVeloCoe(random_index);
    BlueGroundState::GetInstance()->y_velo_coe = GetRandomYVeloCoe(random_index);
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
    BlueGroundState::GetInstance()->x_velo_coe = 1.0f;
    BlueGroundState::GetInstance()->y_velo_coe = 1.0f;
}



float x_velo_coe_list[] = 
    {
        0.0f, sqrtf(BATTLE_GND_MAX_VELO_COE), BATTLE_GND_MAX_VELO_COE, sqrtf(BATTLE_GND_MAX_VELO_COE), 
        0.0f, -sqrtf(BATTLE_GND_MAX_VELO_COE), -BATTLE_GND_MAX_VELO_COE, -sqrtf(BATTLE_GND_MAX_VELO_COE)
    };

float y_velo_coe_list[] = 
    {
        BATTLE_GND_MAX_VELO_COE, sqrtf(BATTLE_GND_MAX_VELO_COE), 0.0f, -sqrtf(BATTLE_GND_MAX_VELO_COE),
        -BATTLE_GND_MAX_VELO_COE, -sqrtf(BATTLE_GND_MAX_VELO_COE), 0.0f, sqrtf(BATTLE_GND_MAX_VELO_COE)
    };

int GetRandomXVeloCoe(int _random_index)
{
    return x_velo_coe_list[_random_index];
}

int GetRandomYVeloCoe(int _random_index)
{
    return y_velo_coe_list[_random_index];
}