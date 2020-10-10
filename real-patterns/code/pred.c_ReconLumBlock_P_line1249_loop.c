#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n;
extern int bs;
extern int m;
extern int * restrict data;
extern unsigned char * restrict prev;
extern int x1;
extern int y1;
extern int lx;

void loop()
{
#pragma scop

    for(n = 0; n < bs; n++)
    {
        for(m = 0; m < bs; m++)
        {
            *(data + m + n * 16) +=((int )( *(prev + x1 + 2 * m +(y1 + 2 * n) * 2 * lx)));
        }
    }

#pragma endscop
}
