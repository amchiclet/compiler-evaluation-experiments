#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int count;
extern short last_val;
extern short * restrict src;
extern double * restrict dest;
extern double normfact;

void loop()
{
#pragma scop

    for(k = 0; k < count; k++)
    {
        last_val += src[k];
        dest[k] = last_val * normfact;
    }

#pragma endscop
}
