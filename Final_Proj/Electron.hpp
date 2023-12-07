#ifndef Electron_HPP
#define Electron_HPP

#define GROUND_APRNC_LENGTH 27
#define EXCITED_APRNC_LENGTH 45

class Electron 
{
    //此处碰撞箱和贴图使用同一套体积，为了方便
    public:

    char excited_aprnc[EXCITED_APRNC_LENGTH];
    int excited_aprnc_Xofst[EXCITED_APRNC_LENGTH];
    int excited_aprnc_Yofst[EXCITED_APRNC_LENGTH];
};

#endif