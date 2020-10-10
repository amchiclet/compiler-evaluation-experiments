#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ni;
extern int j;
extern int nj;
extern double  C[1000 + 0][1100 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < ni; i++) for(j = 0; j < nj; j++) C[i][j] =((double )(i * j % ni)) / ni;

#pragma endscop
}
