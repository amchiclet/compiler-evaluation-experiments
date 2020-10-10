#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int row;
extern int numRows;
extern int * restrict xfeeds_in_row;
extern int est_fds;
extern int value;
extern int * restrict feeds_in_row;
extern int fdWidth;
extern int binWidth;

void loop()
{
#pragma scop

    for(row = 1; row <= numRows; row++)
    {
        if(xfeeds_in_row[row] > 0)
        {
            est_fds += xfeeds_in_row[row];
        }
        value = feeds_in_row[row] * fdWidth / binWidth;
        if(feeds_in_row[row] > 0)
        {
            feeds_in_row[row] = 1 + value;
        }
        else
        {
            feeds_in_row[row] = 0;
        }
    }

#pragma endscop
}
