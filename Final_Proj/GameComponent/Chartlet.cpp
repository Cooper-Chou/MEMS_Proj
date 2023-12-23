#include "Chartlet.hpp"

char gnd_aprnc_1_element[] = 
{
       '/','-','O','-','\\',
   '|',' ','^','o','^',' ','|',
      '\\','-','O','-','/'
};

int gnd_aprnc_1_Xofst[] =
{
    -2, -1, 0, 1, 2,
    -3, -2, -1, 0, 1, 2, 3,
    -2, -1, 0, 1, 2
};

int gnd_aprnc_1_Yofst[] =
{
    1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 
    -1, -1, -1, -1, -1
};

int gnd_aprnc_1_length = 17;

/*----------------------------*/

char gnd_aprnc_2_element[] = 
{
       '/','-','O','-','\\',
   '|',' ','0','v','0',' ','|',
      '\\','-','O','-','/'
};

int gnd_aprnc_2_Xofst[] =
{
    -2, -1, 0, 1, 2,
    -3, -2, -1, 0, 1, 2, 3,
    -2, -1, 0, 1, 2
};

int gnd_aprnc_2_Yofst[] =
{
    1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 
    -1, -1, -1, -1, -1
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

int exc_aprnc_1_Xofst[] =
{
    -2, -1, 0, 1, 2,
    -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5,
    -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6,
    -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5,
    -2, -1, 0, 1, 2
};

int exc_aprnc_1_Yofst[] =
{
    2, 2, 2, 2, 2,  
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -2, -2, -2, -2, -2
};

int exc_aprnc_1_length = 45;

/*----------------------------*/

char exc_aprnc_2_element[] = 
{
                'A','-','A','-','A',
    '<','/','#','-','=','-','=','-','#','\\','>',
'<','|','|',' ',' ','X','^','X',' ',' ','|','|','>',
    '<','\\','#','-','=','-','=','-','#','/','>',
                'V','-','V','-','V'
};

int exc_aprnc_2_Xofst[] =
{
    -2, -1, 0, 1, 2,
    -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5,
    -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6,
    -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5,
    -2, -1, 0, 1, 2
};

int exc_aprnc_2_Yofst[] =
{
    2, 2, 2, 2, 2,  
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -2, -2, -2, -2, -2
};

int exc_aprnc_2_length = 45;

/*----------------------------*/

char photon_aprnc_exist_element[] = 
{
    '(','$',')'
};

int photon_aprnc_exist_Xofst[] = 
{
    -1, 0, 1
};

int photon_aprnc_exist_Yofst[] = 
{
    0, 0, 0
};

int photon_aprnc_exist_length = 3;

/*----------------------------*/

char photon_aprnc_gone_element[] = 
{
    ' ',' ',' '
};

int photon_aprnc_gone_Xofst[] = 
{
    -1, 0, 1
};

int photon_aprnc_gone_Yofst[] = 
{
    0, 0, 0
};

int photon_aprnc_gone_length = 3;

/*-----------------------------------------------------------------*/
Chartlet *p_gnd_aprnc_1 = new Chartlet(gnd_aprnc_1_element, gnd_aprnc_1_Xofst, gnd_aprnc_1_Yofst, gnd_aprnc_1_length);
Chartlet *p_gnd_aprnc_2 = new Chartlet(gnd_aprnc_2_element, gnd_aprnc_2_Xofst, gnd_aprnc_2_Yofst, gnd_aprnc_2_length);
Chartlet *p_exc_aprnc_1 = new Chartlet(exc_aprnc_1_element, exc_aprnc_1_Xofst, exc_aprnc_1_Yofst, exc_aprnc_1_length);
Chartlet *p_exc_aprnc_2 = new Chartlet(exc_aprnc_2_element, exc_aprnc_2_Xofst, exc_aprnc_2_Yofst, exc_aprnc_2_length);
Chartlet *p_photon_aprnc_exist = new Chartlet(photon_aprnc_exist_element, photon_aprnc_exist_Xofst, photon_aprnc_exist_Yofst, photon_aprnc_exist_length);
Chartlet *p_photon_aprnc_gone = new Chartlet(photon_aprnc_gone_element, photon_aprnc_gone_Xofst, photon_aprnc_gone_Yofst, photon_aprnc_gone_length);
