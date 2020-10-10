#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern double  average[4] ;
extern long Section;
extern double  LoopSpeed[3][25] ;
extern double  harmonic[4] ;
extern double  geometric[4] ;
extern long  xspan[4] ;
extern long  Nspan[3][25] ;
extern double  minimum[4] ;
extern double  maximum[4] ;

void loop()
{
#pragma scop

    for(k = 1; k <= 24; k++)
    {
        average[Section] = average[Section] + LoopSpeed[Section][k];
        harmonic[Section] = harmonic[Section] + 1 / LoopSpeed[Section][k];
        geometric[Section] = geometric[Section] + log(LoopSpeed[Section][k]);
        xspan[Section] = xspan[Section] + Nspan[Section][k];
        if(LoopSpeed[Section][k] < minimum[Section])
        {
            minimum[Section] = LoopSpeed[Section][k];
        }
        if(LoopSpeed[Section][k] > maximum[Section])
        {
            maximum[Section] = LoopSpeed[Section][k];
        }
    }

#pragma endscop
}
