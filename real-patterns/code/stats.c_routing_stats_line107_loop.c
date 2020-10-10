#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int ny;
extern int max_occ;
extern int ** restrict chany_occ;
extern int i;
extern float av_occ;

void loop()
{
#pragma scop

    for(j = 1; j <= ny; j++)
    {
        max_occ =(chany_occ[i][j] > max_occ?chany_occ[i][j] : max_occ);
        av_occ += chany_occ[i][j];
    }

#pragma endscop
}
