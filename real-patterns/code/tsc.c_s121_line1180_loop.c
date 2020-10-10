#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern float  a[32000] ;
extern float  b[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000 - 1; i++)
    {
        j = i + 1;
        a[i] = a[j] + b[i];
    }

#pragma endscop
}
