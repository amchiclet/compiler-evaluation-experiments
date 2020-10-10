#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int inc;
extern float  a[32000] ;
extern float  b[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000 - 1; i += inc)
    {
        a[i] = a[i + inc] + b[i];
    }

#pragma endscop
}
