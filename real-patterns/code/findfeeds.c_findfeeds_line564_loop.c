#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int row;
extern int numRows;
extern int * restrict add_to_row;
extern int max_row_length;
extern int * restrict length_of_row;
extern int fdWidth;

void loop()
{
#pragma scop

    for(row = 1; row <= numRows; row++)
    {
        add_to_row[row] =(max_row_length - length_of_row[row]) / fdWidth;
        add_to_row[0] += add_to_row[row];
    }

#pragma endscop
}
