#include "bsp.hpp"
#include <stdio.h>
#include "lyrics.hpp"

#define BEAT 500 /*ms*/

int main(void)
{
	bspInit();
	printf("Song length = %d\n", songLength);
	for(int i = 0;i < songLength;i++)	
	{
		printf("Note freq = %d Hz\n",MySong[i]);
		bspSetFreq(MySong[i]);
		delay(BEAT);
	}
	pwmWrite(GPIO_BEEP, 0); //演奏结束以后关掉声音
/*	int a = 0;
	while(1)
	{
		scanf("%d",&a);
		bspSetFreq(a);
	}
*/
}
