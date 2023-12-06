#include "AttackController.hpp"

void AttackController::HandleInput()
{
}

void AttackController::Init()
{
	bspInit();
    wiringPiISR(GPIO_BUTTON,INT_EDGE_FALLING,&AttackController::fallingDetected);
}

void AttackController::Update()
{
    HandleInput();
    Attack_state_machine.Update();
	// printf("Red: %d, Green: %d, Blue: %d \n", digitalRead(GPIO_RED), digitalRead(GPIO_GREEN), digitalRead(GPIO_BLUE));
}

void AttackController::fallingDetected()
{
 //   printf("Button Pressed!\n");
    last_btn_millis = millis();
}

int AttackController::buttonState()
{
    if(millis() == last_btn_millis + BUTTON_DELAY)
    {
    }
}