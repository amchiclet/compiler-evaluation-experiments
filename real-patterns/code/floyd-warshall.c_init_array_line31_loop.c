#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern int  path[2800 + 0][2800 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) for(j = 0; j < n; j++)
        {
            path[i][j] = i * j % 7 + 1;
            if((i + j) % 13 == 0 ||(i + j) % 7 == 0 ||(i + j) % 11 == 0) path[i][j] = 999;
        }

#pragma endscop
}
