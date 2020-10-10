#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int u;
extern int n;
extern int v;
typedef int32_t od_coeff;
extern od_coeff  x[64 * 2][64 * 2] ;
extern int i;
extern int j;

void loop()
{
#pragma scop

    for(u = 0; u < n * 2; u++)
    {
        for(v = 0; v < n * 2; v++)
        {
            x[u][v] =(u == i && v == j) << 8 + 4;
        }
    }

#pragma endscop
}
