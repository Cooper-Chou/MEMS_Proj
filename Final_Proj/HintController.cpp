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
}

void HintController::Init()
{
	bspInit();
    wiringPiISR(GPIO_BUTTON,INT_EDGE_FALLING,&HintController::fallingDetected);
}

void HintController::Update()
{
    HandleInput();
    hint_state_machine.Update();
	// printf("Red: %d, Green: %d, Blue: %d \n", digitalRead(GPIO_RED), digitalRead(GPIO_GREEN), digitalRead(GPIO_BLUE));
}

void HintController::fallingDetected()
{
 //   printf("Button Pressed!\n");
    last_btn_millis = millis();
}

int HintController::buttonState()
{
    if(millis() == last_btn_millis + BUTTON_DELAY)
    {
    }
}