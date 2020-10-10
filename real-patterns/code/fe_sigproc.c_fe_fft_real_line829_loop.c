#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef double float64;
typedef float64 frame_t;
extern frame_t xt;
extern frame_t * restrict x;

void loop()
{
#pragma scop

    for(i = 0; i < n; i += 2)
    {
        xt = x[i];
        x[i] = xt + x[i + 1];
        x[i + 1] = xt - x[i + 1];
    }

#pragma endscop
}
