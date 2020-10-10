#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nx;
extern int j;
extern int ny;
extern double  ex[1000 + 0][1200 + 0] ;
extern double  ey[1000 + 0][1200 + 0] ;
extern double  hz[1000 + 0][1200 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < nx; i++) for(j = 0; j < ny; j++)
        {
            ex[i][j] =((double )i) *(j + 1) / nx;
            ey[i][j] =((double )i) *(j + 2) / ny;
            hz[i][j] =((double )i) *(j + 3) / nx;
        }

#pragma endscop
}
