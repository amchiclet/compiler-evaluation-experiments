#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int i;
extern unsigned char * restrict cur;
extern unsigned char * restrict clp;
extern short * restrict blk;
extern unsigned char * restrict pred;
extern int lx;

void loop()
{
#pragma scop

    for(j = 0; j < 8; j++)
    {
        for(i = 0; i < 8; i++) cur[i] = clp[blk[i] + pred[i]];
        blk += 8;
        cur += lx;
        pred += lx;
    }

#pragma endscop
}
