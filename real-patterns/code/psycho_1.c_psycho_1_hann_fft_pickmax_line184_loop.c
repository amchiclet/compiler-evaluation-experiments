#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double  x_real[1024] ;
extern double  sample[1024] ;
extern double  window[1024] ;

void loop()
{
#pragma scop

    for(i = 0; i < 1024; i++) x_real[i] =((double )(sample[i] * window[i]));

#pragma endscop
}
