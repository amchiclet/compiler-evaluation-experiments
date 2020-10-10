#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  b[32000] ;
extern float x;
extern float y;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        a[i] =(b[i] + x + y) *((float ).333);
        y = x;
        x = b[i];
    }

#pragma endscop
}
