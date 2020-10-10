#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int height;
extern int j;
extern int width;
extern unsigned char ** restrict cimage;
extern char * restrict superbuffer;

void loop()
{
#pragma scop

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            cimage[i][j] = superbuffer[i * width + j];
        }
    }

#pragma endscop
}
