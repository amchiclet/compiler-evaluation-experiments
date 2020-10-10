#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int count;
extern short diff;
extern int * restrict src;
extern short last_val;
extern short * restrict dest;

void loop()
{
#pragma scop

    for(k = 0; k < count; k++)
    {
        diff =((src[k] >> 16) - last_val);
        dest[k] = diff;
        last_val =(src[k] >> 16);
    }

#pragma endscop
}
