#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
typedef double float64;
typedef float64 frame_t;
extern frame_t xt;
extern frame_t * restrict x;
extern int k;

void loop()
{
#pragma scop

    for(i = 0; i < n - 1; ++i)
    {
        if(i < j)
        {
            xt = x[j];
            x[j] = x[i];
            x[i] = xt;
        }
        k = n / 2;
        while(k <= j)
        {
            j -= k;
            k /= 2;
        }
        j += k;
    }

#pragma endscop
}
