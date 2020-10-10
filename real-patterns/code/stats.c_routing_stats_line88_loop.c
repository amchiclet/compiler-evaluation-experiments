#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nx;
extern int max_occ;
extern int ** restrict chanx_occ;
extern int j;
extern float av_occ;

void loop()
{
#pragma scop

    for(i = 1; i <= nx; i++)
    {
        max_occ =(chanx_occ[i][j] > max_occ?chanx_occ[i][j] : max_occ);
        av_occ += chanx_occ[i][j];
    }

#pragma endscop
}
