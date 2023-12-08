#include "GameController.hpp"

void GameController::HandleInput()
{
}

void GameController::Init()
{
	bspInit();
    wiringPiISR(GPIO_BUTTON,INT_EDGE_FALLING,&GameController::fallingDetected);
}

void GameController::Update()
{
    HandleInput();
    Battle_state_machine.Update();
	// printf("Red: %d, Green: %d, Blue: %d \n", digitalRead(GPIO_RED), digitalRead(GPIO_GREEN), digitalRead(GPIO_BLUE));
}

void GameController::fallingDetected()
{
 //   printf("Button Pressed!\n");
    last_btn_millis = millis();
}

int GameController::buttonState()
{
    if(millis() == last_btn_millis + BUTTON_DELAY)
    {
    }
}