#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float temp;
extern float * restrict xx;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000 / 2; i++)
    {
        temp += xx[i];
    }

#pragma endscop
}
