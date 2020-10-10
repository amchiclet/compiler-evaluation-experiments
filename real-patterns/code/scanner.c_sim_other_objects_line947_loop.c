#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int low;
extern int high;
extern int j;
extern int numf1s;
extern double ** restrict tds;
extern double ** restrict bus;

void loop()
{
#pragma scop

    for(i = low; i < high; i++)
    {
        for(j = 0; j < numf1s; j++)
        {
            if(i % low)
            {
                tds[j][i] = tds[j][0];
                tds[j][i] = bus[j][0];
            }
            else
            {
                tds[j][i] = tds[j][1];
                tds[j][i] = bus[j][1];
            }
        }
    }

#pragma endscop
}
