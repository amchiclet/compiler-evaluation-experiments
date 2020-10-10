#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern unsigned int k;
extern unsigned int size;
extern unsigned int  count[256] ;
extern unsigned char * restrict L;

void loop()
{
#pragma scop

    for(k = 0; k < size; k++)
    {
        count[L[k]]++;
    }

#pragma endscop
}
