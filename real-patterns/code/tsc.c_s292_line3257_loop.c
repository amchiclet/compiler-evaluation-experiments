#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float  b[32000] ;
extern int im1;
extern int im2;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        a[i] =(b[i] + b[im1] + b[im2]) *((float ).333);
        im2 = im1;
        im1 = i;
    }

#pragma endscop
}
