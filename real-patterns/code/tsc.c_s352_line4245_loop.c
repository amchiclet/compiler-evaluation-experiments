#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float dot;
extern float  a[32000] ;
extern float  b[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i += 5)
    {
        dot = dot + a[i] * b[i] + a[i + 1] * b[i + 1] + a[i + 2] * b[i + 2] + a[i + 3] * b[i + 3] + a[i + 4] * b[i + 4];
    }

#pragma endscop
}
