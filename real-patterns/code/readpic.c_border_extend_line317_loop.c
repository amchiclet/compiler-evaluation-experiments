#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int h1;
extern unsigned char * restrict fp;
extern unsigned char * restrict frame;
extern int w2;
extern int i;
extern int w1;

void loop()
{
#pragma scop

    for(j = 0; j < h1; j++)
    {
        fp = frame + j * w2;
        for(i = w1; i < w2; i++) fp[i] = fp[i - 1];
    }

#pragma endscop
}
