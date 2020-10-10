#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nx;
extern int j;
extern int ny;
extern int ** restrict chany_occ;

void loop()
{
#pragma scop

    for(i = 0; i <= nx; i++) for(j = 1; j <= ny; j++) chany_occ[i][j] = 0;

#pragma endscop
}
