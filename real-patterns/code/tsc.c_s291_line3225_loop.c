#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  b[32000] ;
extern int im1;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        a[i] =(b[i] + b[im1]) *((float ).5);
        im1 = i;
    }

#pragma endscop
}
