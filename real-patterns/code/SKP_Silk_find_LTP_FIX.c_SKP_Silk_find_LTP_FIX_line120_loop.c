#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int WLTP_max;
extern int * restrict WLTP_ptr;

void loop()
{
#pragma scop

    for(i = 0; i < 5 * 5; i++)
    {
        WLTP_max =(WLTP_ptr[i] > WLTP_max?WLTP_ptr[i] : WLTP_max);
    }

#pragma endscop
}
