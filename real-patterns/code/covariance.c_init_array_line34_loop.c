#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern double  data[1400 + 0][1200 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < 1400; i++) for(j = 0; j < 1200; j++) data[i][j] =((double )i) * j / 1200;

#pragma endscop
}
