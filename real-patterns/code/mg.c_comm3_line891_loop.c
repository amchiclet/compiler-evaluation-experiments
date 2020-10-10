#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i3;
extern int n3;
extern int i1;
extern int n1;
extern double * restrict u;
extern int m2lt;
extern int m1lt;
extern int n2;

void loop()
{
#pragma scop

    for(i3 = 1; i3 < n3 - 1; i3++)
    {
        for(i1 = 0; i1 < n1; i1++)
        {
            u[i3 * m2lt * m1lt +(n2 - 1) * m1lt + i1] = u[i3 * m2lt * m1lt + 1 * m1lt + i1];
            u[i3 * m2lt * m1lt + 0 * m1lt + i1] = u[i3 * m2lt * m1lt +(n2 - 2) * m1lt + i1];
        }
    }

#pragma endscop
}
