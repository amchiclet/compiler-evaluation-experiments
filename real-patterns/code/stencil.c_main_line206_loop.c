#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern long n;
extern int i;
extern float * restrict out;

void loop()
{
#pragma scop

    for(j = 2; j < n - 2; j++) for(i = 2; i < n - 2; i++) out[i + j * n] =((float )0.0);

#pragma endscop
}
