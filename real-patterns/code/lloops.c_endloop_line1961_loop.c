#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern long j;
extern long Inner_loops;
extern double  Zr[7][101] ;
extern double  Zr0[7][101] ;
extern double  Zu[7][101] ;
extern double  Zu0[7][101] ;
extern double  Zv[7][101] ;
extern double  Zv0[7][101] ;
extern double  Zz[7][101] ;
extern double  Zz0[7][101] ;

void loop()
{
#pragma scop

    for(i = 1; i < 6; i++)
    {
        for(j = 1; j < Inner_loops; j++)
        {
            Zr[i][j] = Zr0[i][j];
            Zu[i][j] = Zu0[i][j];
            Zv[i][j] = Zv0[i][j];
            Zz[i][j] = Zz0[i][j];
        }
    }

#pragma endscop
}
