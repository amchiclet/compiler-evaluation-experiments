#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern double x;
extern double din2;
extern int* restrict in1;
extern int carry;
extern double d1_radix;
extern int* restrict out;
extern double dradix;

void loop()
{
#pragma scop

    for(j = n; j >= 1; j--)
    {
        x = din2 * in1[j] + carry + 0.5;
        carry =((int )(d1_radix * x));
        out[j] =((int )(x - dradix * carry));
    }

#pragma endscop
}
