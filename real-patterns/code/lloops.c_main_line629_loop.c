#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern long Section;
extern long k;
extern double  average[4] ;
extern double  weight[3] ;
extern double  LoopSpeed[3][25] ;
extern double  harmonic[4] ;
extern double  geometric[4] ;
extern long  xspan[4] ;
extern long  Nspan[3][25] ;
extern double  minimum[4] ;
extern double  maximum[4] ;
extern double wt;

void loop()
{
#pragma scop

    for(Section = 0; Section < 3; Section++)
    {
        for(k = 1; k <= 24; k++)
        {
            average[3] = average[3] + weight[Section] * LoopSpeed[Section][k];
            harmonic[3] = harmonic[3] + weight[Section] / LoopSpeed[Section][k];
            geometric[3] = geometric[3] + weight[Section] * log(LoopSpeed[Section][k]);
            xspan[3] = xspan[3] +((long )weight[Section]) * Nspan[Section][k];
            if(LoopSpeed[Section][k] < minimum[3])
            {
                minimum[3] = LoopSpeed[Section][k];
            }
            if(LoopSpeed[Section][k] > maximum[3])
            {
                maximum[3] = LoopSpeed[Section][k];
            }
        }
        wt = wt + weight[Section];
    }

#pragma endscop
}
