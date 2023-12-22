#ifndef Chartlet_HPP
#define Chartlet_HPP

class Chartlet
{
    public:
    char *aprnc;
    long *aprnc_Xofst;
    long *aprnc_Yofst;
    int length;

    Chartlet(char* _aprnc, long* _aprnc_Xofst, long* _aprnc_Yofst, int _length)
    {
        aprnc = _aprnc;
        aprnc_Xofst = _aprnc_Xofst;
        aprnc_Yofst = _aprnc_Yofst;
        length = _length;
    }
};

extern char gnd_aprnc_1_element[];

extern long gnd_aprnc_1_Xofst[];

extern long gnd_aprnc_1_Yofst[];

extern int gnd_aprnc_1_length;

/*----------------------------*/

extern char gnd_aprnc_2_element[];

extern long gnd_aprnc_2_Xofst[];

extern long gnd_aprnc_2_Yofst[];

extern int gnd_aprnc_2_length;

/*----------------------------*/

extern char exc_aprnc_1_element[];

extern long exc_aprnc_1_Xofst[];

extern long exc_aprnc_1_Yofst[];

extern int exc_aprnc_1_length;

/*----------------------------*/

extern char exc_aprnc_2_element[];

extern long exc_aprnc_2_Xofst[];

extern long exc_aprnc_2_Yofst[];

extern int exc_aprnc_2_length ;

/*----------------------------*/

extern char photon_aprnc_exist_element[];

extern long photon_aprnc_exist_Xofst[];

extern long photon_aprnc_exist_Yofst[];

extern int photon_aprnc_exist_length;

/*----------------------------*/

extern char photon_aprnc_gone_element[];

extern long photon_aprnc_gone_Xofst[];

extern long photon_aprnc_gone_Yofst[];

extern int photon_aprnc_gone_length;

/*-----------------------------------------------------------------*/
extern Chartlet *p_gnd_aprnc_1;
extern Chartlet *p_gnd_aprnc_2;
extern Chartlet *p_exc_aprnc_1;
extern Chartlet *p_exc_aprnc_2;
extern Chartlet *p_photon_aprnc_exist;
extern Chartlet *p_photon_aprnc_gone;

#endif