#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int iz;
extern int kk;
extern int jj;
extern int ii;
extern double  y[5][5][5] ;
extern double  ytwo[4][5][5][5] ;
extern double  ixtmc1[5][5] ;
extern double  y1[7][5][5][5] ;
extern double  ixtmc2[5][5] ;

void loop()
{
#pragma scop

    for(iz = 0; iz < 5; iz++)
    {
        for(kk = 0; kk < 5; kk++)
        {
            for(jj = 0; jj < 5; jj++)
            {
                for(ii = 0; ii < 5; ii++)
                {
                    y[jj][iz][ii] = y[jj][iz][ii] + ytwo[0][iz][kk][ii] * ixtmc1[jj][kk];
                    y1[0][jj][iz][ii] = y1[0][jj][iz][ii] + ytwo[2][iz][kk][ii] * ixtmc1[jj][kk];
                    y1[1][jj][iz][ii] = y1[1][jj][iz][ii] + ytwo[1][iz][kk][ii] * ixtmc1[jj][kk];
                    y1[2][jj][iz][ii] = y1[2][jj][iz][ii] + ytwo[3][iz][kk][ii] * ixtmc1[jj][kk];
                    y1[3][jj][iz][ii] = y1[3][jj][iz][ii] + ytwo[0][iz][kk][ii] * ixtmc2[jj][kk];
                    y1[4][jj][iz][ii] = y1[4][jj][iz][ii] + ytwo[2][iz][kk][ii] * ixtmc2[jj][kk];
                    y1[5][jj][iz][ii] = y1[5][jj][iz][ii] + ytwo[1][iz][kk][ii] * ixtmc2[jj][kk];
                    y1[6][jj][iz][ii] = y1[6][jj][iz][ii] + ytwo[3][iz][kk][ii] * ixtmc2[jj][kk];
                }
            }
        }
    }

#pragma endscop
}
