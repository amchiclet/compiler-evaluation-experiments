#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  b[32000] ;
extern float  a[32000] ;

void loop()
{
#pragma scop

    for(int i = 4; i < 32000; i++)
    {
        b[i] = b[i - 4] + a[i];
    }

#pragma endscop
}
