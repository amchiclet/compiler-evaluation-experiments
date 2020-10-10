#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int alphaSize;
extern int  parent[258 * 2] ;
extern int nHeap;
extern int  heap[258 + 2] ;
extern int  weight[258 * 2] ;

void loop()
{
#pragma scop

    for(i = 1; i <= alphaSize; i++)
    {
        parent[i] = - 1;
        nHeap++;
        heap[nHeap] = i;
        {
            int zz;
            int tmp;
            zz = nHeap;
            tmp = heap[zz];
            while(weight[tmp] < weight[heap[zz >> 1]])
            {
                heap[zz] = heap[zz >> 1];
                zz >>= 1;
            }
            heap[zz] = tmp;
        };
    }

#pragma endscop
}
