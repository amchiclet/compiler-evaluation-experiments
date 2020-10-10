#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i3;
extern int n3;
extern int i2;
extern int n2;
extern int i1;
extern int n1;
extern double * restrict z;
extern int m2lt;
extern int m1lt;

void loop()
{
#pragma scop

    for(i3 = 0; i3 < n3; i3++)
    {
        for(i2 = 0; i2 < n2; i2++)
        {
            for(i1 = 0; i1 < n1; i1++)
            {
                z[i3 * m2lt * m1lt + i2 * m1lt + i1] = 0.0;
            }
        }
    }

#pragma endscop
}
