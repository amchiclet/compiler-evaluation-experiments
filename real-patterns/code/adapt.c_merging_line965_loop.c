#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int jface;
extern int  jjface[6] ;
extern int ielold;
extern int  iela[8] ;
extern int  children[6][4] ;
extern int ii;
extern int  ntempa[4] ;
extern int cb;
extern int  cbc[2400][6] ;
enum false_enum {false=0,true=1};;
typedef enum false_enum logical;
extern logical  ifcoa_id[2400] ;
extern int  sje[2400][6][2][2] ;
extern int ntemp;
extern int ielnew;
extern int  ijel[2400][6][2] ;
extern int  ntema[4] ;
extern int  iijj[4][2] ;

void loop()
{
#pragma scop

    for(i = 0; i < 6; i++)
    {
        jface = jjface[i];
        ielold = iela[children[i][0]];
        for(ii = 0; ii < 4; ii++)
        {
            ntempa[ii] = iela[children[i][ii]];
        }
        cb = cbc[ielold][i];
        if(cb == 2)
        {
            if(ifcoa_id[sje[ielold][i][0][0]])
            {
                if(i == 1 || i == 3 || i == 5)
                {
                    ntemp = sje[sje[ntempa[0]][i][0][0]][i][0][0];
                }
                else
                {
                    ntemp = sje[ntempa[0]][i][0][0];
                }
                sje[ielnew][i][0][0] = ntemp;
                ijel[ielnew][i][0] = 0;
                ijel[ielnew][i][1] = 0;
                cbc[ielnew][i] = 2;
            }
            else
            {
                for(ii = 0; ii < 4; ii++)
                {
                    ntema[ii] = sje[ntempa[ii]][i][0][0];
                    cbc[ntema[ii]][jface] = 1;
                    sje[ntema[ii]][jface][0][0] = ielnew;
                    ijel[ntema[ii]][jface][0] = iijj[ii][0];
                    ijel[ntema[ii]][jface][1] = iijj[ii][1];
                    sje[ielnew][i][iijj[ii][1]][iijj[ii][0]] = ntema[ii];
                    ijel[ielnew][i][0] = 0;
                    ijel[ielnew][i][1] = 0;
                }
                cbc[ielnew][i] = 3;
            }
        }
        else if(cb == 1)
        {
            ntemp = sje[ielold][i][0][0];
            cbc[ntemp][jface] = 2;
            ijel[ntemp][jface][0] = 0;
            ijel[ntemp][jface][1] = 0;
            sje[ntemp][jface][0][0] = ielnew;
            sje[ntemp][jface][1][0] = - 1;
            sje[ntemp][jface][0][1] = - 1;
            sje[ntemp][jface][1][1] = - 1;
            cbc[ielnew][i] = 2;
            ijel[ielnew][i][0] = 0;
            ijel[ielnew][i][1] = 0;
            sje[ielnew][i][0][0] = ntemp;
        }
        else if(cb == 0)
        {
            cbc[ielnew][i] = 0;
            sje[ielnew][i][0][0] = - 1;
            sje[ielnew][i][1][0] = - 1;
            sje[ielnew][i][0][1] = - 1;
            sje[ielnew][i][1][1] = - 1;
        }
    }

#pragma endscop
}
