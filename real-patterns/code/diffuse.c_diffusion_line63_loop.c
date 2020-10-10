#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ie;
extern int nelt;
extern int k;
extern int j;
extern int i;
extern double  pdiff[2400][5][5][5] ;
extern double  dpcelm[2400][5][5][5] ;
extern double  trhs[2400][5][5][5] ;
extern double rho1;
extern double  tmult[2400][5][5][5] ;

void loop()
{
#pragma scop

    for(ie = 0; ie < nelt; ie++)
    {
        for(k = 0; k < 5; k++)
        {
            for(j = 0; j < 5; j++)
            {
                for(i = 0; i < 5; i++)
                {
                    pdiff[ie][k][j][i] = dpcelm[ie][k][j][i] * trhs[ie][k][j][i];
                    rho1 = rho1 + trhs[ie][k][j][i] * pdiff[ie][k][j][i] * tmult[ie][k][j][i];
                }
            }
        }
    }

#pragma endscop
}
