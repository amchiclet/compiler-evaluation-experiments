#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern int j;
extern float ** restrict symmat2;
extern float ** restrict symmat;

void loop()
{
#pragma scop

    for(i = 1; i <= m; i++)
    {
        for(j = 1; j <= m; j++)
        {
            symmat2[i][j] = symmat[i][j];
        }
    }

#pragma endscop
}
