#ifndef LED_Controller_HPP
#define LED_Controller_HPP

#include <StateMachine.hpp>
#include <stdio.h>
#include <stdint.h>
#include "bsp.hpp"
#include "LED_StateDefine.hpp"
#include "Controller.hpp"

#define LED_STATE_UPDATE_PERIOD 2 /*ms*/

class LED_StateMachine : public StateMachine
{
    public:
        LED_StateMachine():StateMachine()
        {
            this->Init();
        }
        
        virtual void Init();
};

class LED_Controller : public Controller
{
    public:
    static unsigned int last_millis;
    static unsigned int current_millis;
	static unsigned int last_falling_us;
	static unsigned int frame_last;

    LED_StateMachine led_state_machine;

    LED_Controller():led_state_machine()
    {
        this->Init();
    }

	void IRFalling();
    virtual void HandleInput();
    virtual void Init();
    virtual void Update();
};


#endif
