#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef int int32;
extern int32 in_len;
typedef double float64;
typedef float64 window_t;
extern window_t * restrict in;

void loop()
{
#pragma scop

    for(i = 0; i < in_len / 2; i++)
    {
        float64 hamm;
        hamm = 0.54 - 0.46 * cos(2 * 3.14159265358979323846 * i /(((float64 )in_len) - 1.0));
        in[i] = hamm;
    }

#pragma endscop
}
