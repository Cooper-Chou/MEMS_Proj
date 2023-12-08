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

class Electron : public StateMachine
{
    public:
    int x_coor;
    int y_coor;
    Color color;

    public:
        Electron(GameController* _FSM_Owner):StateMachine<GameController>(_FSM_Owner) //子类构造函数必须要调用父类构造函数
        {
            this->Init();
        }
        
        virtual void Init();
};

class HintStateDefine : public StateMachine
{
    public:
        HintStateDefine():StateMachine() //子类构造函数必须要调用父类构造函数
        {
            this->Init();
        }
        
        virtual void Init();
};

class Photon : public StateMachine
{
    public:
    int x_coor;
    int y_coor;
    Chartlet chartlet;

    public:
        Photon():StateMachine() //子类构造函数必须要调用父类构造函数
        {
            this->Init();
        }
        
        virtual void Init();
};

class GameController : public Controller
{
    public:
    static unsigned int current_millis;
    static unsigned int last_btn_millis;
    HintStateDefine Battle_state_machine;

    GameController():Battle_state_machine()
    {
        this->Init();
    }

    static void fallingDetected();
    

    virtual void HandleInput();
    virtual void Init();
    virtual void Update();
};


#endif
