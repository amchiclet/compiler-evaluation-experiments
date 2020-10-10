#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern int m;
extern float  b[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000 - 1; i++)
    {
        a[i] = a[i + m] + b[i];
    }

#pragma endscop
}
