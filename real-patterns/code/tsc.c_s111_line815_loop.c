#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  b[32000] ;

void loop()
{
#pragma scop

    for(int i = 1; i < 32000; i += 2)
    {
        a[i] = a[i - 1] + b[i];
    }

#pragma endscop
}
