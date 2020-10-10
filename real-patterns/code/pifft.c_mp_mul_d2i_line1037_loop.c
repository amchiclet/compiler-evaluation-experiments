#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int ndata;
extern double x;
extern double d1_radix2;
extern double scale;
extern double* restrict din;
extern int shift;
extern int carry;
extern int carry2;
extern int radix;
extern int carry1;
extern int* restrict out;

void loop()
{
#pragma scop

    for(j = ndata; j > 1; j--)
    {
        x = d1_radix2 *(scale * din[j - shift] + carry + 0.5);
        carry = carry2;
        carry2 =((int )x) - 1;
        x = radix *(x - carry2);
        carry1 =((int )x);
        out[j + 1] =((int )(radix *(x - carry1)));
        carry += carry1;
    }

#pragma endscop
}
