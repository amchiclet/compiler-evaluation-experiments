#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef double REAL;
extern REAL * restrict dx;
extern REAL dmax;
extern int itemp;

void loop()
{
#pragma scop

    for(i = 1; i < n; i++) if(fabs(((double )dx[i])) > dmax)
        {
            itemp = i;
            dmax = fabs(((double )dx[i]));
        }

#pragma endscop
}
