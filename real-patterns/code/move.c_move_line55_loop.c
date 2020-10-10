#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int iside;
extern int jface;
extern int  jjface[6] ;
extern int cb;
extern int  cbc[2400][6] ;
extern int i;
extern double  xc_new[2400][8] ;
extern int iel;
extern double  xc[2400][8] ;
extern double  yc_new[2400][8] ;
extern double  yc[2400][8] ;
extern double  zc_new[2400][8] ;
extern double  zc[2400][8] ;
extern int  cbc_new[2400][6] ;
extern int ntemp;
extern int  sje[2400][6][2][2] ;
extern int  ijel_new[2400][6][2] ;
extern int  sje_new[2400][6][2][2] ;
extern int  id_to_mt[2400] ;
extern int  ijel[2400][6][2] ;
extern int ii2;
extern int ii1;

void loop()
{
#pragma scop

    for(iside = 0; iside < 6; iside++)
    {
        jface = jjface[iside];
        cb = cbc[i][iside];
        xc_new[iel][iside] = xc[i][iside];
        yc_new[iel][iside] = yc[i][iside];
        zc_new[iel][iside] = zc[i][iside];
        cbc_new[iel][iside] = cb;
        if(cb == 2)
        {
            ntemp = sje[i][iside][0][0];
            ijel_new[iel][iside][0] = 0;
            ijel_new[iel][iside][1] = 0;
            sje_new[iel][iside][0][0] = id_to_mt[ntemp];
        }
        else if(cb == 1)
        {
            ntemp = sje[i][iside][0][0];
            ijel_new[iel][iside][0] = ijel[i][iside][0];
            ijel_new[iel][iside][1] = ijel[i][iside][1];
            sje_new[iel][iside][0][0] = id_to_mt[ntemp];
        }
        else if(cb == 3)
        {
            for(ii2 = 0; ii2 < 2; ii2++)
            {
                for(ii1 = 0; ii1 < 2; ii1++)
                {
                    ntemp = sje[i][iside][ii2][ii1];
                    ijel_new[iel][iside][0] = 0;
                    ijel_new[iel][iside][1] = 0;
                    sje_new[iel][iside][ii2][ii1] = id_to_mt[ntemp];
                }
            }
        }
        else if(cb == 0)
        {
            sje_new[iel][iside][0][0] = - 1;
            sje_new[iel][iside][1][0] = - 1;
            sje_new[iel][iside][0][1] = - 1;
            sje_new[iel][iside][1][1] = - 1;
        }
    }

#pragma endscop
}
