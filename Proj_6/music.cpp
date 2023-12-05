#include "bsp.hpp"
#include <stdio.h>
#include "lyrics.hpp"

#define BEAT 300 /*ms*/

int main(void)
{
	bspInit();
	printf("Song length = %d\n", songLength);
	for (int i = 0; i < songLength; i++)
	{
		bspSetFreq(MySong[i]);
		delay(BEAT);
	}
	pwmWrite(GPIO_BEEP, 0);
/*	int a = 0;
	while(1)
	{
		scanf("%d",&a);
		bspSetFreq(a);
	}
*/
}
