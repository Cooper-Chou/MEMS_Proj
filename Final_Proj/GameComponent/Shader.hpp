#ifndef Shader_HPP
#define Shader_HPP

#include <stdio.h>
#include "Chartlet.hpp"

#define BLOCK_SHAPE '@'

class Shader
{
    public:
    //下面这两个数据自动从文件中获取, 不包括换行符!
    FILE* fp_origin_map;
    FILE* fp_map;
    int file_length;

    static int MAP_WIDTH;
    static int MAP_HEIGHT;
    
    Chartlet (*element_list)[];

    public:
    void Init();
    void Shade(Chartlet (*_element_list)[], int _element_num);
    void Display();
    void RefreshMap();
};


#endif