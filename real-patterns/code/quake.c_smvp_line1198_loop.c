#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nodes;
extern int Anext;
extern int * restrict Aindex;
extern int Alast;
extern double sum0;
extern double *** restrict A;
extern double ** restrict v;
extern double sum1;
extern double sum2;
extern int col;
extern int * restrict Acol;
extern double ** restrict w;

void loop()
{
#pragma scop

    for(i = 0; i < nodes; i++)
    {
        Anext = Aindex[i];
        Alast = Aindex[i + 1];
        sum0 = A[Anext][0][0] * v[i][0] + A[Anext][0][1] * v[i][1] + A[Anext][0][2] * v[i][2];
        sum1 = A[Anext][1][0] * v[i][0] + A[Anext][1][1] * v[i][1] + A[Anext][1][2] * v[i][2];
        sum2 = A[Anext][2][0] * v[i][0] + A[Anext][2][1] * v[i][1] + A[Anext][2][2] * v[i][2];
        Anext++;
        while(Anext < Alast)
        {
            col = Acol[Anext];
            sum0 += A[Anext][0][0] * v[col][0] + A[Anext][0][1] * v[col][1] + A[Anext][0][2] * v[col][2];
            sum1 += A[Anext][1][0] * v[col][0] + A[Anext][1][1] * v[col][1] + A[Anext][1][2] * v[col][2];
            sum2 += A[Anext][2][0] * v[col][0] + A[Anext][2][1] * v[col][1] + A[Anext][2][2] * v[col][2];
            w[col][0] += A[Anext][0][0] * v[i][0] + A[Anext][1][0] * v[i][1] + A[Anext][2][0] * v[i][2];
            w[col][1] += A[Anext][0][1] * v[i][0] + A[Anext][1][1] * v[i][1] + A[Anext][2][1] * v[i][2];
            w[col][2] += A[Anext][0][2] * v[i][0] + A[Anext][1][2] * v[i][1] + A[Anext][2][2] * v[i][2];
            Anext++;
        }
        w[i][0] += sum0;
        w[i][1] += sum1;
        w[i][2] += sum2;
    }

#pragma endscop
}
