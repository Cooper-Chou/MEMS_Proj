#ifndef HintController_HPP
#define HintController_HPP

#include <StateMachine.hpp>
#include <stdio.h>
#include <stdint.h>
#include "bsp.hpp"
#include "LED_StateDefine.hpp"
#include "Controller.hpp"

#define LED_STATE_UPDATE_PERIOD 2 /*ms*/
#define BUTTON_DELAY 100 /*ms*/

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
    static unsigned int last_millis;
    static unsigned int current_millis;
    static unsigned int last_btn_millis;
    static uint8_t press_count;
    HintStateMachine hint_state_machine;

    HintController():hint_state_machine()
    {
        this->Init();
    }

    static void buttonPressed();

    virtual void HandleInput();
    virtual void Init();
    virtual void Update();
};


#endif
