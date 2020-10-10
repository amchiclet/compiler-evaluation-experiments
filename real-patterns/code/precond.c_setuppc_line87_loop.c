#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nmor;
extern double  dpcmor[92700] ;

void loop()
{
#pragma scop

    for(i = 0; i < nmor; i++)
    {
        dpcmor[i] = 1.0 / dpcmor[i];
    }

#pragma endscop
}
