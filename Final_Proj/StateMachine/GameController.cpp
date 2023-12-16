#include "GameController.hpp"
#include "bsp.hpp"
#include <wiringPi.h>

void GameController::Update()
{
    last_tick = millis();

    //先让红蓝方吃完buff
    red_electron.HandleInput();
    blue_electron.HandleInput();

    red_electron.Update();
    blue_electron.Update();

    photon.HandleInput();
    photon.Update();

    hint_state_machine.Update(); 
}


void RedElectron::HandleInput()
{
    //此处可能是xy摇杆的方向和电压变化的关系正好是反过来的，y坐标并不需要加负号处理
    x_coor += (long)((X_DEFAULT_VELOCITY*p_current_state->x_velo_coe)*(bspReadBarVolt(RED_BAR_X) - 0.5f*VCC) / (0.5*VCC));
	y_coor += (long)((Y_DEFAULT_VELOCITY*p_current_state->y_velo_coe)*(bspReadBarVolt(RED_BAR_Y) - 0.5f*VCC) / (0.5*VCC));

    if(ImpactOverlap(this, p_FSM_Owner->photon) && p_FSM_Owner->photon.p_current_state == &p_FSM_Owner->photon.exist_state)
    {
        //如果当前状态不是激发态，那么就切换到激发态，否则就重置激发态的计时器
        if(p_current_state == &excited_state)
        {
            p_FSM_Owner->battle_state_entering_tick = millis();
        }
        else
        {
            TODO: //这里需要加上一个判断，如果对方是激发态，那就把对方设成基态
            ChangeState(&excited_state);
        }
    }

    //激发态时间结束以后就回到基态
    if(p_FSM_Owner->battle_state_remain_ms <= 0)
    {
        ChangeState(&ground_state);
    }
}

void BlueElectron::HandleInput()
{
    //此处可能是xy摇杆的方向和电压变化的关系正好是反过来的，y坐标并不需要加负号处理
    x_coor += (long)((X_DEFAULT_VELOCITY*p_current_state->x_velo_coe)*(bspReadBarVolt(BLUE_BAR_X) - 0.5f*VCC) / (0.5*VCC));
	y_coor += (long)((Y_DEFAULT_VELOCITY*p_current_state->y_velo_coe)*(bspReadBarVolt(BLUE_BAR_Y) - 0.5f*VCC) / (0.5*VCC));

    if(ImpactOverlap(this, p_FSM_Owner->photon) && p_FSM_Owner->photon.p_current_state == &p_FSM_Owner->photon.exist_state)
    {
        //如果当前状态不是激发态，那么就切换到激发态，否则就重置激发态的计时器
        if(p_current_state != &excited_state)
        {
            ChangeState(&excited_state);
        }
        else
        {
            p_FSM_Owner->battle_state_entering_tick = millis();
        }
    }

    if(p_FSM_Owner->battle_state_remain_ms <= 0)
    {
        ChangeState(&ground_state);
    }
}

void Photon::HandleInput()
{
}

void HintStateMachine::HandleInput()
{
}   



void RedElectron::Init()
{
    // 这个地方创建了几个实例, 就决定了有几个状态!
    ground_state.Init(this->p_FSM_Owner);
    excited_state.Init(this->p_FSM_Owner);
    ground_state.chartlet.SetOwner(this);
    excited_state.chartlet.SetOwner(this);
    setCurrentState(&ground_state);
}
void BlueElectron::Init()
{
    // 这个地方创建了几个实例, 就决定了有几个状态!
    ground_state.Init(this->p_FSM_Owner);
    excited_state.Init(this->p_FSM_Owner);
    ground_state.chartlet.SetOwner(this);
    excited_state.chartlet.SetOwner(this);
    setCurrentState(&ground_state);
}
void HintStateMachine::Init()
{
    // 这个地方创建了几个实例, 就决定了有几个状态!
    // 所有状态都应该是单例, 所以不需要将状态设置成状态机的成员, 在这里初始化后会自动创建一个单例, 以后只调用这个单例就好!
    PeaceState::GetInstance()->Init();
    BattleState::GetInstance()->Init();
    EndingState::GetInstance()->Init();
    setCurrentState(PeaceState::GetInstance());
}
void Photon::Init()
{
    // 这个地方创建了几个实例, 就决定了有几个状态!
    // 这个地方创建了几个实例, 就决定了有几个状态!
    exist_state.Init(this->p_FSM_Owner);
    gone_state.Init(this->p_FSM_Owner);
    exist_state.chartlet.SetOwner(this);
    gone_state.chartlet.SetOwner(this);
    setCurrentState(&gone_state);
}
void GameController::Init()
{
    last_tick = millis();
}


