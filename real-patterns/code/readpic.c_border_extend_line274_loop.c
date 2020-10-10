#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int h1;
extern int h2;
extern unsigned char * restrict fp;
extern unsigned char * restrict frame;
extern int w2;
extern int i;

void loop()
{
#pragma scop

    for(j = h1; j < h2; j++)
    {
        fp = frame + j * w2;
        for(i = 0; i < w2; i++) fp[i] = fp[i - w2];
    }

#pragma endscop
}
