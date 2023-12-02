#ifndef bsp_HPP
#define bsp_HPP

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <wiringPi.h> 
#include <stdint.h>

#define GPIO_BEEP 1

void bspInit(void);
void bspSetFreq(int _freq);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
