#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int x;
extern int xbytes;
extern unsigned char * restrict fixbuf;
extern unsigned char * restrict bufpos;

void loop()
{
#pragma scop

    for(x = 0; x < xbytes; x += 3)
    {
        fixbuf[x] = bufpos[x + 2];
        fixbuf[x + 1] = bufpos[x + 1];
        fixbuf[x + 2] = bufpos[x];
    }

#pragma endscop
}
