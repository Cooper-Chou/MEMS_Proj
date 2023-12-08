#include "GameController.hpp"

void Electron::Init()
{
    // 这个地方创建了几个实例, 就决定了有几个状态!
    // 所有状态都应该是单例, 所以不需要将状态设置成状态机的成员, 在这里初始化后会自动创建一个单例, 以后只调用这个单例就好!
    GroundState::GetInstance()->Init();
    ExcitedState::GetInstance()->Init();
    setCurrentState(GroundState::GetInstance());
}

void HintStateDefine::Init()
{
    // 这个地方创建了几个实例, 就决定了有几个状态!
    // 所有状态都应该是单例, 所以不需要将状态设置成状态机的成员, 在这里初始化后会自动创建一个单例, 以后只调用这个单例就好!
    State_Peace::GetInstance()->Init();
    State_Battle::GetInstance()->Init();
    State_GameEnding::GetInstance()->Init();
    setCurrentState(State_Peace::GetInstance());
}

void Photon::Init()
{

}


void GameController::Init()
{
    
}