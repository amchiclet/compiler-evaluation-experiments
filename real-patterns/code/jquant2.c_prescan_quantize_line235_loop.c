#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int row;
extern int num_rows;
typedef unsigned char JSAMPLE;
typedef JSAMPLE * JSAMPROW;
extern JSAMPROW restrict ptr;
typedef JSAMPROW * JSAMPARRAY;
extern JSAMPARRAY restrict input_buf;
typedef unsigned int JDIMENSION;
extern JDIMENSION col;
extern JDIMENSION width;
typedef unsigned short UINT16;
typedef UINT16 histcell;
typedef histcell * histptr;
extern histptr restrict histp;
typedef histcell  hist1d[1 << 5];
typedef hist1d * hist2d;
typedef hist2d * hist3d;
extern hist3d restrict histogram;

void loop()
{
#pragma scop

    for(row = 0; row < num_rows; row++)
    {
        ptr = input_buf[row];
        for(col = width; col > 0; col--)
        {
            histp = &histogram[((int )ptr[0]) >> 8 - 5][((int )ptr[1]) >> 8 - 6][((int )ptr[2]) >> 8 - 5];
            if((++ *histp) <= 0) ( *histp)--;
            ptr += 3;
        }
    }

#pragma endscop
}
