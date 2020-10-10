#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern int k;
extern float  b[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000 / 2; i++)
    {
        a[i + k] = a[i] + b[i];
    }

#pragma endscop
}
