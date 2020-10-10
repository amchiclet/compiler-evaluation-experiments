#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int count;
extern signed char last_val;
extern signed char * restrict src;
extern float * restrict dest;
extern float normfact;

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
