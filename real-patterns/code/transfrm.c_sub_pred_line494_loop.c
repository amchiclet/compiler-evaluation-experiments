#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int i;
extern short * restrict blk;
extern unsigned char * restrict cur;
extern unsigned char * restrict pred;
extern int lx;

void loop()
{
#pragma scop

    for(j = 0; j < 4; j++)
    {
        for(i = 0; i < 8; i++) blk[i] =(cur[i] - pred[i]);
        blk += 8;
        cur += lx;
        pred += lx;
        for(i = 0; i < 8; i++) blk[i] =(cur[i] - pred[i]);
        blk += 8;
        cur += lx;
        pred += lx;
    }

#pragma endscop
}
