#ifndef GameController_HPP
#define GameController_HPP

#include <stdio.h>
#include <stdint.h>
#include "bsp.hpp"
#include "Controller.hpp"

#define BUTTON_DELAY 20 /*ms*/

class GameController : public Controller
{
    public:
    static unsigned int current_millis;
    static unsigned int last_btn_millis;
    HintStateMachine Attack_state_machine;

    GameController():Attack_state_machine()
    {
        this->Init();
    }

    static void fallingDetected();
    

    virtual void HandleInput();
    virtual void Init();
    virtual void Update();
};


#endif
