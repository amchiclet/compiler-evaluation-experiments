#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern unsigned int k;
extern unsigned int size;
extern unsigned char * restrict debw;
extern unsigned char * restrict L;
extern unsigned int * restrict T;
extern unsigned int orgpos;

void loop()
{
#pragma scop

    for(k = 1; k < size; k++)
    {
        debw[size - k - 1] = L[T[orgpos]];
        orgpos = T[orgpos];
    }

#pragma endscop
}
