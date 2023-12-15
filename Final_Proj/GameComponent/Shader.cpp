#include "Shader.hpp"
#include <stdio.h>
#include "MATH.h"

void Shader::RefreshMap()
{
    rewind(fp_map); //确保文件指针在开头
    rewind(fp_origin_map); //确保文件指针在开头
    char _buffer_char;
    while((_buffer_char = fgetc(fp_origin_map))!=EOF)
    {
        fputc(_buffer_char,fp_map);
    }
}

void Shader::Init()
{
    //初始化时就把地图读入
	fp_origin_map = fopen("ORIGIN_MAP.txt", "r");
    fp_map = fopen("MAP.txt", "w+");
    //此处打开文件以后先不关闭, 要等到游戏结束以后再关闭, 不然会反复读写磁盘,运行速度会变慢

	if (feof(fp_origin_map))
	{
		printf("Open MAP.txt failed!");
    }

    rewind(fp_map); //确保文件指针在开头
    rewind(fp_origin_map); //确保文件指针在开头
    int width_count_flag = 0;
    MAP_WIDTH = 0;
    MAP_HEIGHT = 0;
    file_length = 0;

    char _buffer_char;
    while((_buffer_char = fgetc(fp_origin_map))!=EOF)
    {
        if(_buffer_char != '\n')
        {
            if(width_count_flag == 0)
            {
                MAP_WIDTH++;
            }
        }
        else
        {
            MAP_HEIGHT++;
            width_count_flag = 1;
        }
        fputc(_buffer_char,fp_map);
        file_length++;
    }
}

void Shader::Shade(Chartlet (*_element_list)[],int _element_num)
{
    RefreshMap();

    for(int i = 0; i < _element_num; i++)
    {
        for(int j = 0; j < (*_element_list)[i].length; j++)
        {
            long element_linear_coor = 0;
            long element_y_coor = (*_element_list)[i].p_chart_onwer->y_coor + (*(*_element_list)[i].aprnc_Yofst)[j];
            long element_x_coor = (*_element_list)[i].p_chart_onwer->x_coor + (*(*_element_list)[i].aprnc_Xofst)[j];
            //贴图的中心的坐标默认已经取过模，这里要在加上偏移量以后再取一次模，实现周期性边界的效果
            element_y_coor = modulus(element_y_coor - 1, MAP_HEIGHT - 2) + 1;
            element_x_coor = modulus(element_x_coor - 1, MAP_WIDTH - 2) + 1;
            //上面 -1 + 1 -2 的目的是减去边框，因为实际游戏区域比地图小一圈，就是小了边框
            
            element_linear_coor = (MAP_HEIGHT - element_y_coor)*(MAP_WIDTH+1)//此处 +1 是为了包含换行符
                                     + element_x_coor;
            fseek(fp_map, (element_linear_coor-1L)*sizeof(char), SEEK_SET); //此处偏移量需要减1, 比如在坐标为1的时候, 就是相对于文件开头不偏移
            if(fgetc(fp_map) == ' ')
            {
                fseek(fp_map, -sizeof(char), SEEK_CUR); //fgetc()以后会往后移一格, 要移回去
                fputc((*(*_element_list)[i].aprnc)[j],fp_map);
            }
            else
            {
                fseek(fp_map, -sizeof(char), SEEK_CUR); //fgetc()以后会往后移一格, 要移回去
                fputc(BLOCK_SHAPE,fp_map); //贴图如果有重叠区域就进行特殊渲染
            }
        }
    }
}

void Shader::Display()
{
    rewind(fp_map); //从头开始显示

    char _buffer_char;
    while((_buffer_char = fgetc(fp_map))!=EOF)
    {
        printf("%c",_buffer_char);
    }
}

void Shader::Close()
{
    fclose(fp_map);
    fclose(fp_origin_map);
}