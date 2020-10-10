#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long kx;
extern long ky;
extern long Inner_loops;
extern double  Du1[101] ;
extern double  U1[2][101][5] ;
extern long nl1;
extern double  Du2[101] ;
extern double  U2[2][101][5] ;
extern double  Du3[101] ;
extern double  U3[2][101][5] ;
extern long nl2;
extern double  Xtra[40] ;

void loop()
{
#pragma scop

    for(kx = 1; kx < 3; kx++)
    {
        for(ky = 1; ky < Inner_loops; ky++)
        {
            Du1[ky] = U1[nl1][ky + 1][kx] - U1[nl1][ky - 1][kx];
            Du2[ky] = U2[nl1][ky + 1][kx] - U2[nl1][ky - 1][kx];
            Du3[ky] = U3[nl1][ky + 1][kx] - U3[nl1][ky - 1][kx];
            U1[nl2][ky][kx] = U1[nl1][ky][kx] + Xtra[1] * Du1[ky] + Xtra[2] * Du2[ky] + Xtra[3] * Du3[ky] + Xtra[34] *(U1[nl1][ky][kx + 1] - 2.0 * U1[nl1][ky][kx] + U1[nl1][ky][kx - 1]);
            U2[nl2][ky][kx] = U2[nl1][ky][kx] + Xtra[4] * Du1[ky] + Xtra[5] * Du2[ky] + Xtra[6] * Du3[ky] + Xtra[34] *(U2[nl1][ky][kx + 1] - 2.0 * U2[nl1][ky][kx] + U2[nl1][ky][kx - 1]);
            U3[nl2][ky][kx] = U3[nl1][ky][kx] + Xtra[7] * Du1[ky] + Xtra[8] * Du2[ky] + Xtra[9] * Du3[ky] + Xtra[34] *(U3[nl1][ky][kx + 1] - 2.0 * U3[nl1][ky][kx] + U3[nl1][ky][kx - 1]);
        }
    }

#pragma endscop
}
