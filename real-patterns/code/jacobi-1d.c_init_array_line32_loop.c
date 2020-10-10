#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  A[2000 + 0] ;
extern double  B[2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        A[i] =(((double )i) + 2) / n;
        B[i] =(((double )i) + 3) / n;
    }

#pragma endscop
}
