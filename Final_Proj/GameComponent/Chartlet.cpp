#include "Chartlet.hpp"

char gnd_aprnc_1_element[] = 
{
       '/','-','O','-','\\',
   '|',' ','^','o','^',' ','|',
      '\\','-','O','-','/'
};

long gnd_aprnc_1_Xofst[] =
{
    -2L, -1L, 0L, 1L, 2L,
    -3L, -2L, -1L, 0L, 1L, 2L, 3L,
    -2L, -1L, 0L, 1L, 2L
};

long gnd_aprnc_1_Yofst[] =
{
    1L, 1L, 1L, 1L, 1L, 
    0L, 0L, 0L, 0L, 0L, 0L, 0L, 
    -1L, -1L, -1L, -1L, -1L
};

int gnd_aprnc_1_length = 17;

/*----------------------------*/

char gnd_aprnc_2_element[] = 
{
       '/','-','O','-','\\',
   '|',' ','0','v','0',' ','|',
      '\\','-','O','-','/'
};

long gnd_aprnc_2_Xofst[] =
{
    -2L, -1L, 0L, 1L, 2L,
    -3L, -2L, -1L, 0L, 1L, 2L, 3L,
    -2L, -1L, 0L, 1L, 2L
};

long gnd_aprnc_2_Yofst[] =
{
    1L, 1L, 1L, 1L, 1L, 
    0L, 0L, 0L, 0L, 0L, 0L, 0L, 
    -1L, -1L, -1L, -1L, -1L
};

int gnd_aprnc_2_length = 17;

/*----------------------------*/

char exc_aprnc_1_element[] = 
{
                'A','-','A','-','A',
    '<','/','#','-','=','-','=','-','#','\\','>',
'<','|','|',' ',' ','T','A','T',' ',' ','|','|','>',
    '<','\\','#','-','=','-','=','-','#','/','>',
                'V','-','V','-','V'
};

long exc_aprnc_1_Xofst[] =
{
    -2L, -1L, 0L, 1L, 2L,
    -5L, -4L, -3L, -2L, -1L, 0L, 1L, 2L, 3L, 4L, 5L,
    -7L, -6L, -5L, -4L, -3L, -2L, -1L, 0L, 1L, 2L, 3L, 4L, 5L, 6L, 7L,
    -5L, -4L, -3L, -2L, -1L, 0L, 1L, 2L, 3L, 4L, 5L,
    -2L, -1L, 0L, 1L, 2L
};

long exc_aprnc_1_Yofst[] =
{
    2L, 2L, 2L, 2L, 2L,  
    1L, 1L, 1L, 1L, 1L, 1L, 1L, 1L, 1L, 1L, 1L, 
    0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 
    -1L, -1L, -1L, -1L, -1L, -1L, -1L, -1L, -1L, -1L, -1L, 
    -2L, -2L, -2L, -2L, -2L
};

int exc_aprnc_1_length = 52;

/*----------------------------*/

char exc_aprnc_2_element[] = 
{
                'A','-','A','-','A',
    '<','/','#','-','=','-','=','-','#','\\','>',
'<','|','|',' ',' ','X','^','X',' ',' ','|','|','>',
    '<','\\','#','-','=','-','=','-','#','/','>',
                'V','-','V','-','V'
};

long exc_aprnc_2_Xofst[] =
{
    -2L, -1L, 0L, 1L, 2L,
    -5L, -4L, -3L, -2L, -1L, 0L, 1L, 2L, 3L, 4L, 5L,
    -7L, -6L, -5L, -4L, -3L, -2L, -1L, 0L, 1L, 2L, 3L, 4L, 5L, 6L, 7L,
    -5L, -4L, -3L, -2L, -1L, 0L, 1L, 2L, 3L, 4L, 5L,
    -2L, -1L, 0L, 1L, 2L
};

long exc_aprnc_2_Yofst[] =
{
    2L, 2L, 2L, 2L, 2L,  
    1L, 1L, 1L, 1L, 1L, 1L, 1L, 1L, 1L, 1L, 1L, 
    0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 
    -1L, -1L, -1L, -1L, -1L, -1L, -1L, -1L, -1L, -1L, -1L, 
    -2L, -2L, -2L, -2L, -2L
};

int exc_aprnc_2_length = 52;

/*----------------------------*/

char photon_aprnc_exist_element[] = 
{
    '(','$',')'
};

long photon_aprnc_exist_Xofst[] = 
{
    -1L, 0L, 1L
};

long photon_aprnc_exist_Yofst[] = 
{
    0L, 0L, 0L
};

int photon_aprnc_exist_length = 3;

/*----------------------------*/

char photon_aprnc_gone_element[] = 
{
    ' ',' ',' '
};

long photon_aprnc_gone_Xofst[] = 
{
    -1L, 0L, 1L
};

long photon_aprnc_gone_Yofst[] = 
{
    0L, 0L, 0L
};

int photon_aprnc_gone_length = 3;

/*-----------------------------------------------------------------*/
Chartlet *p_gnd_aprnc_1 = new Chartlet(gnd_aprnc_1_element, gnd_aprnc_1_Xofst, gnd_aprnc_1_Yofst, gnd_aprnc_1_length);
Chartlet *p_gnd_aprnc_2 = new Chartlet(gnd_aprnc_2_element, gnd_aprnc_2_Xofst, gnd_aprnc_2_Yofst, gnd_aprnc_2_length);
Chartlet *p_exc_aprnc_1 = new Chartlet(exc_aprnc_1_element, exc_aprnc_1_Xofst, exc_aprnc_1_Yofst, exc_aprnc_1_length);
Chartlet *p_exc_aprnc_2 = new Chartlet(exc_aprnc_2_element, exc_aprnc_2_Xofst, exc_aprnc_2_Yofst, exc_aprnc_2_length);
Chartlet *p_photon_aprnc_exist = new Chartlet(photon_aprnc_exist_element, photon_aprnc_exist_Xofst, photon_aprnc_exist_Yofst, photon_aprnc_exist_length);
Chartlet *p_photon_aprnc_gone = new Chartlet(photon_aprnc_gone_element, photon_aprnc_gone_Xofst, photon_aprnc_gone_Yofst, photon_aprnc_gone_length);
