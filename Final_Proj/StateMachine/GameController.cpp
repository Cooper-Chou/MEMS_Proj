#include "GameController.hpp"
#include "../BSP/bsp.hpp"
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

    if(game_state == GameState::PEACE)
    {
        game_state_color = Color::NO_COLOR;
    }

    if(game_state == GameState::BATTLE)
    {
        //先找出进攻方
        Xon* p_attacker = nullptr;
        switch (game_state_color)
        {
        case Color::RED:
            p_attacker = &red_electron;
            break;

        case Color::BLUE:
            p_attacker = &blue_electron;
            break;
        }

        //然后遍历所有电子，由于同一时间只能有一个进攻方，所以只要有与进攻方相撞的，即判进攻方获胜
        for(int i = 0; i < Color::COLOR_NUM; i++)
        {
            if(ImpactOverlap(p_attacker,electron_p_list[i]))
            {
                game_state = GameState::END;
                game_state_color = p_attacker->color;
            }
        }
    }

    hint_state_machine.Update(); 

    shader.Shade(this);
    shader.Display();
}


void RedElectron::HandleInput()
{
    //此处可能是xy摇杆的方向和电压变化的关系正好是反过来的，y坐标并不需要加负号处理
    x_coor += (long)((p_current_state->x_velo_coe*X_DEFAULT_VELOCITY)*(bspReadBarVolt(RED_BAR_X) - 0.5f*VCC) / (0.5*VCC));
	y_coor += (long)((p_current_state->y_velo_coe*Y_DEFAULT_VELOCITY)*(bspReadBarVolt(RED_BAR_Y) - 0.5f*VCC) / (0.5*VCC));

    if(ImpactOverlap(this, &p_FSM_owner->photon) && p_FSM_owner->photon.GetPCurrentState() == &p_FSM_owner->photon.exist_state)
    {
        p_FSM_owner->photon_absorbed_flag = 1;
        //如果当前状态是激发态，那么就重置激发态的计时器
        if(p_current_state == &excited_state)
        {
            p_FSM_owner->game_state_color = color;
            p_FSM_owner->battle_state_entering_tick = millis();
        }
        else
        {
            //如果当前状态不是激发态，那么就切换到激发态
            ChangeState(&excited_state);
        }
    }

    //如果自己处于激发态并且游戏是战斗状态，但是进攻方不是自己，说明有别的玩家吃到了新的buff，那么自己应该回到基态
    if(p_FSM_owner->game_state == GameState::BATTLE && p_current_state == &excited_state && p_FSM_owner->game_state_color != color)
    {
        ChangeState(&ground_state);
    }

    //激发态时间结束以后就回到基态
    if(p_FSM_owner->battle_state_remain_ms <= 0)
    {
        ChangeState(&ground_state);
    }
}

void BlueElectron::HandleInput()
{
    //此处可能是xy摇杆的方向和电压变化的关系正好是反过来的，y坐标并不需要加负号处理
    x_coor += (long)((p_current_state->x_velo_coe*X_DEFAULT_VELOCITY)*(bspReadBarVolt(BLUE_BAR_X) - 0.5f*VCC) / (0.5*VCC));
	y_coor += (long)((p_current_state->y_velo_coe*Y_DEFAULT_VELOCITY)*(bspReadBarVolt(BLUE_BAR_Y) - 0.5f*VCC) / (0.5*VCC));

    if(ImpactOverlap(this, &p_FSM_owner->photon) && p_FSM_owner->photon.GetPCurrentState() == &p_FSM_owner->photon.exist_state)
    {
        p_FSM_owner->photon_absorbed_flag = 1;
        //如果当前状态是激发态，那么就重置激发态的计时器
        if(p_current_state == &excited_state)
        {
            p_FSM_owner->game_state_color = color;
            p_FSM_owner->battle_state_entering_tick = millis();
        }
        else
        {
            //如果当前状态不是激发态，那么就切换到激发态
            ChangeState(&excited_state);
        }
    }

    //如果自己处于激发态并且游戏是战斗状态，但是进攻方不是自己，说明有别的玩家吃到了新的buff，那么自己应该回到基态
    if(p_FSM_owner->game_state == GameState::BATTLE && p_current_state == &excited_state && p_FSM_owner->game_state_color != color)
    {
        ChangeState(&ground_state);
    }

    //激发态时间结束以后就回到基态
    if(p_FSM_owner->battle_state_remain_ms <= 0)
    {
        ChangeState(&ground_state);
    }
}

void Photon::HandleInput()
{
    ;
}

void HintStateMachine::HandleInput()
{
    if(p_FSM_owner->game_state == GameState::PEACE)
    {
        ChangeState(PeaceState::GetInstance());
    }
    else if(p_FSM_owner->game_state == GameState::BATTLE)
    {
        ChangeState(BattleState::GetInstance());
    }
    else if(p_FSM_owner->game_state == GameState::END)
    {
        ChangeState(EndState::GetInstance());
    }
}   



void RedElectron::Init()
{
    // 这个地方创建了几个实例, 就决定了有几个状态!
    ground_state.Init(this->p_FSM_owner);
    excited_state.Init(this->p_FSM_owner);
    setCurrentState(&ground_state);
}
void BlueElectron::Init()
{
    // 这个地方创建了几个实例, 就决定了有几个状态!
    ground_state.Init(this->p_FSM_owner);
    excited_state.Init(this->p_FSM_owner);
    setCurrentState(&ground_state);
}
void HintStateMachine::Init()
{
    // 这个地方创建了几个实例, 就决定了有几个状态!
    // 提示状态都应该是单例, 所以不需要将状态设置成状态机的成员, 在这里初始化后会自动创建一个单例, 以后只调用这个单例就好!
    PeaceState::GetInstance()->Init(p_FSM_owner);
    BattleState::GetInstance()->Init(p_FSM_owner);
    EndState::GetInstance()->Init(p_FSM_owner);
    setCurrentState(PeaceState::GetInstance());
}
void Photon::Init()
{
    // 这个地方创建了几个实例, 就决定了有几个状态!
    // 这个地方创建了几个实例, 就决定了有几个状态!
    exist_state.Init(p_FSM_owner);
    gone_state.Init(p_FSM_owner);
    setCurrentState(&gone_state);
}
void GameController::Init()
{
    last_tick = millis();
    red_electron.Init();
    blue_electron.Init();
    photon.Init();
    red_electron.SetInitCoor(MAP_WIDTH / 4L, MAP_HEIGHT / 2L);
    blue_electron.SetInitCoor(3L*MAP_WIDTH / 4L, MAP_HEIGHT / 2L);
    photon.SetInitCoor(MAP_WIDTH / 2L, MAP_HEIGHT / 2L);
    electron_p_list[0] = &red_electron;
    electron_p_list[1] = &blue_electron;
    for(int i = 0; i < Color::COLOR_NUM; i++)
    {
        shading_xon_p_list[i] = electron_p_list[i];
    }
    shading_xon_p_list[Color::COLOR_NUM + PHOTON_NUM - 1] = &photon;
    shader.Init();
}

bool ImpactOverlap(Xon *_A_xon, Xon *_B_xon)
{
    float x_dist = _A_xon->x_coor - _B_xon->x_coor;
    float y_dist = _A_xon->y_coor - _B_xon->y_coor;
    float dist = sqrtf(x_dist*x_dist + y_dist*y_dist);

    if(dist - (_A_xon->GetPCurrentState()->impact_radius + _B_xon->GetPCurrentState()->impact_radius) <= -0.5f)
    {
        return true;
    }
    else
    {
        return false;
    }
}

