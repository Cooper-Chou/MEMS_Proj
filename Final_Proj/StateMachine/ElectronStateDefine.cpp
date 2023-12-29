#include "ElectronStateDefine.hpp"
#include "GameController.hpp"
#include <cmath>

void ElectronGroundState::Init(GameController* _FSM_Owner)
{
    x_velo_coe = 1.0f;
    y_velo_coe = 1.0f;
    impact_radius = GND_IMPACT_RADIUS;
    m_random_num = 0;
}
void ElectronGroundState::Enter(GameController* _FSM_Owner)
{ 
;
}
void ElectronGroundState::Execute(GameController* _FSM_Owner)
{
    srand(_FSM_Owner->battle_state_entering_tick); //以进入激发态的时间为种子
    m_random_num = rand() % 4;
}
void ElectronGroundState::Exit(GameController* _FSM_Owner)
{
;
}

void ElectronExcitedState::Init(GameController* _FSM_Owner)
{
    x_velo_coe = EXC_VELO_COE;
    y_velo_coe = EXC_VELO_COE;
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
}


float accelerate_angle[] = 
    {
        //分别是：上，右上，右，左上, 单位是 rad
        0.0f, 3.1415926f/4.0f, 3.1415926f/2.0f, 3.0f*3.1415926f/4.0f
    };

void ElectronGroundState::CalcXVeloCoe(GameController* _FSM_Owner, float _direct_angle)
{
    // printf("Accelerate angle = %f\n", accelerate_angle[m_random_num]/3.1415926f*180.0f);
    float angle_diff = _direct_angle - accelerate_angle[m_random_num];
    // angle_diff = angle_diff > 0.0f ? angle_diff : angle_diff + M_PI;
    //处于战斗状态的基态电子需要某个方向的额外加速
    //TODO:速度计算还是有问题
    if(_FSM_Owner->game_state == GameState::BATTLE)
    {
        //此处绝对值是数学上的问题要求的
        x_velo_coe = sinf(_direct_angle)*(0.5f*(BATTLE_GND_MAX_VELO_COE - 1.0f) * (cosf(angle_diff*2.0f) + 1.0f) + 1.0f);
    }
    else
    {
        x_velo_coe = 1.0f;
    }
}

void ElectronGroundState::CalcYVeloCoe(GameController* _FSM_Owner, float _direct_angle)
{
    float angle_diff = _direct_angle - accelerate_angle[m_random_num];
    //处于战斗状态的基态电子需要某个方向的额外加速
    if(_FSM_Owner->game_state == GameState::BATTLE)
    {
        y_velo_coe = fabs(cosf(_direct_angle)*(0.5f*(BATTLE_GND_MAX_VELO_COE - 1.0f) * (cosf(angle_diff*2.0f) + 1.0f) + 1.0f));
    }
    else
    {
        y_velo_coe = 1.0f;
    }
}
