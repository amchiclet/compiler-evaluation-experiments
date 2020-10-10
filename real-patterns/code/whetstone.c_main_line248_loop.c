#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long I;
extern long N6;
extern int J;
extern int K;
extern int L;
extern double  E1[5] ;

void loop()
{
#pragma scop

    for(I = 1; I <= N6; I++)
    {
        J = J *(K - J) *(L - K);
        K = L * K -(L - J) * K;
        L =(L - K) *(K + J);
        E1[L - 1] =(J + K + L);
        E1[K - 1] =(J * K * L);
    }

#pragma endscop
}
