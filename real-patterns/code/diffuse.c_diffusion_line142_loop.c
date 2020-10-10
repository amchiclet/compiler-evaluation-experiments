#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ie;
extern int nelt;
extern int k;
extern int j;
extern int i;
extern double cona;
extern double  pdiff[2400][5][5][5] ;
extern double  pdiffp[2400][5][5][5] ;
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
                    cona = cona + pdiff[ie][k][j][i] * pdiffp[ie][k][j][i] * tmult[ie][k][j][i];
                }
            }
        }
    }

#pragma endscop
}
