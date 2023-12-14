#ifndef GameController_HPP
#define GameController_HPP

#include <stdio.h>
#include <stdint.h>
#include "bsp.hpp"
#include <StateMachine.hpp>
#include "Controller.hpp"
#include "Chartlet.hpp"

#define X_DEFAULT_VELOCITY 8.0f;
#define Y_DEFAULT_VELOCITY 4.0f;


enum Color
{
    NULL = 0,
    RED = 1,
    BLUE = 2
};

class RedElectron : public StateMachine
{
    private:
    static RedElectron *m_pInstance;

    public:
    long x_coor;
    long y_coor;
    Color color;

    public:
    RedElectron(GameController* _FSM_Owner, int _x_coor, int _y_coor):
            StateMachine<GameController>(_FSM_Owner), //子类构造函数必须要调用父类构造函数
            x_coor(_x_coor),y_coor(_y_coor),color(Color::RED)
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

class BlueElectron : public StateMachine
{
    private:
    static BlueElectron *m_pInstance;

    public:
    long x_coor;
    long y_coor;
    Color color;

    public:
    BlueElectron(GameController* _FSM_Owner, int _x_coor, int _y_coor):
            StateMachine<GameController>(_FSM_Owner),x_coor(_x_coor),y_coor(_y_coor),color(Color::BLUE) //子类构造函数必须要调用父类构造函数
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

class HintStateMachine : public StateMachine
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

class Photon : public StateMachine
{
    private:
    static Photon *m_pInstance;

    public:
    long x_coor;
    long y_coor;
    Chartlet chartlet = new Chartlet<Photon>(m_pInstance, &photon_aprnc, &photon_aprnc_Xofst, &photon_aprnc_Yofst, photon_aprnc_length);

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
    HintStateMachine hint_state_machine;
    Photon photon;
    RedElectron red_electron;
    BlueElectron blue_electron;

    GameController():hint_state_machine(),photon(this),red_electron(this),blue_electron(this),Controller()
    {
        this->Init();
    }

    static void fallingDetected();
    

    virtual void HandleInput();
    virtual void Init();
    virtual void Update();
};

//速度重分配，计算碰撞，动量守恒
void VeloRdsrbt()
{

}


#endif
