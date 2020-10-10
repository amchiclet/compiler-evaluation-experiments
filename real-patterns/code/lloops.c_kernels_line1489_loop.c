#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long j;
extern long k;
extern long Inner_loops;
extern double qa;
extern double  Za[7][101] ;
extern double  Zr[7][101] ;
extern double  Zb[7][101] ;
extern double  Zu[7][101] ;
extern double  Zv[7][101] ;
extern double  Zz[7][101] ;

void loop()
{
#pragma scop

    for(j = 1; j < 6; j++)
    {
        for(k = 1; k < Inner_loops; k++)
        {
            qa = Za[j + 1][k] * Zr[j][k] + Za[j - 1][k] * Zb[j][k] + Za[j][k + 1] * Zu[j][k] + Za[j][k - 1] * Zv[j][k] + Zz[j][k];
            Za[j][k] += 0.175 *(qa - Za[j][k]);
        }
    }

#pragma endscop
}
