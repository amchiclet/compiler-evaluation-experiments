#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int iel;
extern int nelt;
extern int  newc[2400] ;
extern int  newe[2400] ;
extern int  newi[2400] ;
extern int cb1;
extern int  cbc[2400][6] ;
extern int cb2;
extern int cb3;
extern int cb4;
extern int cb5;
extern int cb6;
enum false_enum {false=0,true=1};
typedef enum false_enum logical;
extern logical  eassign[2400][12] ;
extern int ntemp;
extern int  sje[2400][6][2][2] ;
extern int  diagn[2400][12][2] ;
extern int  ijel[2400][6][2] ;
extern logical  ncon_edge[2400][12] ;
extern logical  if_1_edge[2400][12] ;
extern logical  fassign[2400][6] ;

void loop()
{
#pragma scop

    for(iel = 0; iel < nelt; iel++)
    {
        newc[iel] = 0;
        newe[iel] = 0;
        newi[iel] = 0;
        cb1 = cbc[iel][0];
        cb2 = cbc[iel][1];
        cb3 = cbc[iel][2];
        cb4 = cbc[iel][3];
        cb5 = cbc[iel][4];
        cb6 = cbc[iel][5];
        if(cb6 == 0)
        {
            if(cb4 == 0 || cb4 == 1)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][10] = true;
            }
            if(cb1 != 3)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][0] = true;
            }
            if(cb3 != 3)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][8] = true;
            }
            if(cb2 == 0 || cb2 == 1)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][4] = true;
            }
        }
        else if(cb6 == 1)
        {
            if(cb4 == 0)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][10] = true;
            }
            else if(cb4 == 1)
            {
                ntemp = sje[iel][3][0][0];
                if(cbc[ntemp][5] != 3 || sje[ntemp][5][0][0] > iel)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][10] = true;
                    if(cbc[ntemp][5] == 2)
                    {
                        diagn[iel][10][0] = sje[ntemp][5][0][0];
                        diagn[iel][10][1] = ijel[iel][5][1];
                        ncon_edge[sje[ntemp][5][0][0]][9] = true;
                        if_1_edge[iel][10] = true;
                    }
                    if(cbc[ntemp][5] == 3 && sje[ntemp][5][0][0] > iel)
                    {
                        diagn[iel][10][0] = sje[ntemp][5][ijel[iel][5][1]][1];
                    }
                }
            }
            if(cb1 == 0)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][0] = true;
            }
            else if(cb1 == 1)
            {
                ntemp = sje[iel][0][0][0];
                if(cbc[ntemp][5] != 3 || sje[ntemp][5][0][0] > iel)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][0] = true;
                    if(cbc[ntemp][5] == 2)
                    {
                        diagn[iel][0][0] = sje[ntemp][5][0][0];
                        diagn[iel][0][1] = ijel[iel][5][0];
                        ncon_edge[sje[ntemp][5][0][0]][6] = true;
                        if_1_edge[iel][0] = true;
                    }
                    if(cbc[ntemp][5] == 3 && sje[ntemp][5][0][0] > iel)
                    {
                        diagn[iel][0][0] = sje[ntemp][5][0][ijel[iel][5][0]];
                    }
                }
            }
            else if(cb1 == 2)
            {
                if(ijel[iel][5][1] == 1)
                {
                    ntemp = sje[iel][0][0][0];
                    if(cbc[ntemp][5] == 1)
                    {
                        newe[iel] = newe[iel] + 1;
                        eassign[iel][0] = true;
                    }
                    else
                    {
                        if(sje[ntemp][5][0][0] > iel)
                        {
                            newe[iel] = newe[iel] + 1;
                            eassign[iel][0] = true;
                            diagn[iel][0][0] = sje[ntemp][5][0][0];
                        }
                    }
                }
                else
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][0] = true;
                }
            }
            if(cb3 == 0)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][8] = true;
            }
            else if(cb3 == 1)
            {
                ntemp = sje[iel][2][0][0];
                if(cbc[ntemp][5] != 3 || sje[ntemp][5][0][0] > iel)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][8] = true;
                    if(cbc[ntemp][5] == 2)
                    {
                        diagn[iel][8][0] = sje[ntemp][5][0][0];
                        diagn[iel][8][1] = ijel[iel][5][1];
                        ncon_edge[sje[ntemp][5][0][0]][11] = true;
                        if_1_edge[iel][8] = true;
                    }
                    if(cbc[ntemp][5] == 3 && sje[ntemp][5][0][0] > iel)
                    {
                        diagn[iel][8][0] = sje[ntemp][5][ijel[iel][5][1]][1];
                    }
                }
            }
            else if(cb3 == 2)
            {
                if(ijel[iel][5][0] == 1)
                {
                    ntemp = sje[iel][2][0][0];
                    if(cbc[ntemp][5] == 1)
                    {
                        newe[iel] = newe[iel] + 1;
                        eassign[iel][8] = true;
                    }
                    else
                    {
                        if(sje[ntemp][5][0][0] > iel)
                        {
                            newe[iel] = newe[iel] + 1;
                            eassign[iel][8] = true;
                            diagn[iel][8][0] = sje[ntemp][5][0][0];
                        }
                    }
                }
                else
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][8] = true;
                }
            }
            if(cb2 == 0)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][4] = true;
            }
            else if(cb2 == 1)
            {
                ntemp = sje[iel][1][0][0];
                if(cbc[ntemp][5] != 3 || sje[ntemp][5][0][0] > iel)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][4] = true;
                    if(cbc[ntemp][5] == 2)
                    {
                        diagn[iel][4][0] = sje[ntemp][5][0][0];
                        diagn[iel][4][1] = ijel[iel][5][0];
                        ncon_edge[sje[ntemp][5][0][0]][2] = true;
                        if_1_edge[iel][4] = true;
                    }
                    if(cbc[ntemp][5] == 3 && sje[ntemp][5][0][0] > iel)
                    {
                        diagn[iel][8][0] = sje[ntemp][5][ijel[iel][5][1]][1];
                    }
                }
            }
        }
        if(cb4 == 0)
        {
            if(cb1 != 3)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][3] = true;
            }
            if(cb5 != 3)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][11] = true;
            }
            if(cb2 == 0 || cb2 == 1)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][7] = true;
            }
        }
        else if(cb4 == 1)
        {
            if(cb1 == 2)
            {
                if(ijel[iel][3][1] == 0)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][3] = true;
                }
                else
                {
                    ntemp = sje[iel][3][0][0];
                    if(cbc[ntemp][0] != 3 || sje[ntemp][0][0][0] > iel)
                    {
                        newe[iel] = newe[iel] + 1;
                        eassign[iel][3] = true;
                        if(cbc[ntemp][0] == 3 && sje[ntemp][0][0][0] > iel)
                        {
                            diagn[iel][3][0] = sje[ntemp][0][1][ijel[iel][3][0]];
                        }
                    }
                }
            }
            else if(cb1 == 0)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][3] = true;
            }
            else if(cb1 == 1)
            {
                ntemp = sje[iel][3][0][0];
                if(cbc[ntemp][0] != 3 || sje[ntemp][0][0][0] > iel)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][3] = true;
                    if(cbc[ntemp][0] == 2)
                    {
                        diagn[iel][3][0] = sje[ntemp][0][0][0];
                        diagn[iel][3][1] = ijel[iel][3][0];
                        ncon_edge[sje[ntemp][0][0][0]][5] = true;
                        if_1_edge[iel][3] = true;
                    }
                    if(cbc[ntemp][0] == 3 && sje[ntemp][0][0][0] > iel)
                    {
                        diagn[iel][3][0] = sje[ntemp][0][1][ijel[iel][3][0]];
                    }
                }
            }
            if(cb5 == 2)
            {
                if(ijel[iel][3][0] == 0)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][11] = true;
                }
                else
                {
                    ntemp = sje[iel][3][0][0];
                    if(cbc[ntemp][4] != 3 || sje[ntemp][4][0][0] > iel)
                    {
                        newe[iel] = newe[iel] + 1;
                        eassign[iel][11] = true;
                        if(cbc[ntemp][4] == 3 && sje[ntemp][4][0][0] > iel)
                        {
                            diagn[iel][11][0] = sje[ntemp][4][ijel[iel][3][1]][1];
                        }
                    }
                }
            }
            else if(cb5 == 0)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][11] = true;
            }
            else if(cb5 == 1)
            {
                ntemp = sje[iel][3][0][0];
                if(cbc[ntemp][4] != 3 || sje[ntemp][4][0][0] > iel)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][11] = true;
                    if(cbc[ntemp][4] == 2)
                    {
                        diagn[iel][11][0] = sje[ntemp][4][0][0];
                        diagn[iel][11][1] = ijel[iel][3][1];
                        ncon_edge[sje[ntemp][4][0][0]][8] = true;
                        if_1_edge[iel][11] = true;
                    }
                    if(cbc[ntemp][4] == 3 && sje[ntemp][4][0][0] > iel)
                    {
                        diagn[iel][11][0] = sje[ntemp][4][ijel[iel][3][1]][1];
                    }
                }
            }
            if(cb2 == 0)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][7] = true;
            }
            else if(cb2 == 1)
            {
                ntemp = sje[iel][3][0][0];
                if(cbc[ntemp][1] != 3 || sje[ntemp][1][0][0] > iel)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][7] = true;
                    if(cbc[ntemp][1] == 2)
                    {
                        diagn[iel][7][0] = sje[ntemp][1][0][0];
                        diagn[iel][7][1] = ijel[iel][3][0];
                        ncon_edge[sje[ntemp][1][0][0]][1] = true;
                        if_1_edge[iel][7] = true;
                    }
                    if(cbc[ntemp][1] == 3 && sje[ntemp][1][0][0] > iel)
                    {
                        diagn[iel][7][0] = sje[ntemp][2][1][ijel[iel][3][0]];
                    }
                }
            }
        }
        if(cb2 == 0)
        {
            if(cb3 != 3)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][5] = true;
            }
            if(cb5 != 3)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][6] = true;
            }
        }
        else if(cb2 == 1)
        {
            if(cb3 == 2)
            {
                if(ijel[iel][1][1] == 0)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][5] = true;
                }
                else
                {
                    ntemp = sje[iel][1][0][0];
                    if(cbc[ntemp][2] != 3 || sje[ntemp][2][0][0] > iel)
                    {
                        newe[iel] = newe[iel] + 1;
                        eassign[iel][5] = true;
                        if(cbc[ntemp][2] == 3 && sje[ntemp][2][0][0] > iel)
                        {
                            diagn[iel][5][0] = sje[ntemp][2][1][ijel[iel][1][0]];
                        }
                    }
                }
            }
            else if(cb3 == 0)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][5] = true;
            }
            else if(cb3 == 1)
            {
                ntemp = sje[iel][1][0][0];
                if(cbc[ntemp][2] != 3 || sje[ntemp][2][0][0] > iel)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][5] = true;
                    if(cbc[ntemp][2] == 2)
                    {
                        diagn[iel][5][0] = sje[ntemp][2][0][0];
                        diagn[iel][5][1] = ijel[iel][1][0];
                        ncon_edge[sje[ntemp][2][0][0]][3] = true;
                        if_1_edge[iel][5] = true;
                    }
                    if(cbc[ntemp][2] == 3 && sje[ntemp][2][0][0] > iel)
                    {
                        diagn[iel][5][0] = sje[ntemp][2][1][ijel[iel][3][0]];
                    }
                }
            }
            if(cb5 == 2)
            {
                if(ijel[iel][1][0] == 0)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][6] = true;
                }
                else
                {
                    ntemp = sje[iel][1][0][0];
                    if(cbc[ntemp][4] != 3 || sje[ntemp][4][0][0] > iel)
                    {
                        newe[iel] = newe[iel] + 1;
                        eassign[iel][6] = true;
                        if(cbc[ntemp][4] == 3 && sje[ntemp][4][0][0] > iel)
                        {
                            diagn[iel][6][0] = sje[ntemp][4][1][ijel[iel][1][1]];
                        }
                    }
                }
            }
            else if(cb5 == 0)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][6] = true;
            }
            else if(cb5 == 1)
            {
                ntemp = sje[iel][1][0][0];
                if(cbc[ntemp][4] != 3 || sje[ntemp][4][0][0] > iel)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][6] = true;
                    if(cbc[ntemp][4] == 2)
                    {
                        diagn[iel][6][0] = sje[ntemp][4][0][0];
                        diagn[iel][6][1] = ijel[iel][1][1];
                        ncon_edge[sje[ntemp][4][0][0]][0] = true;
                        if_1_edge[iel][6] = true;
                    }
                    if(cbc[ntemp][4] == 3 && sje[ntemp][4][0][0] > iel)
                    {
                        diagn[iel][6][0] = sje[ntemp][4][ijel[iel][3][1]][1];
                    }
                }
            }
        }
        if(cb1 == 1)
        {
            newe[iel] = newe[iel] + 2;
            eassign[iel][1] = true;
            if(cb3 == 1)
            {
                ntemp = sje[iel][0][0][0];
                if(cbc[ntemp][2] == 2)
                {
                    diagn[iel][1][0] = sje[ntemp][2][0][0];
                    diagn[iel][1][1] = ijel[iel][0][0];
                    ncon_edge[sje[ntemp][2][0][0]][7] = true;
                    if_1_edge[iel][1] = true;
                }
                else if(cbc[ntemp][2] == 3)
                {
                    diagn[iel][1][0] = sje[ntemp][2][0][ijel[iel][0][0]];
                }
            }
            else if(cb3 == 2)
            {
                ntemp = sje[iel][2][0][0];
                if(ijel[iel][0][1] == 1)
                {
                    if(cbc[ntemp][0] == 2)
                    {
                        diagn[iel][1][0] = sje[ntemp][0][0][0];
                    }
                }
            }
            eassign[iel][2] = true;
            if(cb5 == 1)
            {
                ntemp = sje[iel][0][0][0];
                if(cbc[ntemp][4] == 2)
                {
                    diagn[iel][2][0] = sje[ntemp][4][0][0];
                    diagn[iel][2][1] = ijel[iel][0][1];
                    ncon_edge[sje[ntemp][4][0][0]][4] = true;
                    if_1_edge[iel][2] = true;
                }
                else if(cbc[ntemp][4] == 3)
                {
                    diagn[iel][2][0] = sje[ntemp][4][0][ijel[iel][0][1]];
                }
            }
            else if(cb5 == 2)
            {
                ntemp = sje[iel][4][0][0];
                if(ijel[iel][0][0] == 1)
                {
                    if(cbc[ntemp][0] == 2)
                    {
                        diagn[iel][2][0] = sje[ntemp][0][0][0];
                    }
                }
            }
        }
        else if(cb1 == 2)
        {
            if(cb3 == 2)
            {
                ntemp = sje[iel][0][0][0];
                if(cbc[ntemp][2] != 3)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][1] = true;
                    if(cbc[ntemp][2] == 2)
                    {
                        diagn[iel][1][0] = sje[ntemp][2][0][0];
                    }
                }
            }
            else if(cb3 == 0 || cb3 == 1)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][1] = true;
                if(cb3 == 1)
                {
                    ntemp = sje[iel][0][0][0];
                    if(cbc[ntemp][2] == 2)
                    {
                        diagn[iel][1][0] = sje[ntemp][2][0][0];
                    }
                }
            }
            if(cb5 == 2)
            {
                ntemp = sje[iel][0][0][0];
                if(cbc[ntemp][4] != 3)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][2] = true;
                    if(cbc[ntemp][4] == 2)
                    {
                        diagn[iel][2][0] = sje[ntemp][4][0][0];
                    }
                }
            }
            else if(cb5 == 0 || cb5 == 1)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][2] = true;
                if(cb5 == 1)
                {
                    ntemp = sje[iel][0][0][0];
                    if(cbc[ntemp][4] == 2)
                    {
                        diagn[iel][2][0] = sje[ntemp][4][0][0];
                    }
                }
            }
        }
        else if(cb1 == 0)
        {
            if(cb3 != 3)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][1] = true;
            }
            if(cb5 != 3)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][2] = true;
            }
        }
        if(cb3 == 1)
        {
            newe[iel] = newe[iel] + 1;
            eassign[iel][9] = true;
            if(cb5 == 1)
            {
                ntemp = sje[iel][2][0][0];
                if(cbc[ntemp][4] == 2)
                {
                    diagn[iel][9][0] = sje[ntemp][4][0][0];
                    diagn[iel][9][1] = ijel[iel][2][1];
                    ncon_edge[sje[ntemp][4][0][0]][10] = true;
                    if_1_edge[iel][9] = true;
                }
            }
            if(ijel[iel][2][0] == 1)
            {
                ntemp = sje[iel][2][0][0];
                if(cbc[ntemp][4] == 3)
                {
                    diagn[iel][9][0] = sje[ntemp][4][ijel[iel][2][1]][0];
                }
            }
        }
        else if(cb3 == 2)
        {
            if(cb5 == 2)
            {
                ntemp = sje[iel][2][0][0];
                if(cbc[ntemp][4] != 3)
                {
                    newe[iel] = newe[iel] + 1;
                    eassign[iel][9] = true;
                    if(cbc[ntemp][4] == 2)
                    {
                        diagn[iel][9][0] = sje[ntemp][4][0][0];
                    }
                }
            }
            else if(cb5 == 0 || cb5 == 1)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][9] = true;
                if(cb5 == 1)
                {
                    ntemp = sje[iel][2][0][0];
                    if(cbc[ntemp][4] == 2)
                    {
                        diagn[iel][9][0] = sje[ntemp][4][0][0];
                    }
                }
            }
        }
        else if(cb3 == 0)
        {
            if(cb5 != 3)
            {
                newe[iel] = newe[iel] + 1;
                eassign[iel][9] = true;
            }
        }
        if(cb6 == 1 || cb6 == 0)
        {
            newi[iel] = newi[iel] + 9;
            fassign[iel][5] = true;
        }
        if(cb4 == 1 || cb4 == 0)
        {
            newi[iel] = newi[iel] + 9;
            fassign[iel][3] = true;
        }
        if(cb2 == 1 || cb2 == 0)
        {
            newi[iel] = newi[iel] + 9;
            fassign[iel][1] = true;
        }
        if(cb1 != 3)
        {
            newi[iel] = newi[iel] + 9;
            fassign[iel][0] = true;
        }
        if(cb3 != 3)
        {
            newi[iel] = newi[iel] + 9;
            fassign[iel][2] = true;
        }
        if(cb5 != 3)
        {
            newi[iel] = newi[iel] + 9;
            fassign[iel][4] = true;
        }
        newc[iel] = newe[iel] * 3 + newi[iel];
    }

#pragma endscop
}
