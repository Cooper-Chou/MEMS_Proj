#ifndef GameController_HPP
#define GameController_HPP

#include <stdio.h>
#include <stdint.h>
#include "../BSP/bsp.hpp"
#include <StateMachine.hpp>
#include <Controller.hpp>
#include "PhotonStateDefine.hpp"
#include "ElectronStateDefine.hpp"
#include "HintStateDefine.hpp"
#include "ElectronStateMachineDefine.hpp"
#include "../GameComponent/Chartlet.hpp"
#include <cmath>

//此处的速度只是一个相对值，没有单位，只能 大了调小 小了调大 这样子
#define X_DEFAULT_VELOCITY 800.0f/(float)REFRESH_PERIOD;
#define Y_DEFAULT_VELOCITY 400.0f/(float)REFRESH_PERIOD;

#define RED_X_COOR 


enum Color
{
    NO_COLOR = 0,
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

//先声明防止报错
class GameController;


class RedElectron : public Xon
{
    public:
    ElectronGroundState ground_state;
    ElectronExcitedState excited_state;

    public:
    RedElectron(GameController* _FSM_Owner):
            Xon(_FSM_Owner,Color::RED), //子类构造函数必须要调用父类构造函数
            ground_state(p_gnd_aprnc_1),excited_state(p_exc_aprnc_1)
    {;}
    
    virtual void Init();
    virtual void HandleInput();
};

class BlueElectron : public Xon
{
    public:
    ElectronGroundState ground_state;
    ElectronExcitedState excited_state;

    public:
    BlueElectron(GameController* _FSM_Owner):
            Xon(_FSM_Owner, Color::BLUE), //子类构造函数必须要调用父类构造函数
            ground_state(p_gnd_aprnc_2),excited_state(p_exc_aprnc_2)
    {;}
 
    virtual void Init();
    virtual void HandleInput();
};

//这个状态机是单例
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
    virtual void HandleInput();

    static HintStateMachine* GetInstance()
    {
        if(m_pInstance == nullptr)
        {
            m_pInstance = new HintStateMachine(GameController::GetInstance());
        }
        return m_pInstance;
    }
};

class Photon : public Xon
{
    public:
    PhotonExistState exist_state;
    PhotonGoneState gone_state;

    public:
    Photon(GameController* _FSM_Owner):Xon(_FSM_Owner, Color::NO_COLOR),//子类构造函数必须要调用父类构造函数
            exist_state(p_photon_aprnc_exist),gone_state(p_photon_aprnc_gone)
    {;}   //光子类不能算作电子，只有电子才具有颜色属性，所以要给它赋予空颜色！
    
    virtual void Init();
    virtual void HandleInput();
};


//GameController也是单例
class GameController : public Controller
{
    private:
    static GameController *m_pInstance;

    public:
    unsigned int last_tick;
    unsigned int battle_state_entering_tick;
    unsigned int battle_state_remain_ms;

    HintStateMachine hint_state_machine;
    Photon photon;
    RedElectron red_electron;
    BlueElectron blue_electron;
    Xon *electron_list[Color::COLOR_NUM];
    GameState game_state;

    /*--------------------------------------*/
    Color game_state_color;
    //如果处于PEACE状态，这个变量没有意义，应该为NO_COLOR
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

    static GameController* GetInstance()
    {
        if(m_pInstance == nullptr)
        {
            m_pInstance = new GameController();
        }
        return m_pInstance;
    }
};

bool ImpactOverlap(Xon *_A_xon, Xon *_B_xon)
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
