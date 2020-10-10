#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int u;
extern int n;
typedef int32_t od_coeff;
extern od_coeff  x[(1 << 2 + 5 - 1) * 2][(1 << 2 + 5 - 1) * 2] ;
extern int v;
typedef int int32_t;
extern od_coeff  y[64 * 2] ;

void loop()
{
#pragma scop

    for(u = 0; u < n * 2; u++) x[u][v] = y[u];

#pragma endscop
}
