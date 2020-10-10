#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int y;
extern int n;
extern int x;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff * restrict chroma_pred;
extern int cpstride;
extern od_coeff * restrict decoded_luma;
extern int dlstride;

void loop()
{
#pragma scop

    for(y = 0; y < n; y++)
    {
        for(x = 0; x < n; x++)
        {
            chroma_pred[y * cpstride + x] = decoded_luma[y * dlstride + x];
        }
    }

#pragma endscop
}
