#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern long j;
extern double  Zr0[7][101] ;
extern double  Zr[7][101] ;
extern double  Zu0[7][101] ;
extern double  Zu[7][101] ;
extern double  Zv0[7][101] ;
extern double  Zv[7][101] ;
extern double  Zz0[7][101] ;
extern double  Zz[7][101] ;
extern double  Za0[101][25] ;
extern double  Za[7][101] ;

void loop()
{
#pragma scop

    for(i = 0; i < 7; i++)
    {
        for(j = 0; j < 101; j++)
        {
            Zr0[i][j] = Zr[i][j];
            Zu0[i][j] = Zu[i][j];
            Zv0[i][j] = Zv[i][j];
            Zz0[i][j] = Zz[i][j];
            Za0[i][j] = Za[i][j];
        }
    }

#pragma endscop
}
