#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int i;
extern int error;
extern int  b[10][10] ;

void loop()
{
#pragma scop

    for(j = 0; j < 10; j++) for(i = 0; i < 10; i++) if(i != j) error +=(b[j][i] >= 0?b[j][i] : -b[j][i]);

#pragma endscop
}
