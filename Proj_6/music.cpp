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
		printf("i = %d\n", i);
		//	int i = 0;
		//	scanf("%d", &i);
		bspSetFreq(MySong[i]);
		printf("%d\n", MySong[i]);
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
