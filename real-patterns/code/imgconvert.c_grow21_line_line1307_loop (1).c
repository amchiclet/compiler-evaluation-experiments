#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int w;
extern int width;
typedef unsigned char uint8_t;
extern uint8_t * restrict d;
extern uint8_t * restrict s1;

void loop()
{
#pragma scop

    for(w = width; w >= 4; w -= 4)
    {
        d[1] = d[0] = s1[0];
        d[3] = d[2] = s1[1];
        s1 += 2;
        d += 4;
    }

#pragma endscop
}
