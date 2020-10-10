#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef double REAL;
extern REAL * restrict b;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) b[i] = 0.;

#pragma endscop
}
