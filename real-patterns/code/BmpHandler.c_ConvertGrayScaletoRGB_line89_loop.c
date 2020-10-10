#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int y;
extern int j;
extern int x;
extern int k;
extern double *** restrict grayscale;
extern double max;
extern double min;

void loop()
{
#pragma scop

    for(i = 0; i < y; i++) for(j = 0; j < x; j++) for(k = 0; k < 4 * 4; k++)
            {
                if(grayscale[i + 1][j][k] > max) max = grayscale[i + 1][j][k];
                if(grayscale[i + 1][j][k] < min) min = grayscale[i + 1][j][k];
            }

#pragma endscop
}
