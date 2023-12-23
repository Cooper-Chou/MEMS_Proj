#include "ElectronStateDefine.hpp"
#include "GameController.hpp"

void ElectronGroundState::Init(GameController* _FSM_Owner)
{
    x_velo_coe = 1.0f;
    y_velo_coe = 1.0f;
    impact_radius = GND_IMPACT_RADIUS;
}
void ElectronGroundState::Enter(GameController* _FSM_Owner)
{ 
;
}
void ElectronGroundState::Execute(GameController* _FSM_Owner)
{
    srand(_FSM_Owner->battle_state_entering_tick); //以进入激发态的时间为种子
    m_random_num = rand() % 8;
    //处于战斗状态的基态电子需要某个方向的额外加速
    if(_FSM_Owner->game_state == GameState::BATTLE)
    {
        x_velo_coe = GetRandomXVeloCoe(m_random_num);
        y_velo_coe = GetRandomYVeloCoe(m_random_num);
    }
    else
    {
        x_velo_coe = 1.0f;
        y_velo_coe = 1.0f;
    }
}
void ElectronGroundState::Exit(GameController* _FSM_Owner)
{
;
}

void ElectronExcitedState::Init(GameController* _FSM_Owner)
{
    x_velo_coe = EXC_X_VELO_COE;
    y_velo_coe = EXC_Y_VELO_COE;
    impact_radius = EXC_IMPACT_RADIUS;
}
void ElectronExcitedState::Enter(GameController* _FSM_Owner)
{
    _FSM_Owner->game_state = GameState::BATTLE;
    _FSM_Owner->battle_state_entering_tick = millis();
    _FSM_Owner->battle_state_remain_ms = EXCITED_STATE_LAST - (millis() - _FSM_Owner->battle_state_entering_tick);
}
void ElectronExcitedState::Execute(GameController* _FSM_Owner)
{
    _FSM_Owner->game_state = GameState::BATTLE;
    _FSM_Owner->battle_state_remain_ms = EXCITED_STATE_LAST - (millis() - _FSM_Owner->battle_state_entering_tick);
}
void ElectronExcitedState::Exit(GameController* _FSM_Owner)
{
    _FSM_Owner->game_state = GameState::PEACE;
    _FSM_Owner->battle_state_remain_ms = 0;
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