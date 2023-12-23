#include "PhotonStateDefine.hpp"
#include <wiringPi.h>
#include "../GameComponent/Shader.hpp"
#include <stdlib.h>
#include "GameController.hpp"

void PhotonExistState::Init(GameController* _FSM_Owner)
{
    impact_radius = PHOTON_IMPACT_RADIUS;
}
void PhotonExistState::Enter(GameController* _FSM_Owner)
{ 
    _FSM_Owner->photon_absorbed_flag = 0;
    state_entering_tick = millis();

    //每次光子重新出现都要随机刷新在一个位置
    srand(state_entering_tick);
    _FSM_Owner->photon.x_coor = (int)rand() % MAP_WIDTH;
    _FSM_Owner->photon.y_coor = (int)rand() % MAP_HEIGHT;
}
void PhotonExistState::Execute(GameController* _FSM_Owner)
{
    state_remaining_ms = PHOTON_LAST_MS - (millis() - state_entering_tick);
}
void PhotonExistState::Exit(GameController* _FSM_Owner)
{
;
}

PhotonGoneState::PhotonGoneState(Chartlet *_chartlet):XonState(_chartlet)
    {
        x_velo_coe = 0.0f;
        y_velo_coe = 0.0f;
    }
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
    //如果光子没有被吸收，是自然死亡，就只消失一小会就再出现
    if(_FSM_Owner->photon_absorbed_flag == 0)
    {
        state_remaining_ms = PHOTON_INTERVAL_MS - (millis() - state_entering_tick);
    }
    //如果光子是被吸收掉了，是非自然死亡，就消失久一点
    else
    {
        state_remaining_ms = PHOTON_GONE_MS - (millis() - state_entering_tick);
    }
}
void PhotonGoneState::Exit(GameController* _FSM_Owner)
{
;
}
