#include "GameController.hpp"
#include "../BSP/bsp.hpp"
#include <wiringPi.h>
#include "../GameComponent/MATH.h"
#include "XonStateMachineDefine.hpp"

void GameController::Update()
{
    last_tick = millis();
    shader.RefreshMap();

    //先让红蓝方吃完buff
    blue_electron.HandleInput();
    red_electron.HandleInput();
    photon.HandleInput();

    photon.Update();
    red_electron.Update();
    blue_electron.Update();

    if(game_state == GameState::BATTLE)
    {
        Xon *p_attacker = nullptr;
        if(game_state_color == Color::RED)
        {
            p_attacker = &red_electron;
        }
        else if(game_state_color == Color::BLUE)
        {
            p_attacker = &blue_electron;
        }
        //然后遍历所有电子，由于同一时间只能有一个进攻方，所以只要有与进攻方相撞的，即判进攻方获胜
        for(int i = 0; i < Color::COLOR_NUM; i++)
        {
            for(int j = i + 1; j < Color::COLOR_NUM; j++)
            {
                if(ImpactOverlap(electron_p_list[i],electron_p_list[j]))
                {
                    if(electron_p_list[i] == p_attacker || electron_p_list[j] == p_attacker)
                    {
                        game_state = GameState::END;
                        game_state_color = p_attacker->color;
                    }
                }
            }
        }
    }

    hint_state_machine.Update(); 

    shader.Shade(this);
    shader.Display();
}


void RedElectron::HandleInput()
{
    //此处y坐标需要加负号处理，因为y轴方向和电压变化的关系与x轴是反过来的
    x_coor += (int)((p_current_state->x_velo_coe*X_DEFAULT_VELOCITY)*(0.5f*VCC - bspReadBarVolt(RED_BAR_X)) / (0.5*VCC));
	y_coor += (int)((p_current_state->y_velo_coe*Y_DEFAULT_VELOCITY)*(0.5f*VCC - bspReadBarVolt(RED_BAR_Y)) / (0.5*VCC));
    //此处需要取模，实现周期性效果，并且如果不取模会导致碰撞箱计算出错
    x_coor = modulus<int>(x_coor, MAP_WIDTH);
    y_coor = modulus<int>(y_coor, MAP_HEIGHT);

    printf("overlap state = %d\nx_coor_1 = %d, y_coor_1 = %d\nx_coor_2 = %d, y_coor_2 = %d\n",ImpactOverlap(this, &p_FSM_owner->blue_electron),this->x_coor,this->y_coor,p_FSM_owner->blue_electron.x_coor,p_FSM_owner->blue_electron.y_coor);
    printf("Game State = %d\n",p_FSM_owner->game_state);
    //printf("Overlap state = %d, photon state = %d\n",ImpactOverlap(this, &p_FSM_owner->photon),p_FSM_owner->photon.GetPCurrentState() == &p_FSM_owner->photon.exist_state);
    if(ImpactOverlap(this, &p_FSM_owner->photon) && p_FSM_owner->photon.GetPCurrentState() == &p_FSM_owner->photon.exist_state)
    {
        p_FSM_owner->game_state_color = color;
        p_FSM_owner->photon_absorbed_flag = 1;
        //如果当前状态是激发态，那么就重置激发态的计时器
        if(p_current_state == &excited_state)
        {
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

    //战斗状态时的基态电子需要额外渲染一下加速的方向
    if(p_FSM_owner->game_state == GameState::BATTLE && p_current_state == &ground_state)
    {
        p_FSM_owner->shader.AppendElement(x_coor, y_coor, battle_hint_aprnc, battle_hint_Xofst[ground_state.m_random_num], battle_hint_Yofst[ground_state.m_random_num], 2);
    }
}

void BlueElectron::HandleInput()
{
    //此处y坐标需要加负号处理，因为y轴方向和电压变化的关系与x轴是反过来的
    x_coor += (int)((p_current_state->x_velo_coe*X_DEFAULT_VELOCITY)*(0.5f*VCC - bspReadBarVolt(BLUE_BAR_X)) / (0.5*VCC));
	y_coor += (int)((p_current_state->y_velo_coe*Y_DEFAULT_VELOCITY)*(0.5f*VCC - bspReadBarVolt(BLUE_BAR_Y)) / (0.5*VCC));
    //此处需要取模，实现周期性效果，并且如果不取模会导致碰撞箱计算出错
    x_coor = modulus<int>(x_coor, MAP_WIDTH);
    y_coor = modulus<int>(y_coor, MAP_HEIGHT);

    if(ImpactOverlap(this, &p_FSM_owner->photon) && p_FSM_owner->photon.GetPCurrentState() == &p_FSM_owner->photon.exist_state)
    {
        p_FSM_owner->game_state_color = color;
        p_FSM_owner->photon_absorbed_flag = 1;
        //如果当前状态是激发态，那么就重置激发态的计时器
        if(p_current_state == &excited_state)
        {
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
    
    printf("Knowing battle = %d, ground state = %d\n", p_FSM_owner->game_state == GameState::BATTLE, p_current_state == &ground_state);
    //战斗状态时的基态电子需要额外渲染一下加速的方向
    if(p_FSM_owner->game_state == GameState::BATTLE && p_current_state == &ground_state)
    {
        p_FSM_owner->shader.AppendElement(x_coor, y_coor, battle_hint_aprnc, battle_hint_Xofst[ground_state.m_random_num], battle_hint_Yofst[ground_state.m_random_num], 2);
    }
}

void Photon::HandleInput()
{
    if(p_current_state == &gone_state && gone_state.state_remaining_ms <= 0)
    {
        ChangeState(&exist_state);
    }
    else if(p_current_state == &exist_state && exist_state.state_remaining_ms <= 0 || p_FSM_owner->photon_absorbed_flag == 1)
    {
        ChangeState(&gone_state);
    }
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
    photon.SetInitCoor(MAP_WIDTH / 2, MAP_HEIGHT / 2);
    electron_p_list[0] = &red_electron;
    electron_p_list[1] = &blue_electron;
    for(int i = 0; i < Color::COLOR_NUM; i++)
    {
        shading_xon_p_list[i] = electron_p_list[i];
    }
    shading_xon_p_list[Color::COLOR_NUM + PHOTON_NUM - 1] = &photon;
    shader.Init();
    red_electron.SetInitCoor(MAP_WIDTH / 4, MAP_HEIGHT / 2);
    blue_electron.SetInitCoor(3*MAP_WIDTH / 4, MAP_HEIGHT / 2);
}

bool ImpactOverlap(Xon *_A_xon, Xon *_B_xon)
{
    float x_dist = _A_xon->x_coor - _B_xon->x_coor;
    float y_dist = 2.0f * (_A_xon->y_coor - _B_xon->y_coor);
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

int battle_hint_Xofst[][2] = 
{
  {0, 0},
  {5, -5},
  {5, -5},
  {5, -5}
};

int battle_hint_Yofst[][2] = 
{
  {2, -2},
  {2, -2},
  {0, 0},
  {-2, 2}
};

char battle_hint_aprnc[] = 
{
  '*','*'
};