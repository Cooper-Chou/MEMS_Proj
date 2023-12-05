#include "HintController.hpp"

void HintStateMachine::Init()
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

void HintController::HandleInput()
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
        hint_state_machine.ChangeState(State_RedBlink::GetInstance());
        break;
    case 1:
        hint_state_machine.ChangeState(State_RedOn::GetInstance());
        break;
    case 2:
        hint_state_machine.ChangeState(State_GreenBlink::GetInstance());
        break;
    case 3:
        hint_state_machine.ChangeState(State_GreenOn::GetInstance());
        break;
    case 4:
        hint_state_machine.ChangeState(State_BlueBlink::GetInstance());
        break;
    case 5:
        hint_state_machine.ChangeState(State_BlueOn::GetInstance());
        break;
    }
}

void HintController::Init()
{
	bspInit();
    wiringPiISR(GPIO_BUTTON,INT_EDGE_FALLING,&HintController::buttonPressed);
}

void HintController::Update()
{
    HandleInput();
    hint_state_machine.Update();
	// printf("Red: %d, Green: %d, Blue: %d \n", digitalRead(GPIO_RED), digitalRead(GPIO_GREEN), digitalRead(GPIO_BLUE));
}

void HintController::buttonPressed()
{
 //   printf("Button Pressed!\n");
    last_btn_millis = millis();
}
