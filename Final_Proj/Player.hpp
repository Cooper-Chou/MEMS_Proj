#ifndef Player_HPP
#define Player_HPP

#define GROUND_APRNC_LENGTH 27
#define EXCITED_APRNC_LENGTH 45

class Player 
{
    //此处碰撞箱和贴图使用同一套体积，为了方便
    public:
    char ground_aprnc[GROUND_APRNC_LENGTH];
    int gorund_aprnc_xcoor[GROUND_APRNC_LENGTH];
    int gorund_aprnc_ycoor[GROUND_APRNC_LENGTH];

    char excited_aprnc[EXCITED_APRNC_LENGTH];
    int excited_aprnc_xcoor[EXCITED_APRNC_LENGTH];
    int excited_aprnc_ycoor[EXCITED_APRNC_LENGTH];
};

#endif