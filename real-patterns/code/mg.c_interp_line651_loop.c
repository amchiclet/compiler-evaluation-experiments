#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i3;
extern int mm3;
extern int i2;
extern int mm2;
extern int i1;
extern int mm1;
extern double * restrict z;
extern int m2lt;
extern int m1lt;
extern double * restrict u;

void loop()
{
#pragma scop

    for(i3 = 0; i3 < mm3 - 1; i3++)
    {
        double z1[1037];
        double z2[1037];
        double z3[1037];
        for(i2 = 0; i2 < mm2 - 1; i2++)
        {
            for(i1 = 0; i1 < mm1; i1++)
            {
                z1[i1] = z[i3 * m2lt * m1lt +(i2 + 1) * m1lt + i1] + z[i3 * m2lt * m1lt + i2 * m1lt + i1];
                z2[i1] = z[(i3 + 1) * m2lt * m1lt + i2 * m1lt + i1] + z[i3 * m2lt * m1lt + i2 * m1lt + i1];
                z3[i1] = z[(i3 + 1) * m2lt * m1lt +(i2 + 1) * m1lt + i1] + z[(i3 + 1) * m2lt * m1lt + i2 * m1lt + i1] + z1[i1];
            }
            for(i1 = 0; i1 < mm1 - 1; i1++)
            {
                u[2 * i3 * m2lt * m1lt + 2 * i2 * m1lt + 2 * i1] = u[2 * i3 * m2lt * m1lt + 2 * i2 * m1lt + 2 * i1] + z[i3 * m2lt * m1lt + i2 * m1lt + i1];
                u[2 * i3 * m2lt * m1lt + 2 * i2 * m1lt +(2 * i1 + 1)] = u[2 * i3 * m2lt * m1lt + 2 * i2 * m1lt +(2 * i1 + 1)] + 0.5 *(z[i3 * m2lt * m1lt + i2 * m1lt +(i1 + 1)] + z[i3 * m2lt * m1lt + i2 * m1lt + i1]);
            }
            for(i1 = 0; i1 < mm1 - 1; i1++)
            {
                u[2 * i3 * m2lt * m1lt +(2 * i2 + 1) * m1lt + 2 * i1] = u[2 * i3 * m2lt * m1lt +(2 * i2 + 1) * m1lt + 2 * i1] + 0.5 * z1[i1];
                u[2 * i3 * m2lt * m1lt +(2 * i2 + 1) * m1lt +(2 * i1 + 1)] = u[2 * i3 * m2lt * m1lt +(2 * i2 + 1) * m1lt +(2 * i1 + 1)] + 0.25 *(z1[i1] + z1[i1 + 1]);
            }
            for(i1 = 0; i1 < mm1 - 1; i1++)
            {
                u[(2 * i3 + 1) * m2lt * m1lt + 2 * i2 * m1lt + 2 * i1] = u[(2 * i3 + 1) * m2lt * m1lt + 2 * i2 * m1lt + 2 * i1] + 0.5 * z2[i1];
                u[(2 * i3 + 1) * m2lt * m1lt + 2 * i2 * m1lt +(2 * i1 + 1)] = u[(2 * i3 + 1) * m2lt * m1lt + 2 * i2 * m1lt +(2 * i1 + 1)] + 0.25 *(z2[i1] + z2[i1 + 1]);
            }
            for(i1 = 0; i1 < mm1 - 1; i1++)
            {
                u[(2 * i3 + 1) * m2lt * m1lt +(2 * i2 + 1) * m1lt + 2 * i1] = u[(2 * i3 + 1) * m2lt * m1lt +(2 * i2 + 1) * m1lt + 2 * i1] + 0.25 * z3[i1];
                u[(2 * i3 + 1) * m2lt * m1lt +(2 * i2 + 1) * m1lt +(2 * i1 + 1)] = u[(2 * i3 + 1) * m2lt * m1lt +(2 * i2 + 1) * m1lt +(2 * i1 + 1)] + 0.125 *(z3[i1] + z3[i1 + 1]);
            }
        }
    }

#pragma endscop
}
