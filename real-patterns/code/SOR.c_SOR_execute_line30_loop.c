#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int p;
extern int num_iterations;
extern int i;
extern int Mm1;
extern double * restrict Gi;
extern double ** restrict G;
extern double * restrict Gim1;
extern double * restrict Gip1;
extern int j;
extern int Nm1;
extern double omega_over_four;
extern double one_minus_omega;

void loop()
{
#pragma scop

    for(p = 0; p < num_iterations; p++)
    {
        for(i = 1; i < Mm1; i++)
        {
            Gi = G[i];
            Gim1 = G[i - 1];
            Gip1 = G[i + 1];
            for(j = 1; j < Nm1; j++) Gi[j] = omega_over_four *(Gim1[j] + Gip1[j] + Gi[j - 1] + Gi[j + 1]) + one_minus_omega * Gi[j];
        }
    }

#pragma endscop
}
