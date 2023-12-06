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

#define GPIO_IR 4
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

enum ReadingState
{
    READING_BIT = 0,
    FINISHED_BIT = 1,
    WAITING_SIG = 2,
    COMING_SIG = 3
    //长时间的高电平之后只会出现 START 和 REPEAT
};

unsigned int digit_length = 0;
unsigned int last_tick = 0;
ReadingState reading_state = WAITING_SIG;
int bit_count = 0;

int RepeatFlag = 0;
uint8_t true_value = 0;

int readBit()
{
    if (digit_length > DIGIT_0 - TOLERANCE && digit_length < DIGIT_0 + TOLERANCE)
    {
        return 0;
    }
    else if (digit_length > DIGIT_1 - TOLERANCE && digit_length < DIGIT_1 + TOLERANCE)
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
    if (reading_state == WAITING_SIG)
    {
        last_tick = micros();
        reading_state = COMING_SIG;
    }
    else if (reading_state == COMING_SIG)
    {
        digit_length = micros() - last_tick;
        last_tick = micros();
        if (digit_length > DIGIT_START - TOLERANCE && digit_length < DIGIT_START + TOLERANCE)
        {
            //START 以后肯定立刻跟着数据，可以直接开始读
            bit_count = 0;
            reading_state = READING_BIT;
            RepeatFlag = 0;
        }
        else if (digit_length > DIGIT_REPEAT - TOLERANCE && digit_length < DIGIT_REPEAT + TOLERANCE)
        {
            //REPEAT 以后会有长时间高电平，并且可能跟 START 也可能跟 REPEAT
            RepeatFlag = 1;
            reading_state = WAITING_SIG;
        }
    }
    else if (reading_state == READING_BIT)
    {
        digit_length = micros() - last_tick;
        last_tick = micros();

        if(bit_count < 16)
        {
            if(readBit() == 1 || readBit() == 0)
            {
                bit_count++;
            }
            else
            {
                // printf("Error!");
            }
        }
        else if(bit_count >= 16 && bit_count < 24)
        {
            if(readBit() == 1)
            {
                true_value |= (0x01 << ((bit_count - 16) % 8));
                bit_count++;
            }
            else if(readBit() == 0)
            {
                true_value &= ~(0x01 << ((bit_count - 16) % 8));
                bit_count++;
            }
            else
            {
                // printf("Error!!!");
            }
        }
        else if(bit_count >= 24 && bit_count < 32)
        {
            if(readBit() == 1 || readBit() == 0)
            {
                bit_count++;
            }
            else
            {
                // printf("Error!!!!!");
            }
        }
        else
        {
            //数据帧结束了，进入重复帧或者起始帧
            reading_state = WAITING_SIG;
            bit_count = 0;
            bit_used = 0;
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
				paint();
		}
	}
	return 0 ;
}