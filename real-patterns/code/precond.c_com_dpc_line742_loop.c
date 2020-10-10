#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int nn2;
extern int nn2start;
extern int nn2end;
extern int nn1;
extern int nn1start;
extern int nn1end;
extern int j;
extern int jstart;
extern int jend;
extern int i;
extern int istart;
extern int iend;
extern int imor;
extern int  idmo[2400][6][2][2][5][5] ;
extern int iel;
extern int iside;
extern double temp;
extern double anc1;
extern double  pcmor_nc1[6][2][2][5][5] ;
extern int isize;
extern double ac;
extern double  pcmor_c[6][5][5] ;
extern double anc0;
extern double  pcmor_nc0[6][2][2][5][5] ;
extern double anc2;
extern double  pcmor_nc2[6][2][2][5][5] ;
extern double  dpcmor[92700] ;

void loop()
{
#pragma scop

    for(nn2 = nn2start - 1; nn2 < nn2end; nn2++)
    {
        for(nn1 = nn1start - 1; nn1 < nn1end; nn1++)
        {
            for(j = jstart - 1; j < jend; j++)
            {
                for(i = istart - 1; i < iend; i++)
                {
                    imor = idmo[iel][iside][nn2][nn1][j][i];
                    temp = anc1 * pcmor_nc1[isize][nn2][nn1][j][i] + ac * pcmor_c[isize + 1][j][i] + anc0 * pcmor_nc0[isize][nn2][nn1][j][i] + anc2 * pcmor_nc2[isize][nn2][nn1][j][i];
                    dpcmor[imor] = 1.0 / temp;
                }
            }
        }
    }

#pragma endscop
}
