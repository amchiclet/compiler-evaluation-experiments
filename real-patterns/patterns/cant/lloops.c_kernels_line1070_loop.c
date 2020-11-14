#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long ip;
extern long Inner_loops;
extern long i1;
extern double  P[512][4] ;
extern long j1;
extern double  B[64][64] ;
extern double  C[64][64] ;
extern long i2;
extern long j2;
extern double  Y[1001] ;
extern double  Z[1001] ;
extern long  E[96] ;
extern long  F[96] ;
extern double  H[64][64] ;

void loop()
{
#pragma scop

    for(ip = 0; ip < Inner_loops; ip++)
    {
        i1 =((long )P[ip][0]);
        j1 =((long )P[ip][1]);
        i1 &=(64 - 1);
        j1 &=(64 - 1);
        P[ip][2] += B[j1][i1];
        P[ip][3] += C[j1][i1];
        P[ip][0] += P[ip][2];
        P[ip][1] += P[ip][3];
        i2 =((long )P[ip][0]);
        j2 =((long )P[ip][1]);
        i2 =(i2 &(64 - 1)) - 1;
        j2 =(j2 &(64 - 1)) - 1;
        P[ip][0] += Y[i2 + 32];
        P[ip][1] += Z[j2 + 32];
        i2 += E[i2 + 32];
        j2 += F[j2 + 32];
        H[j2][i2] += 1.0;
    }

#pragma endscop
}
