#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long l;
extern long m;
extern long nn;
extern long j;
extern long k;
extern double ss;
extern double  Plan[300] ;
extern double rr;
extern long  Zone[301] ;

void loop()
{
#pragma scop

    for(l = 1; l <= 2; l++)
    {
        m =(nn + nn) *(l - 1);
        for(j = 1; j <= 2; j++)
        {
            for(k = 1; k <= nn; k++)
            {
                m = m + 1;
                ss =((double )k);
                Plan[m - 1] = rr *((ss + 1.0) / ss);
                Zone[m - 1] = k + k;
            }
        }
    }

#pragma endscop
}
