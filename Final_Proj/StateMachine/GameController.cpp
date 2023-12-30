#include "GameController.hpp"
#include "../BSP/bsp.hpp"
#include <cstdio>
#include <wiringPi.h>
#include "../GameComponent/MATH.h"
#include "HintStateDefine.hpp"
#include "XonStateMachineDefine.hpp"
#include <cmath>

int break_flag = 0;

void GameController::Update()
{
    last_tick = millis();

    if(end_flag == 0)
    {
        shader.RefreshMap();

        //先让红蓝方吃完buff
        blue_electron.HandleInput();
        red_electron.HandleInput();
        photon.HandleInput();

        photon.Update();
        red_electron.Update();
        blue_electron.Update();

        shader.Shade(this);
        shader.Display();

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
                            end_flag = 1;
                            game_state = GameState::END;
                            game_state_color = p_attacker->color;
                        }
                    }
                }
            }
        }
    }

    IR_true_vlaue = bspReadIR();
    if(IR_true_vlaue == MID_SIG)
    {
        end_flag = 0;
        Refresh();
    }
    else if(IR_true_vlaue == UP_SIG)
    {
        // printf("Changed silent state!\n");
        if(silent_flag == 0){silent_flag = 1;}
        else{silent_flag = 0;}
    }
    else if(IR_true_vlaue == DOWN_SIG)
    {
        break_flag = 1;
    }

    hint_state_machine.HandleInput();
}


void RedElectron::HandleInput()
{
    float direct_angle = std::acos(bspReadBarPerc(RED_BAR_Y)/sqrt(bspReadBarPerc(RED_BAR_X)*bspReadBarPerc(RED_BAR_X) + bspReadBarPerc(RED_BAR_Y)*bspReadBarPerc(RED_BAR_Y)));
    direct_angle = bspReadBarPerc(RED_BAR_X)*direct_angle/fabs(bspReadBarPerc(RED_BAR_X));
    // printf("RED: x = %f, y = %f   RED: x_coe = %f, y_coe = %f\n",bspReadBarPerc(RED_BAR_X), bspReadBarPerc(RED_BAR_Y), p_current_state->x_velo_coe, p_current_state->y_velo_coe);
    // printf("RED: direct_angle = %f\n", direct_angle/3.1415926f*180.0f);
    // printf("red x < 0 = %d\n", bspReadBarPerc(RED_BAR_X) < 0.0f);
    p_current_state->CalcXVeloCoe(p_FSM_owner, direct_angle);
    p_current_state->CalcYVeloCoe(p_FSM_owner, direct_angle);

    x_coor += (int)((p_current_state->x_velo_coe*X_DEFAULT_VELOCITY)*3.0f*bspReadBarPerc(RED_BAR_X));
	y_coor += (int)((p_current_state->y_velo_coe*Y_DEFAULT_VELOCITY)*3.0f*bspReadBarPerc(RED_BAR_Y));

    //此处需要取模，实现周期性效果，并且如果不取模会导致碰撞箱计算出错
    x_coor = modulus<int>(x_coor, MAP_WIDTH);
    y_coor = modulus<int>(y_coor, MAP_HEIGHT);

    // printf("overlap state = %d\nx_coor_1 = %d, y_coor_1 = %d\nx_coor_2 = %d, y_coor_2 = %d\n",ImpactOverlap(this, &p_FSM_owner->blue_electron),this->x_coor,this->y_coor,p_FSM_owner->blue_electron.x_coor,p_FSM_owner->blue_electron.y_coor);
    // printf("Game State = %d\n",p_FSM_owner->game_state);
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
    float direct_angle = std::acos(bspReadBarPerc(BLUE_BAR_Y)/sqrt(bspReadBarPerc(BLUE_BAR_X)*bspReadBarPerc(BLUE_BAR_X) + bspReadBarPerc(BLUE_BAR_Y)*bspReadBarPerc(BLUE_BAR_Y)));
    direct_angle = bspReadBarPerc(BLUE_BAR_X)*direct_angle/fabs(bspReadBarPerc(BLUE_BAR_X));
    // printf("BLUE: x = %f, y = %f   BLUE: x_coe = %f, y_coe = %f\n",bspReadBarPerc(BLUE_BAR_X), bspReadBarPerc(BLUE_BAR_Y), p_current_state->x_velo_coe, p_current_state->y_velo_coe);
    // printf("BLUE direct angle = %f\n",direct_angle/3.1415926f*180.0f);
    p_current_state->CalcXVeloCoe(p_FSM_owner, direct_angle);
    p_current_state->CalcYVeloCoe(p_FSM_owner, direct_angle);

    x_coor += (int)((p_current_state->x_velo_coe*X_DEFAULT_VELOCITY)*3.0f*bspReadBarPerc(BLUE_BAR_X));
	y_coor += (int)((p_current_state->y_velo_coe*Y_DEFAULT_VELOCITY)*3.0f*bspReadBarPerc(BLUE_BAR_Y));

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
    
    // printf("Knowing battle = %d, ground state = %d\n", p_FSM_owner->game_state == GameState::BATTLE, p_current_state == &ground_state);
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
    else if(p_FSM_owner->game_state == GameState::END || p_FSM_owner->end_flag == 1)
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

void GameController::Refresh()
{
    last_tick = millis();
    red_electron.ChangeState(&red_electron.ground_state);
    blue_electron.ChangeState(&blue_electron.ground_state);
    photon.ChangeState(&photon.exist_state);
    hint_state_machine.ChangeState(PeaceState::GetInstance());
    photon.SetInitCoor(MAP_WIDTH / 2, MAP_HEIGHT / 2);
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