#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float s;
extern float  a[32000] ;
extern float  b[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        s +=((float )2.);
        a[i] = s * b[i];
    }

#pragma endscop
}
