#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern long nn;
extern double dp;
extern double dkk;
extern double spin;
extern double per;
extern double dq;
extern double span;
extern long  Ix[1001] ;
extern long inset;
extern long Mmin;
extern long Mmax;
extern double qq;

void loop()
{
#pragma scop

    for(i = 0; i < nn; i++)
    {
        dp = dkk * spin;
        dkk = dp -((long )(dp / per)) * per;
        dq = dkk * span;
        Ix[i] = inset +((long )(dq / per));
        if(Ix[i] < Mmin | Ix[i] > Mmax)
        {
            Ix[i] = inset + i + 1 *((long )qq);
        }
    }

#pragma endscop
}
