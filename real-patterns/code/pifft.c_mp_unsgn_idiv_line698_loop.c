#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int shift;
extern double x;
extern int* restrict in1;
extern double dradix;
extern int carry;
extern int ix;
extern double d1_in2;
extern double din2;
extern int* restrict out;

void loop()
{
#pragma scop

    for(j = 2; j <= n - shift; j++)
    {
        x = in1[j + shift] + dradix * carry + 0.5;
        ix =((int )(d1_in2 * x));
        carry =((int )(x - din2 * ix));
        out[j] = ix;
    }

#pragma endscop
}
