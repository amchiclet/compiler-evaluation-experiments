#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  b[32000] ;
extern float x;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        a[i] =(b[i] + x) *((float ).5);
        x = b[i];
    }

#pragma endscop
}
