#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int h;
extern unsigned char * restrict d;
extern unsigned char * restrict s;
extern int lx2;
extern int lx;

void loop()
{
#pragma scop

    for(j = 0; j < h; j++)
    {
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        d[4] = s[4];
        d[5] = s[5];
        d[6] = s[6];
        d[7] = s[7];
        d[8] = s[8];
        d[9] = s[9];
        d[10] = s[10];
        d[11] = s[11];
        d[12] = s[12];
        d[13] = s[13];
        d[14] = s[14];
        d[15] = s[15];
        s += lx2;
        d += lx;
    }

#pragma endscop
}
