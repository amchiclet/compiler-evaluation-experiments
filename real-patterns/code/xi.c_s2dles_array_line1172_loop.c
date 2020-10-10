#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int count;
extern short diff;
extern short * restrict src;
extern short last_val;
extern short * restrict dest;

void loop()
{
#pragma scop

    for(k = 0; k < count; k++)
    {
        diff =(src[k] - last_val);
        dest[k] = diff;
        last_val = src[k];
    }

#pragma endscop
}
