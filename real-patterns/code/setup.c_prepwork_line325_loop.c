#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int iel;
extern int nelt;
extern int iface;
extern int cb;
extern int  cbc[2400][6] ;
extern int j;
extern int i;
extern double  tmmor[92700] ;
extern int  idmo[2400][6][2][2][5][5] ;

void loop()
{
#pragma scop

    for(iel = 0; iel < nelt; iel++)
    {
        for(iface = 0; iface < 6; iface++)
        {
            cb = cbc[iel][iface];
            if(cb == 0)
            {
                for(j = 1; j < 5 - 1; j++)
                {
                    for(i = 1; i < 5 - 1; i++)
                    {
                        tmmor[idmo[iel][iface][0][0][j][i]] = 0.0;
                    }
                }
                j = 0;
                for(i = 0; i < 5 - 1; i++)
                {
                    tmmor[idmo[iel][iface][0][0][j][i]] = 0.0;
                }
                if(idmo[iel][iface][0][0][0][5 - 1] == - 1)
                {
                    tmmor[idmo[iel][iface][1][0][0][5 - 1]] = 0.0;
                }
                else
                {
                    tmmor[idmo[iel][iface][0][0][0][5 - 1]] = 0.0;
                    for(i = 0; i < 5; i++)
                    {
                        tmmor[idmo[iel][iface][1][0][j][i]] = 0.0;
                    }
                }
                i = 5 - 1;
                if(idmo[iel][iface][1][0][1][5 - 1] == - 1)
                {
                    for(j = 1; j < 5 - 1; j++)
                    {
                        tmmor[idmo[iel][iface][0][0][j][i]] = 0.0;
                    }
                    tmmor[idmo[iel][iface][1][1][5 - 1][5 - 1]] = 0.0;
                }
                else
                {
                    for(j = 1; j < 5; j++)
                    {
                        tmmor[idmo[iel][iface][1][0][j][i]] = 0.0;
                    }
                    for(j = 0; j < 5; j++)
                    {
                        tmmor[idmo[iel][iface][1][1][j][i]] = 0.0;
                    }
                }
                j = 5 - 1;
                tmmor[idmo[iel][iface][0][1][5 - 1][0]] = 0.0;
                if(idmo[iel][iface][0][1][5 - 1][1] == - 1)
                {
                    for(i = 1; i < 5 - 1; i++)
                    {
                        tmmor[idmo[iel][iface][0][0][j][i]] = 0.0;
                    }
                }
                else
                {
                    for(i = 1; i < 5; i++)
                    {
                        tmmor[idmo[iel][iface][0][1][j][i]] = 0.0;
                    }
                    for(i = 0; i < 5 - 1; i++)
                    {
                        tmmor[idmo[iel][iface][1][1][j][i]] = 0.0;
                    }
                }
                i = 0;
                for(j = 1; j < 5 - 1; j++)
                {
                    tmmor[idmo[iel][iface][0][0][j][i]] = 0.0;
                }
                if(idmo[iel][iface][0][0][5 - 1][0] != - 1)
                {
                    tmmor[idmo[iel][iface][0][0][5 - 1][i]] = 0.0;
                    for(j = 0; j < 5 - 1; j++)
                    {
                        tmmor[idmo[iel][iface][0][1][j][i]] = 0.0;
                    }
                }
            }
        }
    }

#pragma endscop
}
