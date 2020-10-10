#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int code;
extern int  base_dist[30] ;
extern int dist;
extern int n;
extern int  extra_dbits[30] ;
typedef unsigned char uch;
extern uch  dist_code[512] ;

void loop()
{
#pragma scop

    for(code = 0; code < 16; code++)
    {
        base_dist[code] = dist;
        for(n = 0; n < 1 << extra_dbits[code]; n++)
        {
            dist_code[dist++] =((uch )code);
        }
    }

#pragma endscop
}
