#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int x;
extern int* restrict in;
extern int k;
extern int log10_radix;
extern int y;
extern char* restrict out;

void loop()
{
#pragma scop

    for(j = 3; j <= n + 1; j++)
    {
        x = in[j];
        for(k = log10_radix - 1; k >= 0; k--)
        {
            y = x % 10;
            x /= 10;
            out[k] =(48 + y);
        }
        out += log10_radix;
    }

#pragma endscop
}
