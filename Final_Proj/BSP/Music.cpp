#include "Music.hpp"

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

int redWinSongLength = 62;

/*--------------------------------------*/

int blueWinSong[] = 
{

};

int blueWinSongLength = 62;

/*--------------------------------------*/

int battleSong[] = 
{

};

int battleSongLength = 62;

/*--------------------------------------*/

int peaceSong[] = 
{

};

int peaceSongLength = 62;


/*--------------------------------------*/

Music* p_redWin = new Music(redWinSong, redWinSongLength);
Music* p_blueWin = new Music(blueWinSong, blueWinSongLength);
Music* p_battle = new Music(battleSong, battleSongLength);
Music* p_peace = new Music(peaceSong, peaceSongLength);
