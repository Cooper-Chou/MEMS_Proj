#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>

#define TOLERANCE 300 /* us */
#define DIGIT_START 13500 /* us */
#define DIGIT_REPEAT 11250 /* us */
#define DIGIT_0 1125 /* us */
#define DIGIT_1 2250 /* us */

#define EMOJI_WIDTH 5 /* Should be ODD !!!*/
#define EMOJI_HEIGHT 3 /* Should be ODD !!!*/
#define HALF_EMOJI_WIDTH ((EMOJI_WIDTH - 1)/2)
#define HALF_EMOJI_HEIGHT ((EMOJI_HEIGHT - 1)/2)
#define CONVAS_WIDTH (232)
#define CONVAS_HEIGHT (56)

#define GPIO_IR 5
#define UP_SIG 24
#define DN_SIG 82
#define LF_SIG 8
#define RT_SIG 90

static int x_coor = CONVAS_WIDTH / 2;
static int y_coor = CONVAS_HEIGHT / 2; 

void paint()         
{
	if(x_coor < 1 + HALF_EMOJI_WIDTH)
	{
		x_coor = 1 + HALF_EMOJI_WIDTH;
	}
	else if(x_coor > CONVAS_WIDTH - HALF_EMOJI_WIDTH)
	{
		x_coor = CONVAS_WIDTH - HALF_EMOJI_WIDTH;
	}
	if(y_coor < 1 + HALF_EMOJI_HEIGHT)
	{
		y_coor = 1 + HALF_EMOJI_HEIGHT;
	}
	else if(y_coor > CONVAS_HEIGHT - HALF_EMOJI_HEIGHT)
	{
		y_coor = CONVAS_HEIGHT - HALF_EMOJI_HEIGHT;
	}

	for(int i = 0; i < y_coor - 1 - HALF_EMOJI_HEIGHT; i++)
	{
		printf("\n");
	}

	for(int i = 0; i < x_coor - HALF_EMOJI_WIDTH - 1; i++){printf(" ");}printf("\\-|-/\n");
	for(int i = 0; i < x_coor - HALF_EMOJI_WIDTH - 1; i++){printf(" ");}printf("*TAT*\n");
	for(int i = 0; i < x_coor - HALF_EMOJI_WIDTH - 1; i++){printf(" ");}printf("/-|-\\\n");

	for(int i = 0; i < CONVAS_HEIGHT - HALF_EMOJI_HEIGHT - y_coor; i++)
	{
		printf("\n");
	}
}

enum IRReadingState
{
    READING_BIT = 0, //正在读数据位
    WAITING_SIG = 1, //等待新的信号，这个状态在开始 REPEAT 或 IDLE 的时候进入
    COMING_SIG = 2 // IDLE 之后有码元来了，只可能是 START 或者 REPEAT，抑或是个错误数据
    //高电平 IDLE 之后只会出现 START 和 REPEAT!
};

unsigned int IR_digit_length_us = 0;
unsigned int last_tick = 0;
IRReadingState IR_reading_state = WAITING_SIG;
int IR_bit_count = 0;

int IR_repeat_flag = 0;
uint8_t true_value = 0;

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

void handleInput()
{
    if (IR_reading_state == WAITING_SIG)
    {
        last_tick = micros();
        IR_reading_state = COMING_SIG;
    }
    else if (IR_reading_state == COMING_SIG)
    {
        IR_digit_length_us = micros() - last_tick;
        last_tick = micros();
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
        IR_digit_length_us = micros() - last_tick;
        last_tick = micros();

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
                true_value |= (0x01 << ((IR_bit_count - 16) % 8));
                IR_bit_count++;
            }
            else if(readBit() == 0)
            {
                true_value &= ~(0x01 << ((IR_bit_count - 16) % 8));
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

int main()
{
    //初始化连接失败时，将消息打印到屏幕
	if(wiringPiSetup() == -1)
	{
		printf("setup wiringPi failed !");
		return 1; 
	}
    pinMode(GPIO_IR, INPUT);
    wiringPiISR(GPIO_IR, INT_EDGE_FALLING, &handleInput);

	static unsigned int count = millis();

	while(1)
	{
		printf("%d\n",true_value);
		if(millis() - count >= 100)
		{
			count = millis();
				switch (true_value)
				{
				case UP_SIG:
					y_coor -= 2;
					break;

				case DN_SIG:
					y_coor += 2;
					break;

				case LF_SIG:
					x_coor -= 4;
					break;

				case RT_SIG:
					x_coor += 4;
					break;
				
				default:
					break;
				}
				//paint();
		}
	}
	return 0 ;
}
