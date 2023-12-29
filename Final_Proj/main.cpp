#include "BSP/bsp.hpp"
#include "StateMachine/GameController.hpp"
#include <wiringPi.h>

int main()
{
    bspInit();
    int last_tick = millis();
    while(1)
    {
        int current_tick = millis();
        if(current_tick - last_tick >= REFRESH_PERIOD)
        {
            last_tick = current_tick;
            GameController::GetInstance()->Update();
        }
        
        GameController::GetInstance()->hint_state_machine.Update(); 
    }
    return 0;
}