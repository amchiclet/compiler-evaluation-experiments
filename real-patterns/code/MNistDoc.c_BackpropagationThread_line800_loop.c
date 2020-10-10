#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
extern double  inputVector[841] ;

void loop()
{
#pragma scop

    for(ii = 0; ii < 841; ++ii)
    {
        inputVector[ii] = 1.0;
    }

#pragma endscop
}
