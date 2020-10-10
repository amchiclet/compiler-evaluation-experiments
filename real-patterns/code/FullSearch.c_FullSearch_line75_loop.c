#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int SearchLimit;
extern int j;
extern int xt;
extern int xc;
extern int yt;
extern int yc;
extern double * restrict block_ref;
typedef struct
{
    double *data;
    int x_length;
    int y_length;
} Image;
extern Image * restrict img_ref;
extern int ii;
extern int BlockSize;
extern int jj;
extern Image * restrict block;
extern double SADmin;
extern int x_min;
extern int y_min;
extern double MVx_int;
extern double MVy_int;

void loop()
{
#pragma scop

    for(i = -SearchLimit; i < SearchLimit; i++)
    {
        for(j = -SearchLimit; j < SearchLimit; j++)
        {
            xt = xc + j;
            yt = yc + i;
            block_ref = img_ref -> data + yt * img_ref -> x_length + xt;
            double SAD = 0;
            for(ii = 0; ii < BlockSize; ii++)
            {
                for(jj = 0; jj < BlockSize; jj++)
                {
                    SAD +=(abs((block -> data[ii * block -> x_length + jj] - block_ref[ii * img_ref -> x_length + jj])));
                }
            }
            SAD = SAD /(BlockSize * BlockSize);
            if(SAD < SADmin)
            {
                SADmin = SAD;
                x_min = xt;
                y_min = yt;
            }
            MVx_int =(x_min - xc);
            MVy_int =(y_min - yc);
        }
    }

#pragma endscop
}
