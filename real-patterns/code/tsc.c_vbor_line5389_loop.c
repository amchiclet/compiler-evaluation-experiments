#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float temp;
extern float  x[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        temp += x[i];
    }

#pragma endscop
}
