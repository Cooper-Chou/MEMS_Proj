#include "Shader.hpp"
#include <stdio.h>
#include "MATH.h"
#include "../StateMachine/XonStateMachineDefine.hpp"
#include "../StateMachine/GameController.hpp"
#include "errno.h"

long MAP_HEIGHT = 0;
long MAP_WIDTH = 0;

void Shader::RefreshMap()
{
    rewind(fp_temp_map); //确保文件指针在开头
    rewind(fp_origin_map); //确保文件指针在开头
    char _buffer_char = fgetc(fp_origin_map);
    while(_buffer_char!=EOF)
    {
        fputc(_buffer_char,fp_temp_map);
    }
    _buffer_char = fgetc(fp_origin_map);
}

void Shader::Init()
{
    //初始化时就把地图读入
	fp_origin_map = fopen("/home/cooper/MicroComProj/Final_Proj/GameComponent/ORIGIN_MAP.txt", "r");
    fp_temp_map = fopen("/home/cooper/MicroComProj/Final_Proj/GameComponent/MAP_temp.txt", "w+");
    if(fp_origin_map == NULL || fp_temp_map == NULL)
    {
        int errNum = errno;
        perror("Open files error");
        printf("Open files failed!\n");
        return;
    }
    //此处打开文件以后先不关闭, 要等到游戏结束以后再关闭, 不然会反复读写磁盘,运行速度会变慢

	if (feof(fp_origin_map))
	{
		printf("Open MAP.txt failed!\n");
    }

    rewind(fp_temp_map); //确保文件指针在开头
    rewind(fp_origin_map); //确保文件指针在开头
    int width_count_flag = 0;
    file_length = 0;

    char _buffer_char = fgetc(fp_origin_map);
    while(_buffer_char!=EOF)
    {
        //计算行像素数
        if(_buffer_char != '\n')
        {
            if(width_count_flag == 0)
            {
                MAP_WIDTH++;
            }
        }
        //计算列像素数
        else
        {
            MAP_HEIGHT++;
            width_count_flag = 1;
        }
        fputc(_buffer_char,fp_temp_map);
        file_length++;
        _buffer_char = fgetc(fp_origin_map);
    }
    //减去边界的像素，剩下的就完全是游戏角色可以到达的地方
    MAP_WIDTH -= 2;
    MAP_HEIGHT -= 2;
}

void Shader::Shade(GameController* _p_controller)
{
    RefreshMap();

    for(int i = 0; i < Color::COLOR_NUM + PHOTON_NUM; i++)
    {
        for(int j = 0; j < _p_controller->shading_xon_p_list[i]->GetPCurrentState()->p_chartlet->length; j++)
        {
            long element_linear_coor = 0L;
            long element_y_coor = _p_controller->shading_xon_p_list[i]->y_coor + (_p_controller->shading_xon_p_list[i]->GetPCurrentState()->p_chartlet->aprnc_Yofst)[j];
            long element_x_coor = _p_controller->shading_xon_p_list[i]->x_coor + (_p_controller->shading_xon_p_list[i]->GetPCurrentState()->p_chartlet->aprnc_Xofst)[j];
            
            //贴图的中心的坐标默认已经取过模，这里要在加上偏移量以后再取一次模，实现周期性边界的效果
            element_y_coor = modulus<long>(element_y_coor - 1, MAP_HEIGHT) + 1;
            element_x_coor = modulus<long>(element_x_coor - 1, MAP_WIDTH) + 1;
            //上面 -1 + 1 -2 的目的是减去边框，因为实际游戏区域比地图小一圈，就是小了边框
            
            element_linear_coor = (MAP_HEIGHT + 2 - element_y_coor)*(MAP_WIDTH + 2 + 1)//此处 +2 是补上边框,  +1 是为了包含换行符
                                     + element_x_coor;
            fseek(fp_temp_map, (element_linear_coor-1L)*sizeof(char), SEEK_SET); //此处偏移量需要减1, 比如在坐标为1的时候, 就是相对于文件开头不偏移
            if(fgetc(fp_temp_map) == ' ')
            {
                fseek(fp_temp_map, -sizeof(char), SEEK_CUR); //fgetc()以后会往后移一格, 要移回去
                fputc((_p_controller->shading_xon_p_list[i]->GetPCurrentState()->p_chartlet->aprnc)[j],fp_temp_map);
            }
            else
            {
                fseek(fp_temp_map, -sizeof(char), SEEK_CUR); //fgetc()以后会往后移一格, 要移回去
                fputc(BLOCK_SHAPE,fp_temp_map); //贴图如果有重叠区域就进行特殊渲染
            }
        }
    }
}

void Shader::Display()
{
    rewind(fp_temp_map); //从头开始显示

    char _buffer_char;
    while((_buffer_char = fgetc(fp_temp_map))!=EOF)
    {
        printf("%c",_buffer_char);
    }
}

void Shader::Close()
{
    fclose(fp_temp_map);
    fclose(fp_origin_map);
}