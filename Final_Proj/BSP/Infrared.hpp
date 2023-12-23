#ifndef Infrared_HPP
#define Infrared_HPP

#include <wiringPi.h>
#include <stdint.h>

#define TOLERANCE 300 /* us */
#define DIGIT_START 13500 /* us */
#define DIGIT_REPEAT 11250 /* us */
#define DIGIT_0 1125 /* us */
#define DIGIT_1 2250 /* us */

enum IRReadingState
{
    READING_BIT = 0, //正在读数据位
    WAITING_SIG = 1, //等待新的信号，这个状态在开始 REPEAT 或 IDLE 的时候进入
    COMING_SIG = 2 // IDLE 之后有码元来了，只可能是 START 或者 REPEAT，抑或是个错误数据
    //高电平 IDLE 之后只会出现 START 和 REPEAT!
};

int IR_digit_length_us = 0;
int IR_last_us = 0;
IRReadingState IR_reading_state = WAITING_SIG;
int IR_bit_count = 0;

int IR_repeat_flag = 0;
uint8_t IR_true_value = 0;

int readBit()
{
    if (IR_digit_length_us > DIGIT_0 - TOLERANCE && IR_digit_length_us < DIGIT_0 + TOLERANCE)
    {
        return 0;
    }
    else if (IR_digit_length_us > DIGIT_1 - TOLERANCE && IR_digit_length_us < DIGIT_1 + TOLERANCE)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void IRhandleInput()
{
    if (IR_reading_state == WAITING_SIG)
    {
        IR_last_us = micros();
        IR_reading_state = COMING_SIG;
    }
    else if (IR_reading_state == COMING_SIG)
    {
        IR_digit_length_us = micros() - IR_last_us;
        IR_last_us = micros();
        if (IR_digit_length_us > DIGIT_START - TOLERANCE && IR_digit_length_us < DIGIT_START + TOLERANCE)
        {
            //START 以后肯定立刻跟着数据，可以直接开始读
            IR_bit_count = 0;
            IR_reading_state = READING_BIT;
            IR_repeat_flag = 0;
        }
        else if (IR_digit_length_us > DIGIT_REPEAT - TOLERANCE && IR_digit_length_us < DIGIT_REPEAT + TOLERANCE)
        {
            //REPEAT 以后会有长时间高电平，并且可能跟 START 也可能跟 REPEAT
            IR_repeat_flag = 1;
            IR_reading_state = WAITING_SIG;
        }
    }
    else if (IR_reading_state == READING_BIT)
    {
        IR_digit_length_us = micros() - IR_last_us;
        IR_last_us = micros();

        if(IR_bit_count < 16)
        {
            if(readBit() == 1 || readBit() == 0)
            {
                IR_bit_count++;
            }
            else
            {
                // printf("Error!");
            }
        } //只要第三个字节的数据, 前面的和后面的全部扔掉不要
        else if(IR_bit_count >= 16 && IR_bit_count < 24)
        {
            if(readBit() == 1)
            {
                IR_true_value |= (0x01 << ((IR_bit_count - 16) % 8));
                IR_bit_count++;
            }
            else if(readBit() == 0)
            {
                IR_true_value &= ~(0x01 << ((IR_bit_count - 16) % 8));
                IR_bit_count++;
            }
            else
            {
                // printf("Error!!!");
            }
        }
        else if(IR_bit_count >= 24 && IR_bit_count < 32)
        {
            if(readBit() == 1 || readBit() == 0)
            {
                IR_bit_count++;
            }
            else
            {
                // printf("Error!!!!!");
            }
        }
        else
        {
            //数据帧结束了，进入重复帧或者起始帧
            IR_reading_state = WAITING_SIG;
            IR_bit_count = 0;
        }
    }
}

#endif