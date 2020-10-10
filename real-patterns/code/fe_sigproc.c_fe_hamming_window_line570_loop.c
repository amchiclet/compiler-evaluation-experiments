#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef int int32;
extern int32 in_len;
typedef double float64;
typedef float64 frame_t;
extern frame_t * restrict in;
typedef float64 window_t;
extern window_t * restrict window;

void loop()
{
#pragma scop

    for(i = 0; i < in_len / 2; i++)
    {
        in[i] = in[i] * window[i];
        in[in_len - 1 - i] = in[in_len - 1 - i] * window[i];
    }

#pragma endscop
}
