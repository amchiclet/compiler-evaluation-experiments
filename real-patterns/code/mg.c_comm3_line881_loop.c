#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i3;
extern int n3;
extern int i2;
extern int n2;
extern double * restrict u;
extern int m2lt;
extern int m1lt;
extern int n1;

void loop()
{
#pragma scop

    for(i3 = 1; i3 < n3 - 1; i3++)
    {
        for(i2 = 1; i2 < n2 - 1; i2++)
        {
            u[i3 * m2lt * m1lt + i2 * m1lt +(n1 - 1)] = u[i3 * m2lt * m1lt + i2 * m1lt + 1];
            u[i3 * m2lt * m1lt + i2 * m1lt + 0] = u[i3 * m2lt * m1lt + i2 * m1lt +(n1 - 2)];
        }
    }

#pragma endscop
}
