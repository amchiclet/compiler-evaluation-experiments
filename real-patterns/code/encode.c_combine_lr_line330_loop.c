#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int sb;
extern int sblimit;
extern int sample;
extern int gr;
extern double  joint_sample[3][12][32] ;
extern double  sb_sample[2][3][12][32] ;

void loop()
{
#pragma scop

    for(sb = 0; sb < sblimit; ++sb) for(sample = 0; sample < 12; ++sample) for(gr = 0; gr < 3; ++gr) joint_sample[gr][sample][sb] = .5 *(sb_sample[0][gr][sample][sb] + sb_sample[1][gr][sample][sb]);

#pragma endscop
}
