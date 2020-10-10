#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int alphaSize;
extern int j;
extern int k;
extern int  parent[258 * 2] ;
extern unsigned char * restrict len;
extern int maxLen;
extern unsigned char tooLong;

void loop()
{
#pragma scop

    for(i = 1; i <= alphaSize; i++)
    {
        j = 0;
        k = i;
        while(parent[k] >= 0)
        {
            k = parent[k];
            j++;
        }
        len[i - 1] = j;
        if(j > maxLen) tooLong = 1;
    }

#pragma endscop
}
