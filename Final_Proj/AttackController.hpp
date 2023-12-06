#ifndef AttackController_HPP
#define AttackController_HPP

#include <stdio.h>
#include <stdint.h>
#include "bsp.hpp"
#include "Controller.hpp"

#define BUTTON_DELAY 20 /*ms*/

class AttackController : public Controller
{
    public:
    static unsigned int current_millis;
    static unsigned int last_btn_millis;
    HintStateMachine Attack_state_machine;

    AttackController():Attack_state_machine()
    {
        this->Init();
    }

    static void fallingDetected();
    

    virtual void HandleInput();
    virtual void Init();
    virtual void Update();
};


#endif
