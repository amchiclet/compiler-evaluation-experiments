#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m1;
extern double * restrict z;
extern int  j3['\n'][2] ;
extern int m2lt;
extern int m1lt;
extern int  j2['\n'][2] ;
extern int  j1['\n'][2] ;

void loop()
{
#pragma scop

    for(i = '\n' - 1; i >= m1; i--)
    {
        z[j3[i][1] * m2lt * m1lt + j2[i][1] * m1lt + j1[i][1]] = 1.0;
    }

#pragma endscop
}
