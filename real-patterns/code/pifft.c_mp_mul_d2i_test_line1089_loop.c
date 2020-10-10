#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int nfft;
extern double x;
extern double d1_radix2;
extern double scale;
extern double* restrict din;
extern int carry;
extern int carry2;
extern int radix;
extern int carry1;
extern double err;

void loop()
{
#pragma scop

    for(j = nfft + 1; j > 1; j--)
    {
        x = d1_radix2 *(scale * din[j] + carry + 0.5);
        carry = carry2;
        carry2 =((int )x) - 1;
        x = radix *(x - carry2);
        carry1 =((int )x);
        x = radix *(x - carry1);
        carry += carry1;
        x = x - 0.5 -((int )x);
        if(x > err)
        {
            err = x;
        }
        else if(-x > err)
        {
            err = -x;
        }
    }

#pragma endscop
}
