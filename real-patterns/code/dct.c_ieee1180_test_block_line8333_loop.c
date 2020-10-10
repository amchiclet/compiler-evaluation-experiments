#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
typedef int32_t od_coeff;
extern od_coeff  testout[1 << 6][1 << 6] ;
extern od_coeff  refout[1 << 6][1 << 6] ;
extern long  sumerrs[1 << 2 + 5 - 1][1 << 2 + 5 - 1] ;
extern long  sumsqerrs[1 << 2 + 5 - 1][1 << 2 + 5 - 1] ;
extern int  maxerr[1 << 2 + 5 - 1][1 << 2 + 5 - 1] ;
extern int global_maxerr;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            int err;
            err = testout[i][j] - refout[i][j];
            sumerrs[i][j] += err;
            sumsqerrs[i][j] +=(err * err);
            if(err < 0) err = -err;
            maxerr[i][j] = maxerr[i][j] ^(maxerr[i][j] ^ err) & -(err > maxerr[i][j]);
            global_maxerr = global_maxerr ^(global_maxerr ^ err) & -(err > global_maxerr);
        }
    }

#pragma endscop
}
