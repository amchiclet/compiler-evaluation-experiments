#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef int int32;
extern int32 in_len;
typedef double float64;
typedef float64 frame_t;
extern frame_t mean;
extern frame_t * restrict in;

void loop()
{
#pragma scop

    for(i = 0; i < in_len; i++) mean += in[i];

#pragma endscop
}
