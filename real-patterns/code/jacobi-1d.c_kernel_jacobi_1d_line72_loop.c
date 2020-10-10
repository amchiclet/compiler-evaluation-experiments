#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int t;
extern int tsteps;
extern int i;
extern int n;
extern double  B[2000 + 0] ;
extern double  A[2000 + 0] ;

void loop()
{
#pragma scop

    for(t = 0; t < tsteps; t++)
    {
        for(i = 1; i < n - 1; i++) B[i] = 0.33333 *(A[i - 1] + A[i] + A[i + 1]);
        for(i = 1; i < n - 1; i++) A[i] = 0.33333 *(B[i - 1] + B[i] + B[i + 1]);
    }

#pragma endscop
}
