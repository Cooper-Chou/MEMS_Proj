#include "BSP/bsp.hpp"
#include "StateMachine/GameController.hpp"
#include <wiringPi.h>

int main()
{
    bspInit();
    unsigned int last_tick = millis();
    while(1)
    {
        unsigned int current_tick = millis();
        if(current_tick - last_tick >= REFRESH_PERIOD)
        {
            last_tick = current_tick;
            GameController::GetInstance()->Update();
        }
    }
    return 0;
}