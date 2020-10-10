#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef int int32;
extern int32 j;
extern int32 fftsize;
typedef double float64;
typedef float64 powspec_t;
extern powspec_t * restrict spec;
typedef float64 frame_t;
extern frame_t * restrict fft;

void loop()
{
#pragma scop

    for(j = 1; j <= fftsize / 2; j++)
    {
        spec[j] = fft[j] * fft[j] + fft[fftsize - j] * fft[fftsize - j];
    }

#pragma endscop
}
