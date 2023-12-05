#ifndef HintController_HPP
#define HintController_HPP

#include <StateMachine.hpp>
#include <stdio.h>
#include <stdint.h>
#include "bsp.hpp"
#include "Controller.hpp"

#define BUTTON_DELAY 20 /*ms*/

class HintStateMachine : public StateMachine
{
    public:
        HintStateMachine():StateMachine()
        {
            this->Init();
        }
        
        virtual void Init();
};

class HintController : public Controller
{
    public:
    static unsigned int current_millis;
    static unsigned int last_btn_millis;
    HintStateMachine hint_state_machine;

    HintController():hint_state_machine()
    {
        this->Init();
    }

    static void fallingDetected();
    

    virtual void HandleInput();
    virtual void Init();
    virtual void Update();
};


#endif
