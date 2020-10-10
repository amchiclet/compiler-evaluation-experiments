#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int dims20;
extern int ii;
extern int  xstart[3] ;
extern int ii2;
extern int j;
extern int dims21;
extern int jj;
extern int  ystart[3] ;
extern int ij2;
extern int k;
extern int dims22;
extern int kk;
extern int  zstart[3] ;
extern int  indexmap[128][256][256] ;

void loop()
{
#pragma scop

    for(i = 0; i < dims20; i++)
    {
        ii =(i + 1 + xstart[2] - 2 + 256 / 2) % 256 - 256 / 2;
        ii2 = ii * ii;
        for(j = 0; j < dims21; j++)
        {
            jj =(j + 1 + ystart[2] - 2 + 256 / 2) % 256 - 256 / 2;
            ij2 = jj * jj + ii2;
            for(k = 0; k < dims22; k++)
            {
                kk =(k + 1 + zstart[2] - 2 + 128 / 2) % 128 - 128 / 2;
                indexmap[k][j][i] = kk * kk + ij2;
            }
        }
    }

#pragma endscop
}
