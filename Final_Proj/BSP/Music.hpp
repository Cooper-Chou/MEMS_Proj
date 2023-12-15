#ifndef LYRICS_HPP
#define LYRICS_HPP

#include <wiringPi.h>
#include <stdio.h>
#include "bsp.hpp"

#define DO_L 262
#define RE_L 294
#define MI_L 330
#define FA_L 349
#define SO_L 392
#define LA_L 440
#define XI_L 494
#define DO_M 523
#define RE_M 578
#define MI_M 659
#define FA_M 698
#define SO_M 784
#define LA_M 880
#define XI_M 988
#define DO_H 1046
#define RE_H 1175
#define MI_H 1318
#define FA_H 1397
#define SO_H 1568
#define LA_H 1760
#define XI_H 1976

#define BEAT 300 /* ms */

#define RED_WIN_SONG_LENGTH 62
#define BLUE_WIN_SONG_LENGTH 62
#define PEACE_SONG_LENGTH 62
#define BATTLE_SONG_LENGTH 62

class Music
{
	int (*lyrics)[];
	int length;
	int current_song_index = 0;
	unsigned int last_tick;
	Music(int (*_lyrics)[], int _length);
	void play()
	{
		if(millis() - last_tick >= BEAT)
		{
			if(current_song_index < length)
			{
				bspSetFreq((*lyrics)[current_song_index]);
				current_song_index++;
			}
			else
			{
				//Play repeatedly
				current_song_index = 0;
			}
		}
	}
};

int redWinSong[] = 
{
	MI_M, MI_M, MI_M, RE_M, 
	MI_M, RE_M, MI_M, SO_M, 
	SO_M, DO_H, DO_H, XI_M, 
	XI_M, MI_M, MI_M, RE_M, 
	MI_M, MI_M, MI_M, RE_M, 
	MI_M, RE_M, MI_M, DO_H,
	DO_H, DO_H, DO_H, XI_M, 
	RE_H, RE_H, MI_M, MI_M, 
	MI_M, MI_M, MI_M, RE_M,
	MI_M, RE_M, MI_M, XI_M, 
	XI_M, DO_H, DO_H, XI_M, 
	XI_M, MI_M, MI_M, RE_M,
	MI_M, MI_M, MI_M, RE_M, 
	MI_M, RE_M, MI_M, XI_M,
	XI_M, DO_H, DO_H, RE_H,
	RE_H, RE_H
};

int blueWinSong[] = 
{

};

int battleSong[] = 
{

};

int peaceSong[] = 
{

};

#endif