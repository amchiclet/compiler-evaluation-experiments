#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern double  ten[1037][2] ;
extern int ind;
extern double temp;
extern int j_temp;
extern int  j1[1037][2] ;
extern int  j2[1037][2] ;
extern int  j3[1037][2] ;

void loop()
{
#pragma scop

    for(i = 0; i < m - 1; i++)
    {
        if(ten[i][ind] < ten[i + 1][ind])
        {
            temp = ten[i + 1][ind];
            ten[i + 1][ind] = ten[i][ind];
            ten[i][ind] = temp;
            j_temp = j1[i + 1][ind];
            j1[i + 1][ind] = j1[i][ind];
            j1[i][ind] = j_temp;
            j_temp = j2[i + 1][ind];
            j2[i + 1][ind] = j2[i][ind];
            j2[i][ind] = j_temp;
            j_temp = j3[i + 1][ind];
            j3[i + 1][ind] = j3[i][ind];
            j3[i][ind] = j_temp;
        }
        else
        {
            return ;
        }
    }

#pragma endscop
}
