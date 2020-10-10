#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  u1[2000 + 0] ;
extern double  u2[2000 + 0] ;
extern double fn;
extern double  v1[2000 + 0] ;
extern double  v2[2000 + 0] ;
extern double  y[2000 + 0] ;
extern double  z[2000 + 0] ;
extern double  x[2000 + 0] ;
extern double  w[2000 + 0] ;
extern int j;
extern double  A[2000 + 0][2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        u1[i] = i;
        u2[i] =(i + 1) / fn / 2.0;
        v1[i] =(i + 1) / fn / 4.0;
        v2[i] =(i + 1) / fn / 6.0;
        y[i] =(i + 1) / fn / 8.0;
        z[i] =(i + 1) / fn / 9.0;
        x[i] = 0.0;
        w[i] = 0.0;
        for(j = 0; j < n; j++) A[i][j] =((double )(i * j % n)) / n;
    }

#pragma endscop
}
