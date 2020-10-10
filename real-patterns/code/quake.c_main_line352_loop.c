#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int k;
extern double  vertices[4][3] ;
extern double ** restrict ARCHcoord;
extern int  cor[4] ;

void loop()
{
#pragma scop

    for(j = 0; j < 4; j++) for(k = 0; k < 3; k++) vertices[j][k] = ARCHcoord[cor[j]][k];

#pragma endscop
}
