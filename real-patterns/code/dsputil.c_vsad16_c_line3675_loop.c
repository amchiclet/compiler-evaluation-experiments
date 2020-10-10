#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int y;
extern int h;
extern int x;
extern int score;
typedef unsigned char uint8_t;
extern uint8_t * restrict s1;
extern uint8_t * restrict s2;
extern int stride;

void loop()
{
#pragma scop

    for(y = 1; y < h; y++)
    {
        for(x = 0; x < 16; x++)
        {
            score +=(s1[x] - s2[x] - s1[x + stride] + s2[x + stride] >= 0?s1[x] - s2[x] - s1[x + stride] + s2[x + stride] : -(s1[x] - s2[x] - s1[x + stride] + s2[x + stride]));
        }
        s1 += stride;
        s2 += stride;
    }

#pragma endscop
}
