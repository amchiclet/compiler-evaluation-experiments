#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int h;
extern int i;
extern int w;
extern int v;
extern unsigned char * restrict d;
extern unsigned char * restrict s;
extern int lx2;

void loop()
{
#pragma scop

    for(j = 0; j < h; j++)
    {
        for(i = 0; i < w; i++)
        {
            v =(d[i] +(((unsigned int )(s[i] + s[i + 1] + 1)) >> 1));
            d[i] =(v +((v >= 0?1 : 0)) >> 1);
        }
        s += lx2;
        d += lx2;
    }

#pragma endscop
}
