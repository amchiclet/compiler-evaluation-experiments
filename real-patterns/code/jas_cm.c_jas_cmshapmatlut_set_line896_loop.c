#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef double jas_cmreal_t;
typedef struct
{
    jas_cmreal_t *data;
    int size;
} jas_cmshapmatlut_t;
extern jas_cmshapmatlut_t * restrict lut;
typedef unsigned long uint_fast32_t;
typedef uint_fast32_t jas_iccuint32_t;
typedef unsigned long uint_fast16_t;
typedef uint_fast16_t jas_iccuint16_t;
typedef struct
{
    jas_iccuint32_t numents;
    jas_iccuint16_t *ents;
} jas_icccurv_t;
extern jas_icccurv_t * restrict curv;

void loop()
{
#pragma scop

    for(i = 0; i < lut -> size; ++i)
    {
        lut -> data[i] = curv -> ents[i] / 65535.0;
    }

#pragma endscop
}
