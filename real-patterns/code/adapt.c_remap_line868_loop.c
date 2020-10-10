#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int kk;
extern int jj;
extern int ii;
extern double  yone[2][5][5][5] ;
extern double  ixmc1[5][5] ;
extern double  x[5][5][5] ;
extern double  ixmc2[5][5] ;
extern double  ytwo[4][5][5][5] ;
extern double  ixtmc1[5][5] ;
extern double  ixtmc2[5][5] ;

void loop()
{
#pragma scop

    for(i = 0; i < 5; i++)
    {
        for(kk = 0; kk < 5; kk++)
        {
            for(jj = 0; jj < 5; jj++)
            {
                for(ii = 0; ii < 5; ii++)
                {
                    yone[0][i][jj][ii] = yone[0][i][jj][ii] + ixmc1[kk][ii] * x[i][jj][kk];
                    yone[1][i][jj][ii] = yone[1][i][jj][ii] + ixmc2[kk][ii] * x[i][jj][kk];
                }
            }
        }
        for(kk = 0; kk < 5; kk++)
        {
            for(jj = 0; jj < 5; jj++)
            {
                for(ii = 0; ii < 5; ii++)
                {
                    ytwo[0][jj][i][ii] = ytwo[0][jj][i][ii] + yone[0][i][kk][ii] * ixtmc1[jj][kk];
                    ytwo[1][jj][i][ii] = ytwo[1][jj][i][ii] + yone[0][i][kk][ii] * ixtmc2[jj][kk];
                    ytwo[2][jj][i][ii] = ytwo[2][jj][i][ii] + yone[1][i][kk][ii] * ixtmc1[jj][kk];
                    ytwo[3][jj][i][ii] = ytwo[3][jj][i][ii] + yone[1][i][kk][ii] * ixtmc2[jj][kk];
                }
            }
        }
    }

#pragma endscop
}
