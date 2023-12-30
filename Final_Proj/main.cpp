#include "BSP/bsp.hpp"
#include "StateMachine/GameController.hpp"
#include <wiringPi.h>

int main()
{
    bspInit();
    extern int break_flag;
    int last_tick = millis();
    while(break_flag == 0)
    {
        int current_tick = millis();
        if(current_tick - last_tick >= REFRESH_PERIOD)
        {
            last_tick = current_tick;
            GameController::GetInstance()->Update();
        }
        
        GameController::GetInstance()->hint_state_machine.Update(); 
    }
    pwmWrite(GPIO_BEEP, 0);
    return 0;
}