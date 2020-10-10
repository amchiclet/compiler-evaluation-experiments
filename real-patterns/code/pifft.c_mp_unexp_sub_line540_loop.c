#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int expdif;
extern int x;
extern int* restrict in1;
extern int* restrict in2;
extern int borrow;
extern int* restrict out;
extern int radix;

void loop()
{
#pragma scop

    for(j = n - 1; j >= expdif; j--)
    {
        x = in1[j] - in2[j - expdif] + borrow;
        borrow =(x < 0?- 1 : 0);
        out[j] = x +(radix & borrow);
    }

#pragma endscop
}
