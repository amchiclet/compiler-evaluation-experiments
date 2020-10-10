#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int t;
extern int tmax;
extern int j;
extern int ny;
extern double  ey[1000 + 0][1200 + 0] ;
extern double  _fict_[500 + 0] ;
extern int i;
extern int nx;
extern double  hz[1000 + 0][1200 + 0] ;
extern double  ex[1000 + 0][1200 + 0] ;

void loop()
{
#pragma scop

    for(t = 0; t < tmax; t++)
    {
        for(j = 0; j < ny; j++) ey[0][j] = _fict_[t];
        for(i = 1; i < nx; i++) for(j = 0; j < ny; j++) ey[i][j] = ey[i][j] - 0.5 *(hz[i][j] - hz[i - 1][j]);
        for(i = 0; i < nx; i++) for(j = 1; j < ny; j++) ex[i][j] = ex[i][j] - 0.5 *(hz[i][j] - hz[i][j - 1]);
        for(i = 0; i < nx - 1; i++) for(j = 0; j < ny - 1; j++) hz[i][j] = hz[i][j] - 0.7 *(ex[i][j + 1] - ex[i][j] + ey[i + 1][j] - ey[i][j]);
    }

#pragma endscop
}
