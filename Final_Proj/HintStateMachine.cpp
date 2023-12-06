#include "HintStateMachine.hpp"

void HintStateMachine::Init()
{
    // 这个地方创建了几个实例，就决定了有几个状态！
    State_RedBlink::GetInstance()->Init();
    State_BlueBlink::GetInstance()->Init();
    State_PurpleOn::GetInstance()->Init();
    State_Off::GetInstance()->Init();
    setCurrentState(State_Off::GetInstance());
}