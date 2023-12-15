#ifndef Chartlet_HPP
#define Chartlet_HPP

#include "GameController.hpp"

template<typename _xon>
class Chartlet
{
    protected:
    _xon* p_chart_owner;

    public:
    char (*aprnc)[];
    long (*aprnc_Xofst)[];
    long (*aprnc_Yofst)[];
    int length;

    Chartlet()
    {
        this->Init();
    }

    Init(_xon* _p_chart_onwer, char (*_aprnc)[], long (*_aprnc_Xofst)[], long (*_aprnc_Yofst)[], int _length)
    {
        p_chart_owner = _p_chart_onwer;
        aprnc = _aprnc;
        aprnc_Xofst = _aprnc_Xofst;
        aprnc_Yofst = _aprnc_Yofst;
        length = _length;
    }

    long GetOwnerXCoor()
    {
        return p_chart_owner->x_coor;
    }

    long GetOwnerYCoor()
    {
        return p_chart_owner->y_coor;
    }
};

char gnd_aprnc_1[] = 
{
       '/','-','O','-','\\',
   '|',' ','^','o','^',' ','|',
      '\\','-','O','-','/'
};

long gnd_aprnc_1_Xofst[] =
{
    -2, -1, 0, 1, 2,
    -3, -2, -1, 0, 1, 2, 3,
    -2, -1, 0, 1, 2
};

long gnd_aprnc_1_Yofst[] =
{
    1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 
    -1, -1, -1, -1, -1
};

int gnd_aprnc_1_length = 17;

/*----------------------------*/

char gnd_aprnc_2[] = 
{
       '/','-','O','-','\\',
   '|',' ','0','v','0',' ','|',
      '\\','-','O','-','/'
};

long gnd_aprnc_2_Xofst[] =
{
    -2, -1, 0, 1, 2,
    -3, -2, -1, 0, 1, 2, 3,
    -2, -1, 0, 1, 2
};

long gnd_aprnc_2_Yofst[] =
{
    1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 
    -1, -1, -1, -1, -1
};

int gnd_aprnc_2_length = 17;

/*----------------------------*/

char exc_aprnc_1[] = 
{
                'A','-','A','-','A',
    '<','/','#','-','=','-','=','-','#','\\','>',
'<','|','|',' ',' ','T','A','T',' ',' ','|','|','>',
    '<','\\','#','-','=','-','=','-','#','/','>',
                'V','-','V','-','V'
};

long exc_aprnc_1_Xofst[] =
{
    -2, -1, 0, 1, 2,
    -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5,
    -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7,
    -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5,
    -2, -1, 0, 1, 2
};

long exc_aprnc_1_Yofst[] =
{
    2, 2, 2, 2, 2,  
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -2, -2, -2, -2, -2
};

int exc_aprnc_1_length = 52;

/*----------------------------*/

char exc_aprnc_2[] = 
{
                'A','-','A','-','A',
    '<','/','#','-','=','-','=','-','#','\\','>',
'<','|','|',' ',' ','X','^','X',' ',' ','|','|','>',
    '<','\\','#','-','=','-','=','-','#','/','>',
                'V','-','V','-','V'
};

long exc_aprnc_2_Xofst[] =
{
    -2, -1, 0, 1, 2,
    -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5,
    -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7,
    -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5,
    -2, -1, 0, 1, 2
};

long exc_aprnc_2_Yofst[] =
{
    2, 2, 2, 2, 2,  
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -2, -2, -2, -2, -2
};

int exc_aprnc_2_length = 52;

/*----------------------------*/

char photon_aprnc[] = 
{
    '(','$',')'
};

long photon_aprnc_Xofst[] = 
{
    -1, 0, 1
};

long photon_aprnc_Yofst[] = 
{
    0, 0, 0
};

int photon_aprnc_length = 3;

#endif