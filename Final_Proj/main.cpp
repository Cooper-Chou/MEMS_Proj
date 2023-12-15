#include "GameController.hpp"
#include <wiringPi.h>

int main()
{
    GameController game_controller;
    unsigned int last_tick = millis();
    while(1)
    {
        unsigned int current_tick = millis();
        if(current_tick - last_tick >= REFRESH_PERIOD)
        {
            last_tick = current_tick;
            game_controller.Update();
        }
    }
    return 0;
}