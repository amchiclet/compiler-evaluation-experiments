#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int BlockSize;
extern int j;
extern double  A[4] ;
extern double * restrict dfx;
extern double * restrict dfy;
extern double  rhs[2] ;
extern double * restrict z;

void loop()
{
#pragma scop

    for(i = 0; i < BlockSize; i++)
    {
        for(j = 0; j < BlockSize; j++)
        {
            A[0] += dfx[i * BlockSize + j] * dfx[i * BlockSize + j];
            A[1] += dfx[i * BlockSize + j] * dfy[i * BlockSize + j];
            A[2] = A[1];
            A[3] += dfy[i * BlockSize + j] * dfy[i * BlockSize + j];
            rhs[0] += z[i * BlockSize + j] * dfx[i * BlockSize + j];
            rhs[1] += z[i * BlockSize + j] * dfy[i * BlockSize + j];
        }
    }

#pragma endscop
}
