#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int r;
extern int n;
extern int s;
extern double  A[2000 + 0][2000 + 0] ;
extern double (* restrict B)[2000 + 0][2000 + 0];

void loop()
{
#pragma scop

    for(r = 0; r < n; ++r) for(s = 0; s < n; ++s) A[r][s] =( *B)[r][s];

#pragma endscop
}
