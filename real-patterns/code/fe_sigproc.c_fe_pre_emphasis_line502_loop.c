#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef short int int16;
extern int i;
typedef int int32;
extern int32 len;
typedef double float64;
typedef float64 frame_t;
extern frame_t * restrict out;
extern int16 * restrict in;
typedef float float32;
extern float32 factor;

void loop()
{
#pragma scop

    for(i = 1; i < len; i++) out[i] =((frame_t )in[i]) -((frame_t )in[i - 1]) * factor;

#pragma endscop
}
