#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
typedef float ieee754_float32_t;
extern ieee754_float32_t  log_table[512 + 1] ;

void loop()
{
#pragma scop

    for(j = 0; j < 512 + 1; j++) log_table[j] =(log((1.0f + j /((ieee754_float32_t )512))) / log(2.0f));

#pragma endscop
}
