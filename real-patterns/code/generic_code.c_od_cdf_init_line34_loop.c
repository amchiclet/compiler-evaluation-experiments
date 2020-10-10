#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ncdfs;
extern int j;
extern int nsyms;
typedef unsigned short uint16_t;
extern uint16_t * restrict cdf;
extern int val;
extern int first;

void loop()
{
#pragma scop

    for(i = 0; i < ncdfs; i++)
    {
        for(j = 0; j < nsyms; j++)
        {
            cdf[i * nsyms + j] =(val * j + first);
        }
    }

#pragma endscop
}
