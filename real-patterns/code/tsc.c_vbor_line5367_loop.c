#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float a1;
extern float  a[32000] ;
extern float b1;
extern float  b[32000] ;
extern float c1;
extern float  c[32000] ;
extern float d1;
extern float  d[32000] ;
extern float e1;
extern float  e[32000] ;
extern float f1;
extern float  aa[256][256] ;
extern float  x[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 256; i++)
    {
        a1 = a[i];
        b1 = b[i];
        c1 = c[i];
        d1 = d[i];
        e1 = e[i];
        f1 = aa[0][i];
        a1 = a1 * b1 * c1 + a1 * b1 * d1 + a1 * b1 * e1 + a1 * b1 * f1 + a1 * c1 * d1 + a1 * c1 * e1 + a1 * c1 * f1 + a1 * d1 * e1 + a1 * d1 * f1 + a1 * e1 * f1;
        b1 = b1 * c1 * d1 + b1 * c1 * e1 + b1 * c1 * f1 + b1 * d1 * e1 + b1 * d1 * f1 + b1 * e1 * f1;
        c1 = c1 * d1 * e1 + c1 * d1 * f1 + c1 * e1 * f1;
        d1 = d1 * e1 * f1;
        x[i] = a1 * b1 * c1 * d1;
    }

#pragma endscop
}
