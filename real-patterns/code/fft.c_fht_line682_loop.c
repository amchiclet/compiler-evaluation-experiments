#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int kx;
extern double c1;
extern double t_c;
extern double s1;
extern double t_s;
extern double * restrict fn;
extern double * restrict fz;
extern double * restrict fi;
extern double * restrict gi;
extern int k1;
extern int k3;
extern int k2;
extern int k4;

void loop()
{
#pragma scop

    for(i = 1; i < kx; i++)
    {
        double c2;
        double s2;
        double t = c1;
        c1 = t * t_c - s1 * t_s;
        s1 = t * t_s + s1 * t_c;
        c2 = c1 * c1 - s1 * s1;
        s2 = 2 *(c1 * s1);
        fn = fz + 1024;
        fi = fz + i;
        gi = fz + k1 - i;
        do
        {
            double a;
            double b;
            double g0;
            double f0;
            double f1;
            double g1;
            double f2;
            double g2;
            double f3;
            double g3;
            b = s2 * fi[k1] - c2 * gi[k1];
            a = c2 * fi[k1] + s2 * gi[k1];
            f1 = fi[0] - a;
            f0 = fi[0] + a;
            g1 = gi[0] - b;
            g0 = gi[0] + b;
            b = s2 * fi[k3] - c2 * gi[k3];
            a = c2 * fi[k3] + s2 * gi[k3];
            f3 = fi[k2] - a;
            f2 = fi[k2] + a;
            g3 = gi[k2] - b;
            g2 = gi[k2] + b;
            b = s1 * f2 - c1 * g3;
            a = c1 * f2 + s1 * g3;
            fi[k2] = f0 - a;
            fi[0] = f0 + a;
            gi[k3] = g1 - b;
            gi[k1] = g1 + b;
            b = c1 * g2 - s1 * f3;
            a = s1 * g2 + c1 * f3;
            gi[k2] = g0 - a;
            gi[0] = g0 + a;
            fi[k3] = f1 - b;
            fi[k1] = f1 + b;
            gi += k4;
            fi += k4;
        }
        while(fi < fn);
    }

#pragma endscop
}
