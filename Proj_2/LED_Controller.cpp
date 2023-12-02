#include "LED_Controller.hpp"

void LED_StateMachine::Init()
{
    // 这个地方创建了几个实例，就决定了有几个状态！
    State_RedBlink::GetInstance()->Init();
    State_RedOn::GetInstance()->Init();
    State_GreenBlink::GetInstance()->Init();
    State_GreenOn::GetInstance()->Init();
    State_BlueBlink::GetInstance()->Init();
    State_BlueOn::GetInstance()->Init();
    setCurrentState(State_RedBlink::GetInstance());
}

void LED_Controller::HandleInput()
{
    if(millis() == last_btn_millis + BUTTON_DELAY)
    {
        if(digitalRead(GPIO_BUTTON) == LOW)
        {
            press_count += 1;
        }
    }

    switch (press_count % 6)
    {
    case 0:
        led_state_machine.ChangeState(State_RedBlink::GetInstance());
        break;
    case 1:
        led_state_machine.ChangeState(State_RedOn::GetInstance());
        break;
    case 2:
        led_state_machine.ChangeState(State_GreenBlink::GetInstance());
        break;
    case 3:
        led_state_machine.ChangeState(State_GreenOn::GetInstance());
        break;
    case 4:
        led_state_machine.ChangeState(State_BlueBlink::GetInstance());
        break;
    case 5:
        led_state_machine.ChangeState(State_BlueOn::GetInstance());
        break;
    }
}

void LED_Controller::Init()
{
	bspInit();
    wiringPiISR(GPIO_BUTTON,INT_EDGE_FALLING,&LED_Controller::buttonPressed);
}

void LED_Controller::Update()
{
    HandleInput();
    led_state_machine.Update();
	// printf("Red: %d, Green: %d, Blue: %d \n", digitalRead(GPIO_RED), digitalRead(GPIO_GREEN), digitalRead(GPIO_BLUE));
}

void LED_Controller::buttonPressed()
{
 //   printf("Button Pressed!\n");
    last_btn_millis = millis();
}
