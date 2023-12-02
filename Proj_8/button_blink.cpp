#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include "LED_Controller.hpp"


	uint8_t LED_Controller::press_count = 0;
	unsigned int LED_Controller::last_millis;
	unsigned int LED_Controller::current_millis;
	unsigned int LED_Controller::last_btn_millis;

int main()
{
	wiringPiSetup();
	LED_Controller led_controller = LED_Controller();
	LED_Controller::last_millis = millis(); //Record the first time tick
//	printf("First time is: %d \n", LED_Controller::last_millis);
	while(1)
	{
		LED_Controller::current_millis = millis();
		if(LED_Controller::current_millis - LED_Controller::last_millis >= LED_STATE_UPDATE_PERIOD)
		{
			// printf("current_timeout: %d \n", LED_Controller::current_millis - LED_Controller::last_millis);
			LED_Controller::last_millis = LED_Controller::current_millis;
			led_controller.Update();
		}
	}
	return 0;
}


