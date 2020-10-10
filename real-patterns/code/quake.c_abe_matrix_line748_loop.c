#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern int* restrict bv;
extern double* restrict Ce;
struct properties
{
    double cp;
    double cs;
    double den;
};

extern struct properties* restrict prop;
extern double area;

void loop()
{
#pragma scop

    for(i = 0; i < 3; i++)
    {
        j = 3 * bv[i];
        Ce[j] = Ce[j] + prop -> cs * prop -> den * area / 3.0;
        Ce[j + 1] = Ce[j + 1] + prop -> cs * prop -> den * area / 3.0;
        Ce[j + 2] = Ce[j + 2] + prop -> cp * prop -> den * area / 3.0;
    }

#pragma endscop
}
