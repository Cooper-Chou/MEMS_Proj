#ifndef MotionController_HPP
#define MotionController_HPP

#include <StateMachine.hpp>
#include <stdio.h>
#include <stdint.h>
#include "bsp.hpp"
#include "MotionStateDefine.hpp"
#include "Controller.hpp"

#define LED_STATE_UPDATE_PERIOD 2 /*ms*/
#define BUTTON_DELAY 100 /*ms*/

class MotionStateMachine : public StateMachine
{
    public:
        MotionStateMachine():StateMachine()
        {
            this->Init();
        }
        
        virtual void Init();
};

class MotionController : public Controller
{
    public:
    static unsigned int last_millis;
    static unsigned int current_millis;
    static uint8_t press_count;
    MotionStateMachine Motion_state_machine;

    MotionController():Motion_state_machine()
    {
        this->Init();
    }

    static void fallingDetected();

    virtual void HandleInput();
    virtual void Init();
    virtual void Update();
};


#endif
