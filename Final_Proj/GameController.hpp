#ifndef GameController_HPP
#define GameController_HPP

#include <stdio.h>
#include <stdint.h>
#include "bsp.hpp"
#include "Controller.hpp"

class GameController : public Controller
{
    public:
    static unsigned int current_millis;
    static unsigned int last_btn_millis;
    HintStateMachine Battle_state_machine;

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
