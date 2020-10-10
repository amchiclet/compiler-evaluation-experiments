#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern uint8_t  check_basis[388][128 + 1][64 * 2][135 / 8] ;
extern int n;
extern int v;
extern int i;
extern int j;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef int32_t od_coeff;
extern int(* restrict od_dct_check_min);
extern int(* restrict od_dct_check_max);

void loop()
{
#pragma scop

    for(k = 133; k < 388; k++)
    {
        check_basis[k][n + v -(n >> 1)][i][j >> 3] =((uint8_t )(check_basis[k][n + v -(n >> 1)][i][j >> 3] & ~(1 <<(j & 7)) | !(!(od_dct_check_min[k] < -od_dct_check_max[k])) <<(j & 7)));
    }

#pragma endscop
}
