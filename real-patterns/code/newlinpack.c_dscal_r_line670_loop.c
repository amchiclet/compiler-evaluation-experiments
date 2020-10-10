#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef double REAL;
extern REAL * restrict dx;
extern REAL da;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) dx[i] = da * dx[i];

#pragma endscop
}
