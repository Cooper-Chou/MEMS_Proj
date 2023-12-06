#ifndef LYRICS_HPP
#define LYRICS_HPP

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


#define SONG_LENGTH 62

int MySong[] = 
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

int songLength = SONG_LENGTH;

#endif