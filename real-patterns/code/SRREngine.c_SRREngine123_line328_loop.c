#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern double ** restrict A00;
extern double  TikReg[4 * 4][4 * 4] ;

void loop()
{
#pragma scop

    for(i = 0; i < 4 * 4; i++) for(j = 0; j < 4 * 4; j++) A00[i][j] += TikReg[i][j];

#pragma endscop
}
