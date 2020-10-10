#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double  A[1300 + 0][1300 + 0] ;
extern double  B[1300 + 0][1300 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) for(j = 0; j < n; j++)
        {
            A[i][j] =(((double )i) *(j + 2) + 2) / n;
            B[i][j] =(((double )i) *(j + 3) + 3) / n;
        }

#pragma endscop
}
