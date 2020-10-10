#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int iel;
extern int ntemp;
extern int j;
extern int i;
extern int  idel[2400][6][5][5] ;

void loop()
{
#pragma scop

    for(iel = 0; iel < 2400; iel++)
    {
        ntemp = 5 * 5 * 5 * iel;
        for(j = 0; j < 5; j++)
        {
            for(i = 0; i < 5; i++)
            {
                idel[iel][0][j][i] = ntemp + i * 5 + j * 5 * 5 + 5 - 1;
                idel[iel][1][j][i] = ntemp + i * 5 + j * 5 * 5;
                idel[iel][2][j][i] = ntemp + i * 1 + j * 5 * 5 + 5 *(5 - 1);
                idel[iel][3][j][i] = ntemp + i * 1 + j * 5 * 5;
                idel[iel][4][j][i] = ntemp + i * 1 + j * 5 + 5 * 5 *(5 - 1);
                idel[iel][5][j][i] = ntemp + i * 1 + j * 5;
            }
        }
    }

#pragma endscop
}
