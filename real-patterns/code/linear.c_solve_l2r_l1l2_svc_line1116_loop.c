#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int l;
extern double v;
extern double * restrict alpha;
extern double  diag[3] ;
typedef signed char schar;
extern schar * restrict y;
extern int nSV;

void loop()
{
#pragma scop

    for(i = 0; i < l; i++)
    {
        v += alpha[i] *(alpha[i] * diag[y[i] + 1] - 2);
        if(alpha[i] > 0) ++nSV;
    }

#pragma endscop
}
