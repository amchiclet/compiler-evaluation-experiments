#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
extern int i;
extern double  a[200 * 200] ;

void loop()
{
#pragma scop

    for(j = 0; j < n; j++)
    {
        for(i = 0; i < n; i++)
        {
            if(i == j)
            {
                a[i + j * n] = - 2.0;
            }
            else if(i == j + 1 || i == j - 1)
            {
                a[i + j * n] = 1.0;
            }
            else
            {
                a[i + j * n] = 0.0;
            }
        }
    }

#pragma endscop
}
