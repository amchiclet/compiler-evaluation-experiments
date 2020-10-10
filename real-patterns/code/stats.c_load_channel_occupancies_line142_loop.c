#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nx;
extern int j;
extern int ny;
extern int ** restrict chanx_occ;

void loop()
{
#pragma scop

    for(i = 1; i <= nx; i++) for(j = 0; j <= ny; j++) chanx_occ[i][j] = 0;

#pragma endscop
}
