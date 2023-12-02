#ifndef bsp_HPP
#define bsp_HPP

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <wiringPi.h> 
#include <stdint.h>

#define GPIO_RED 29
#define GPIO_GREEN 28
#define GPIO_BLUE 27
#define GPIO_IR 17

void bspInit(void);
void bspLedOn(int _led_pin);
void bspLedOff(int _led_pin);
void bspLedToggle(int _led_pin);
uint8_t bspReadIR(int _IR_pin);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
