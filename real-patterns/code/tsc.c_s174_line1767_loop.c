#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int M;
extern float  a[32000] ;
extern float  b[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < M; i++)
    {
        a[i + M] = a[i] + b[i];
    }

#pragma endscop
}
