#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int h;
extern int i;
extern int v;
extern unsigned char * restrict p1;
extern unsigned char * restrict p1a;
extern unsigned char * restrict p2;
extern int s;
extern int lx;

void loop()
{
#pragma scop

    for(j = 0; j < h; j++)
    {
        for(i = 0; i < 16; i++)
        {
            v =((((unsigned int )(p1[i] + p1a[i] + 1)) >> 1) - p2[i]);
            s += v * v;
        }
        p1 = p1a;
        p1a += lx;
        p2 += lx;
    }

#pragma endscop
}
