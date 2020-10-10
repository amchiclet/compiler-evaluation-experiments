#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern long length;
extern double * restrict a;
extern double * restrict b;
extern double * restrict c;

void loop()
{
#pragma scop

    for(j = 0; j < length; j++)
    {
        a[j] = 0.0;
        b[j] = 2.0;
        c[j] = 2.0;
    }

#pragma endscop
}
