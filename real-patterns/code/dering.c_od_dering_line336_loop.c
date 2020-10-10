#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nvb;
extern int bsize;
extern int j;
extern int nhb;
typedef short int16_t;
extern int16_t * restrict in;
extern int16_t * restrict y;
extern int ystride;

void loop()
{
#pragma scop

    for(i = 0; i < nvb << bsize; i++)
    {
        for(j = 0; j < nhb << bsize; j++)
        {
            in[i *((1 << 2 + 5 - 1) + 2 * 3) + j] = y[i * ystride + j];
        }
    }

#pragma endscop
}
