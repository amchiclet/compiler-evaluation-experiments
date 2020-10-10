#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef double REAL;
extern REAL * restrict dy;
extern REAL da;
extern REAL * restrict dx;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) dy[i] = dy[i] + da * dx[i];

#pragma endscop
}
