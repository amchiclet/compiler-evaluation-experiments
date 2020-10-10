#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int iel;
extern int nelt;
extern int cb;
extern int  cbc[2400][6] ;
extern int cb1;
extern int cb2;
extern int sumcb;
extern int  newc[2400] ;
extern int  vassign[2400][8] ;
extern int ij1;
extern int  ijel[2400][6][2] ;
extern int ij2;
extern int ntemp;
extern int  sje[2400][6][2][2] ;
extern int ntemp1;

void loop()
{
#pragma scop

    for(iel = 0; iel < nelt; iel++)
    {
        cb = cbc[iel][5];
        cb1 = cbc[iel][3];
        cb2 = cbc[iel][1];
        sumcb = 0;
        if(cb == 2 || cb == 3)
        {
            sumcb = sumcb + 1;
        }
        else if(cb == 0)
        {
            sumcb = sumcb + 2;
        }
        else if(cb == 1)
        {
            sumcb = sumcb + 5;
        }
        if(cb1 == 2 || cb1 == 3)
        {
            sumcb = sumcb + 1;
        }
        else if(cb1 == 0)
        {
            sumcb = sumcb + 2;
        }
        else if(cb1 == 1)
        {
            sumcb = sumcb + 5;
        }
        if(cb2 == 2 || cb2 == 3)
        {
            sumcb = sumcb + 1;
        }
        else if(cb2 == 0)
        {
            sumcb = sumcb + 2;
        }
        else if(cb2 == 1)
        {
            sumcb = sumcb + 5;
        }
        if(sumcb == 3)
        {
            newc[iel] = 1;
            vassign[iel][0] = 7;
        }
        else if(sumcb == 4)
        {
            newc[iel] = 2;
            if(cb == 0)
            {
                vassign[iel][0] = 3;
            }
            else if(cb1 == 0)
            {
                vassign[iel][0] = 5;
            }
            else if(cb2 == 0)
            {
                vassign[iel][0] = 6;
            }
            vassign[iel][1] = 7;
        }
        else if(sumcb == 7)
        {
            if(cb == 1)
            {
                ij1 = ijel[iel][5][0];
                ij2 = ijel[iel][5][1];
                if(ij1 == 0 && ij2 == 0)
                {
                    newc[iel] = 2;
                    vassign[iel][0] = 3;
                    vassign[iel][1] = 7;
                }
                else if(ij1 == 0 && ij2 == 1)
                {
                    ntemp = sje[iel][5][0][0];
                    if(cbc[ntemp][0] == 3 && sje[ntemp][0][0][0] < iel)
                    {
                        newc[iel] = 1;
                        vassign[iel][0] = 7;
                    }
                    else
                    {
                        newc[iel] = 2;
                        vassign[iel][0] = 3;
                        vassign[iel][1] = 7;
                    }
                }
                else if(ij1 == 1 && ij2 == 0)
                {
                    ntemp = sje[iel][5][0][0];
                    if(cbc[ntemp][2] == 3 && sje[ntemp][2][0][0] < iel)
                    {
                        newc[iel] = 1;
                        vassign[iel][0] = 7;
                    }
                    else
                    {
                        newc[iel] = 2;
                        vassign[iel][0] = 3;
                        vassign[iel][1] = 7;
                    }
                }
                else
                {
                    newc[iel] = 1;
                    vassign[iel][0] = 7;
                }
            }
            else if(cb1 == 1)
            {
                ij1 = ijel[iel][3][0];
                ij2 = ijel[iel][3][1];
                if(ij1 == 0 && ij2 == 0)
                {
                    newc[iel] = 2;
                    vassign[iel][0] = 5;
                    vassign[iel][1] = 7;
                }
                else if(ij1 == 0 && ij2 == 1)
                {
                    ntemp = sje[iel][3][0][0];
                    if(cbc[ntemp][0] == 3 && sje[ntemp][0][0][0] < iel)
                    {
                        newc[iel] = 1;
                        vassign[iel][0] = 7;
                    }
                    else
                    {
                        newc[iel] = 2;
                        vassign[iel][0] = 5;
                        vassign[iel][1] = 7;
                    }
                }
                else if(ij1 == 1 && ij2 == 0)
                {
                    ntemp = sje[iel][3][0][0];
                    if(cbc[ntemp][4] == 3 && sje[ntemp][4][0][0] < iel)
                    {
                        newc[iel] = 1;
                        vassign[iel][0] = 7;
                    }
                    else
                    {
                        newc[iel] = 2;
                        vassign[iel][0] = 5;
                        vassign[iel][1] = 7;
                    }
                }
                else
                {
                    newc[iel] = 1;
                    vassign[iel][0] = 7;
                }
            }
            else if(cb2 == 1)
            {
                ij1 = ijel[iel][1][0];
                ij2 = ijel[iel][1][1];
                if(ij1 == 0 && ij2 == 0)
                {
                    newc[iel] = 2;
                    vassign[iel][0] = 6;
                    vassign[iel][1] = 7;
                }
                else if(ij1 == 0 && ij2 == 1)
                {
                    ntemp = sje[iel][1][0][0];
                    if(cbc[ntemp][2] == 3 && sje[ntemp][2][0][0] < iel)
                    {
                        newc[iel] = 1;
                        vassign[iel][0] = 7;
                    }
                    else
                    {
                        newc[iel] = 2;
                        vassign[iel][0] = 6;
                        vassign[iel][1] = 7;
                    }
                }
                else if(ij1 == 1 && ij2 == 0)
                {
                    ntemp = sje[iel][1][0][0];
                    if(cbc[ntemp][4] == 3 && sje[ntemp][4][0][0] < iel)
                    {
                        newc[iel] = 1;
                        vassign[iel][0] = 7;
                    }
                    else
                    {
                        newc[iel] = 2;
                        vassign[iel][0] = 6;
                        vassign[iel][1] = 7;
                    }
                }
                else
                {
                    newc[iel] = 1;
                    vassign[iel][0] = 7;
                }
            }
        }
        else if(sumcb == 5)
        {
            newc[iel] = 4;
            if(cb == 2 || cb == 3)
            {
                vassign[iel][0] = 4;
                vassign[iel][1] = 5;
                vassign[iel][2] = 6;
                vassign[iel][3] = 7;
            }
            else if(cb1 == 2 || cb1 == 3)
            {
                vassign[iel][0] = 2;
                vassign[iel][1] = 3;
                vassign[iel][2] = 6;
                vassign[iel][3] = 7;
            }
            else if(cb2 == 2 || cb2 == 3)
            {
                vassign[iel][0] = 1;
                vassign[iel][1] = 3;
                vassign[iel][2] = 5;
                vassign[iel][3] = 7;
            }
        }
        else if(sumcb == 8)
        {
            if(cb == 1)
            {
                if(cb1 == 2 || cb1 == 3)
                {
                    ij1 = ijel[iel][5][0];
                    if(ij1 == 0)
                    {
                        newc[iel] = 4;
                        vassign[iel][0] = 2;
                        vassign[iel][1] = 3;
                        vassign[iel][2] = 6;
                        vassign[iel][3] = 7;
                    }
                    else
                    {
                        ntemp = sje[iel][5][0][0];
                        if(cbc[ntemp][2] == 3 && sje[ntemp][2][0][0] < iel)
                        {
                            newc[iel] = 2;
                            vassign[iel][0] = 6;
                            vassign[iel][1] = 7;
                        }
                        else
                        {
                            newc[iel] = 3;
                            vassign[iel][0] = 3;
                            vassign[iel][1] = 6;
                            vassign[iel][2] = 7;
                        }
                    }
                }
                else if(cb2 == 2 || cb2 == 3)
                {
                    if(ijel[iel][5][1] == 0)
                    {
                        newc[iel] = 4;
                        vassign[iel][0] = 1;
                        vassign[iel][1] = 3;
                        vassign[iel][2] = 5;
                        vassign[iel][3] = 7;
                    }
                    else
                    {
                        ntemp = sje[iel][5][0][0];
                        if(cbc[ntemp][0] == 3 && sje[ntemp][0][0][0] < iel)
                        {
                            newc[iel] = 2;
                            vassign[iel][0] = 5;
                            vassign[iel][1] = 7;
                        }
                        else
                        {
                            newc[iel] = 3;
                            vassign[iel][0] = 3;
                            vassign[iel][1] = 5;
                            vassign[iel][2] = 7;
                        }
                    }
                }
            }
            else if(cb1 == 1)
            {
                if(cb == 2 || cb == 3)
                {
                    ij1 = ijel[iel][3][0];
                    ij2 = ijel[iel][3][1];
                    if(ij1 == 0 && ij2 == 0)
                    {
                        ntemp = sje[iel][3][0][0];
                        if(cbc[ntemp][1] == 3 && sje[ntemp][1][0][0] < iel)
                        {
                            newc[iel] = 3;
                            vassign[iel][0] = 5;
                            vassign[iel][1] = 6;
                            vassign[iel][2] = 7;
                        }
                        else
                        {
                            newc[iel] = 4;
                            vassign[iel][0] = 4;
                            vassign[iel][1] = 5;
                            vassign[iel][2] = 6;
                            vassign[iel][3] = 7;
                        }
                    }
                    else if(ij1 == 0 && ij2 == 1)
                    {
                        ntemp = sje[iel][3][0][0];
                        if(cbc[ntemp][0] == 3 && sje[ntemp][0][0][0] < iel)
                        {
                            newc[iel] = 3;
                            vassign[iel][0] = 4;
                            vassign[iel][1] = 6;
                            vassign[iel][2] = 7;
                        }
                        else
                        {
                            newc[iel] = 4;
                            vassign[iel][0] = 4;
                            vassign[iel][1] = 5;
                            vassign[iel][2] = 6;
                            vassign[iel][3] = 7;
                        }
                    }
                    else if(ij1 == 1 && ij2 == 0)
                    {
                        ntemp = sje[iel][3][0][0];
                        if(cbc[ntemp][4] == 3 && sje[ntemp][4][0][0] < iel)
                        {
                            newc[iel] = 2;
                            vassign[iel][0] = 6;
                            vassign[iel][1] = 7;
                        }
                        else
                        {
                            newc[iel] = 3;
                            vassign[iel][0] = 5;
                            vassign[iel][1] = 6;
                            vassign[iel][2] = 7;
                        }
                    }
                    else if(ij1 == 1 && ij2 == 1)
                    {
                        ntemp = sje[iel][3][0][0];
                        if(cbc[ntemp][4] == 3 && sje[ntemp][4][0][0] < iel)
                        {
                            newc[iel] = 2;
                            vassign[iel][0] = 6;
                            vassign[iel][1] = 7;
                        }
                        else
                        {
                            newc[iel] = 3;
                            vassign[iel][0] = 4;
                            vassign[iel][1] = 6;
                            vassign[iel][2] = 7;
                        }
                    }
                }
                else
                {
                    if(ijel[iel][3][1] == 0)
                    {
                        newc[iel] = 4;
                        vassign[iel][0] = 1;
                        vassign[iel][1] = 3;
                        vassign[iel][2] = 5;
                        vassign[iel][3] = 7;
                    }
                    else
                    {
                        ntemp = sje[iel][3][0][0];
                        if(cbc[ntemp][0] == 3 && sje[ntemp][0][0][0] < iel)
                        {
                            newc[iel] = 2;
                            vassign[iel][0] = 3;
                            vassign[iel][1] = 7;
                        }
                        else
                        {
                            newc[iel] = 3;
                            vassign[iel][0] = 3;
                            vassign[iel][1] = 5;
                            vassign[iel][2] = 7;
                        }
                    }
                }
            }
            else if(cb2 == 1)
            {
                if(cb == 2 || cb == 3)
                {
                    if(ijel[iel][1][0] == 0)
                    {
                        newc[iel] = 4;
                        vassign[iel][0] = 4;
                        vassign[iel][1] = 5;
                        vassign[iel][2] = 6;
                        vassign[iel][3] = 7;
                    }
                    else
                    {
                        ntemp = sje[iel][1][0][0];
                        if(cbc[ntemp][4] == 3 && sje[ntemp][4][0][0] < iel)
                        {
                            newc[iel] = 2;
                            vassign[iel][0] = 5;
                            vassign[iel][1] = 7;
                        }
                        else
                        {
                            newc[iel] = 3;
                            vassign[iel][0] = 5;
                            vassign[iel][1] = 6;
                            vassign[iel][2] = 7;
                        }
                    }
                }
                else
                {
                    if(ijel[iel][1][1] == 0)
                    {
                        newc[iel] = 4;
                        vassign[iel][0] = 2;
                        vassign[iel][1] = 3;
                        vassign[iel][2] = 6;
                        vassign[iel][3] = 7;
                    }
                    else
                    {
                        ntemp = sje[iel][1][0][0];
                        if(cbc[ntemp][2] == 3 && sje[ntemp][2][0][0] < iel)
                        {
                            newc[iel] = 2;
                            vassign[iel][0] = 3;
                            vassign[iel][1] = 7;
                        }
                        else
                        {
                            newc[iel] = 3;
                            vassign[iel][0] = 3;
                            vassign[iel][1] = 6;
                            vassign[iel][2] = 7;
                        }
                    }
                }
            }
        }
        else if(sumcb == 11)
        {
            if(cb == 2 || cb == 3)
            {
                if(ijel[iel][3][0] == 0)
                {
                    ntemp = sje[iel][3][0][0];
                    if(cbc[ntemp][1] == 3 && sje[ntemp][1][0][0] < iel)
                    {
                        newc[iel] = 3;
                        vassign[iel][0] = 5;
                        vassign[iel][1] = 6;
                        vassign[iel][2] = 7;
                    }
                    else
                    {
                        newc[iel] = 4;
                        vassign[iel][0] = 4;
                        vassign[iel][1] = 5;
                        vassign[iel][2] = 6;
                        vassign[iel][3] = 7;
                    }
                }
                else
                {
                    ntemp = sje[iel][1][0][0];
                    if(cbc[ntemp][4] == 3 && sje[ntemp][4][0][0] < iel)
                    {
                        ntemp1 = sje[iel][3][0][0];
                        if(cbc[ntemp1][4] == 3 && sje[ntemp1][4][0][0] < iel)
                        {
                            newc[iel] = 1;
                            vassign[iel][0] = 7;
                        }
                        else
                        {
                            newc[iel] = 2;
                            vassign[iel][0] = 5;
                            vassign[iel][1] = 7;
                        }
                    }
                    else
                    {
                        ntemp1 = sje[iel][3][0][0];
                        if(cbc[ntemp1][4] == 3 && sje[ntemp1][4][0][0] < iel)
                        {
                            newc[iel] = 2;
                            vassign[iel][0] = 6;
                            vassign[iel][1] = 7;
                        }
                        else
                        {
                            newc[iel] = 3;
                            vassign[iel][0] = 5;
                            vassign[iel][1] = 6;
                            vassign[iel][2] = 7;
                        }
                    }
                }
            }
            else if(cb1 == 2 || cb1 == 3)
            {
                if(ijel[iel][1][1] == 0)
                {
                    ntemp = sje[iel][1][0][0];
                    if(cbc[ntemp][5] == 3 && sje[ntemp][5][0][0] < iel)
                    {
                        newc[iel] = 3;
                        vassign[iel][0] = 3;
                        vassign[iel][1] = 6;
                        vassign[iel][2] = 7;
                    }
                    else
                    {
                        newc[iel] = 4;
                        vassign[iel][0] = 2;
                        vassign[iel][1] = 3;
                        vassign[iel][2] = 6;
                        vassign[iel][3] = 7;
                    }
                }
                else
                {
                    ntemp = sje[iel][1][0][0];
                    if(cbc[ntemp][2] == 3 && sje[ntemp][2][0][0] < iel)
                    {
                        ntemp1 = sje[iel][5][0][0];
                        if(cbc[ntemp1][2] == 3 && sje[ntemp1][2][0][0] < iel)
                        {
                            newc[iel] = 1;
                            vassign[iel][0] = 7;
                        }
                        else
                        {
                            newc[iel] = 2;
                            vassign[iel][0] = 3;
                            vassign[iel][1] = 7;
                        }
                    }
                    else
                    {
                        ntemp1 = sje[iel][5][0][0];
                        if(cbc[ntemp1][2] == 3 && sje[ntemp1][2][0][0] < iel)
                        {
                            newc[iel] = 2;
                            vassign[iel][0] = 6;
                            vassign[iel][1] = 7;
                        }
                        else
                        {
                            newc[iel] = 3;
                            vassign[iel][0] = 3;
                            vassign[iel][1] = 6;
                            vassign[iel][2] = 7;
                        }
                    }
                }
            }
            else if(cb2 == 2 || cb2 == 3)
            {
                if(ijel[iel][5][1] == 0)
                {
                    ntemp = sje[iel][3][0][0];
                    if(cbc[ntemp][5] == 3 && sje[ntemp][5][0][0] < iel)
                    {
                        newc[iel] = 3;
                        vassign[iel][0] = 3;
                        vassign[iel][1] = 5;
                        vassign[iel][2] = 7;
                    }
                    else
                    {
                        newc[iel] = 4;
                        vassign[iel][0] = 1;
                        vassign[iel][1] = 3;
                        vassign[iel][2] = 5;
                        vassign[iel][3] = 7;
                    }
                }
                else
                {
                    ntemp = sje[iel][3][0][0];
                    if(cbc[ntemp][0] == 3 && sje[ntemp][0][0][0] < iel)
                    {
                        ntemp1 = sje[iel][5][0][0];
                        if(cbc[ntemp1][0] == 3 && sje[ntemp1][0][0][0] < iel)
                        {
                            newc[iel] = 1;
                            vassign[iel][0] = 7;
                        }
                        else
                        {
                            newc[iel] = 2;
                            vassign[iel][0] = 3;
                            vassign[iel][1] = 7;
                        }
                    }
                    else
                    {
                        ntemp1 = sje[iel][5][0][0];
                        if(cbc[ntemp1][0] == 3 && sje[ntemp1][0][0][0] < iel)
                        {
                            newc[iel] = 2;
                            vassign[iel][0] = 5;
                            vassign[iel][1] = 7;
                        }
                        else
                        {
                            newc[iel] = 3;
                            vassign[iel][0] = 3;
                            vassign[iel][1] = 5;
                            vassign[iel][2] = 7;
                        }
                    }
                }
            }
        }
        else if(sumcb == 6)
        {
            newc[iel] = 8;
            vassign[iel][0] = 0;
            vassign[iel][1] = 1;
            vassign[iel][2] = 2;
            vassign[iel][3] = 3;
            vassign[iel][4] = 4;
            vassign[iel][5] = 5;
            vassign[iel][6] = 6;
            vassign[iel][7] = 7;
        }
        else if(sumcb == 9)
        {
            newc[iel] = 7;
            vassign[iel][0] = 1;
            vassign[iel][1] = 2;
            vassign[iel][2] = 3;
            vassign[iel][3] = 4;
            vassign[iel][4] = 5;
            vassign[iel][5] = 6;
            vassign[iel][6] = 7;
        }
        else if(sumcb == 12)
        {
            if(cb == 0)
            {
                ntemp = sje[iel][1][0][0];
                if(cbc[ntemp][3] == 3 && sje[ntemp][3][0][0] < iel)
                {
                    newc[iel] = 6;
                    vassign[iel][0] = 1;
                    vassign[iel][1] = 2;
                    vassign[iel][2] = 3;
                    vassign[iel][3] = 5;
                    vassign[iel][4] = 6;
                    vassign[iel][5] = 7;
                }
                else
                {
                    newc[iel] = 7;
                    vassign[iel][0] = 1;
                    vassign[iel][1] = 2;
                    vassign[iel][2] = 3;
                    vassign[iel][3] = 4;
                    vassign[iel][4] = 5;
                    vassign[iel][5] = 6;
                    vassign[iel][6] = 7;
                }
            }
            else if(cb1 == 0)
            {
                newc[iel] = 7;
                vassign[iel][0] = 1;
                vassign[iel][1] = 2;
                vassign[iel][2] = 3;
                vassign[iel][3] = 4;
                vassign[iel][4] = 5;
                vassign[iel][5] = 6;
                vassign[iel][6] = 7;
            }
            else if(cb2 == 0)
            {
                ntemp = sje[iel][3][0][0];
                if(cbc[ntemp][5] == 3 && sje[ntemp][5][0][0] < iel)
                {
                    newc[iel] = 6;
                    vassign[iel][0] = 2;
                    vassign[iel][1] = 3;
                    vassign[iel][2] = 4;
                    vassign[iel][3] = 5;
                    vassign[iel][4] = 6;
                    vassign[iel][5] = 7;
                }
                else
                {
                    newc[iel] = 7;
                    vassign[iel][0] = 1;
                    vassign[iel][1] = 2;
                    vassign[iel][2] = 3;
                    vassign[iel][3] = 4;
                    vassign[iel][4] = 5;
                    vassign[iel][5] = 6;
                    vassign[iel][6] = 7;
                }
            }
        }
        else if(sumcb == 15)
        {
            ntemp = sje[iel][3][0][0];
            ntemp1 = sje[iel][1][0][0];
            if(cbc[ntemp][5] == 3 && sje[ntemp][5][0][0] < iel)
            {
                if(cbc[ntemp][1] == 3 && sje[ntemp][1][0][0] < iel)
                {
                    if(cbc[ntemp1][5] == 3 && sje[ntemp1][5][0][0] < iel)
                    {
                        newc[iel] = 4;
                        vassign[iel][0] = 3;
                        vassign[iel][1] = 5;
                        vassign[iel][2] = 6;
                        vassign[iel][3] = 7;
                    }
                    else
                    {
                        newc[iel] = 5;
                        vassign[iel][0] = 2;
                        vassign[iel][1] = 3;
                        vassign[iel][2] = 5;
                        vassign[iel][3] = 6;
                        vassign[iel][4] = 7;
                    }
                }
                else
                {
                    if(cbc[ntemp1][5] == 3 && sje[ntemp1][5][0][0] < iel)
                    {
                        newc[iel] = 5;
                        vassign[iel][0] = 3;
                        vassign[iel][1] = 4;
                        vassign[iel][2] = 5;
                        vassign[iel][3] = 6;
                        vassign[iel][4] = 7;
                    }
                    else
                    {
                        newc[iel] = 6;
                        vassign[iel][0] = 2;
                        vassign[iel][1] = 3;
                        vassign[iel][2] = 4;
                        vassign[iel][3] = 5;
                        vassign[iel][4] = 6;
                        vassign[iel][5] = 7;
                    }
                }
            }
            else
            {
                if(cbc[ntemp][1] == 3 && sje[ntemp][1][0][0] < iel)
                {
                    if(cbc[ntemp1][5] == 3 && sje[ntemp1][5][0][0] < iel)
                    {
                        newc[iel] = 5;
                        vassign[iel][0] = 1;
                        vassign[iel][1] = 3;
                        vassign[iel][2] = 5;
                        vassign[iel][3] = 6;
                        vassign[iel][4] = 7;
                    }
                    else
                    {
                        newc[iel] = 6;
                        vassign[iel][0] = 1;
                        vassign[iel][1] = 2;
                        vassign[iel][2] = 3;
                        vassign[iel][3] = 5;
                        vassign[iel][4] = 6;
                        vassign[iel][5] = 7;
                    }
                }
                else
                {
                    if(cbc[ntemp1][5] == 3 && sje[ntemp1][5][0][0] < iel)
                    {
                        newc[iel] = 6;
                        vassign[iel][0] = 1;
                        vassign[iel][1] = 3;
                        vassign[iel][2] = 4;
                        vassign[iel][3] = 5;
                        vassign[iel][4] = 6;
                        vassign[iel][5] = 7;
                    }
                    else
                    {
                        newc[iel] = 7;
                        vassign[iel][0] = 1;
                        vassign[iel][1] = 2;
                        vassign[iel][2] = 3;
                        vassign[iel][3] = 4;
                        vassign[iel][4] = 5;
                        vassign[iel][5] = 6;
                        vassign[iel][6] = 7;
                    }
                }
            }
        }
    }

#pragma endscop
}
