#ifndef Shader_HPP
#define Shader_HPP

#include <stdio.h>
#include "Chartlet.hpp"

#define BLOCK_SHAPE '@'

class GameController;

class Shader
{
    public:
    //下面这两个数据自动从文件中获取, 不包括换行符!
    FILE* fp_origin_map;
    FILE* fp_temp_map;
    int file_length;

    public:
    void Init();
    void Shade(GameController* _p_controller);
    void Display();
    void RefreshMap();
    void Close();
    void AppendElement(int _element_x_coor, int _element_y_coor, char* _element_aprnc, int* _element_Xofst, int* _element_Yofst, int _element_length);
};

extern int MAP_WIDTH;
extern int MAP_HEIGHT;


#endif