#ifndef GameController_HPP
#define GameController_HPP

#include <stdio.h>
#include <stdint.h>
#include "bsp.hpp"
#include <StateMachine.hpp>
#include "Controller.hpp"
#include "PhotonStateDefine.hpp"
#include "ElectronStateDefine.hpp"
#include "HintStateDefine.hpp"
#include "Chartlet.hpp"
#include <cmath>

//此处的速度只是一个相对值，没有单位，只能 大了调小 小了调大 这样子
#define X_DEFAULT_VELOCITY 800.0f/(float)REFRESH_PERIOD;
#define Y_DEFAULT_VELOCITY 400.0f/(float)REFRESH_PERIOD;


enum Color
{
    NULL = 0,
    RED = 0,
    BLUE = 1,

    COLOR_NUM
};

enum GameState
{
    PEACE = 0,
    BATTLE = 1,
    END = 2
};


class RedElectron : public StateMachine<GameController>
{
    private:
    static RedElectron *m_pInstance;

    public:
    long x_coor;
    long y_coor;
    Color color;
    ElectronGroundState ground_state;
    ElectronExcitedState excited_state;

    public:
    RedElectron(GameController* _FSM_Owner, int _x_coor, int _y_coor):
            StateMachine<GameController>(_FSM_Owner), //子类构造函数必须要调用父类构造函数
            x_coor(_x_coor),y_coor(_y_coor),color(Color::RED),ground_state<GameController>(),excited_state<GameController>()
    {
        this->Init();
    }
    
    virtual void Init();

    static RedElectron* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new RedElectron();
            }
            return m_pInstance;
        }
};

class BlueElectron : public StateMachine<GameController>
{
    private:
    static BlueElectron *m_pInstance;

    public:
    long x_coor;
    long y_coor;
    Color color;
    ElectronGroundState ground_state;
    ElectronExcitedState excited_state;

    public:
    BlueElectron(GameController* _FSM_Owner, int _x_coor, int _y_coor):
            StateMachine<GameController>(_FSM_Owner), //子类构造函数必须要调用父类构造函数
            x_coor(_x_coor),y_coor(_y_coor),color(Color::BLUE),ground_state<GameController>(),excited_state<GameController>()
    {
        this->Init();
    }
    
    virtual void Init();

    static BlueElectron* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new BlueElectron();
            }
            return m_pInstance;
        }
};

class HintStateMachine : public StateMachine<GameController>
{
    private:
    static HintStateMachine *m_pInstance;

    public:
    HintStateMachine(GameController* _FSM_Owner):StateMachine<GameController>(_FSM_Owner) //子类构造函数必须要调用父类构造函数
    {
        this->Init();
    }
    
    virtual void Init();

    static HintStateMachine* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new HintStateMachine();
            }
            return m_pInstance;
        }
};

class Photon : public StateMachine<GameController>
{
    private:
    static Photon *m_pInstance;

    public:
    long x_coor;
    long y_coor;
    PhotonExistState exist_state;
    PhotonGoneState gone_state;

    public:
        Photon(GameController* _FSM_Owner, int _x_coor, int _y_coor):StateMachine<GameController>(_FSM_Owner),x_coor(_x_coor),y_coor(_y_coor) //子类构造函数必须要调用父类构造函数
        {
            this->Init();
        }
        
        virtual void Init();

    static Photon* GetInstance()
    {
        if(m_pInstance == nullptr)
        {
            m_pInstance = new Photon();
        }
        return m_pInstance;
    }
};

class GameController : public Controller
{
    public:
    unsigned int last_tick;
    unsigned int battle_state_entering_tick;
    unsigned int battle_state_remain_ms;

    HintStateMachine hint_state_machine;
    Photon photon;
    RedElectron red_electron;
    BlueElectron blue_electron;
    StateMachine<GameController> *electron_list[Color::COLOR_NUM];
    GameState game_state;

    /*--------------------------------------*/
    Color game_state_color;
    //如果处于PEACE状态，这个变量没有意义，应该为NULL
    //如果处于BATTLE状态，这个变量表示进攻方
    //如果处于END状态，这个变量表示胜利方
    /*--------------------------------------*/

    GameController():hint_state_machine(this),photon(this),game_state(GameState::PEACE),
                    red_electron(this),blue_electron(this),Controller()
    {
        this->Init();
    }    

    virtual void Init();
    virtual void Update();
};

bool ImpactOverlap(StateMachine<GameController> *_A_xon, StateMachine<GameController> *_B_xon)
{
    float x_dist = _A_xon->x_coor - _B_xon->x_coor;
    float y_dist = _A_xon->y_coor - _B_xon->y_coor;
    float dist = sqrtf(x_dist*x_dist + y_dist*y_dist);

    if(dist - (_A_xon->impact_radius + _B_xon->impact_radius) <= -0.5f)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//速度重分配，计算碰撞，动量守恒
void VeloRedistribute()
{

}


#endif
