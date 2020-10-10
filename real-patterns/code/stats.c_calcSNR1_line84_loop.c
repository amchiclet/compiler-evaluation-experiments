#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int h;
extern int i;
extern int w;
extern double v1;
extern unsigned char * restrict org;
extern double s1;
extern double s2;
extern unsigned char * restrict rec;
extern double e2;
extern int lx;

void loop()
{
#pragma scop

    for(j = 0; j < h; j++)
    {
        for(i = 0; i < w; i++)
        {
            v1 = org[i];
            s1 += v1;
            s2 += v1 * v1;
            v1 -= rec[i];
            e2 += v1 * v1;
        }
        org += lx;
        rec += lx;
    }

#pragma endscop
}
