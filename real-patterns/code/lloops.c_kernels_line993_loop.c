#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern long Inner_loops;
extern double ar;
extern double  Cx[101][25] ;
extern double br;
extern double  Px[101][25] ;
extern double cr;

void loop()
{
#pragma scop

    for(i = 0; i < Inner_loops; i++)
    {
        ar = Cx[i][4];
        br = ar - Px[i][4];
        Px[i][4] = ar;
        cr = br - Px[i][5];
        Px[i][5] = br;
        ar = cr - Px[i][6];
        Px[i][6] = cr;
        br = ar - Px[i][7];
        Px[i][7] = ar;
        cr = br - Px[i][8];
        Px[i][8] = br;
        ar = cr - Px[i][9];
        Px[i][9] = cr;
        br = ar - Px[i][10];
        Px[i][10] = ar;
        cr = br - Px[i][11];
        Px[i][11] = br;
        Px[i][13] = cr - Px[i][12];
        Px[i][12] = cr;
    }

#pragma endscop
}
