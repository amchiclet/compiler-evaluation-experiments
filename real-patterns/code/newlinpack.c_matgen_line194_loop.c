#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int i;
typedef double REAL;
extern REAL * restrict b;
extern REAL * restrict a;
extern int lda;

void loop()
{
#pragma scop

    for(j = 0; j < n; j++) for(i = 0; i < n; i++) b[i] = b[i] + a[lda * j + i];

#pragma endscop
}
