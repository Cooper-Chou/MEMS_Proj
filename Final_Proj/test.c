#include <stdio.h>
#include <cmath>

int main()
{
    printf("\033[0m\033[1;31m%c\033[0m \n", 'a');
    printf("%f, %f, %f, %f, %f, %f, %f, %f, %f\n", cosf(M_PI*0.0f), cosf(M_PI*0.25f), cosf(M_PI*0.5f), cosf(M_PI*0.75f), cosf(M_PI), cosf(M_PI*1.25f), cosf(M_PI*1.5f), cosf(M_PI*1.75f), cosf(M_PI*2.0f));
    printf("%f, %f, %f, %f, %f, %f, %f, %f, %f\n", cosf(M_PI*1.0f), cosf(M_PI*1.25f), cosf(M_PI*1.5f), cosf(M_PI*1.75f), cosf(2.0f*M_PI), cosf(M_PI*2.25f), cosf(M_PI*2.5f), cosf(M_PI*2.75f), cosf(M_PI*3.0f));
    // printf("%f, %f, %f, %f, %f\n", std::asin());
    return 0;
}