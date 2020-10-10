#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern long Inner_loops;
extern double  Px[101][25] ;
extern double  Xtra[40] ;

void loop()
{
#pragma scop

    for(i = 0; i < Inner_loops; i++)
    {
        Px[i][0] = Xtra[22] * Px[i][12] + Xtra[21] * Px[i][11] + Xtra[20] * Px[i][10] + Xtra[19] * Px[i][9] + Xtra[18] * Px[i][8] + Xtra[17] * Px[i][7] + Xtra[16] * Px[i][6] + Xtra[12] *(Px[i][4] + Px[i][5]) + Px[i][2];
    }

#pragma endscop
}
