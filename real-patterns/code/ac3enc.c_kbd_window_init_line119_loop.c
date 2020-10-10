#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int n2;
extern double  window[256] ;
extern double  kwindow[256] ;

void loop()
{
#pragma scop

    for(k = 1; k < n2; k++)
    {
        window[k] = window[k - 1] + kwindow[k];
    }

#pragma endscop
}
