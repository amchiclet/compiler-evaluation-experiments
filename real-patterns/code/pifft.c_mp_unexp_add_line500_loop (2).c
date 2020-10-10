#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int x;
extern int* restrict in1;
extern int* restrict in2;
extern int carry;
extern int radix;
extern int* restrict out;

void loop()
{
#pragma scop

    for(j = n - 1; j > 0; j--)
    {
        x = in1[j - 1] + in2[j - 1] - carry;
        carry =(x >= radix?- 1 : 0);
        out[j] = x -(radix & carry);
    }

#pragma endscop
}
