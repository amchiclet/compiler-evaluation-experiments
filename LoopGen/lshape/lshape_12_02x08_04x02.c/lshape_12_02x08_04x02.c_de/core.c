#include <x86intrin.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>



int core(double v00[restrict 31999], double v01[restrict 31999], double v02[restrict 31999], double v03[restrict 31999], double v04[restrict 31999], double v05[restrict 31999], double v06[restrict 31999], double v07[restrict 31999], double v08[restrict 31999], double v09[restrict 31999], double v10[restrict 31999], double v11[restrict 1], double v12[restrict 1], double v13[restrict 1], double v14[restrict 1], double v15[restrict 1], double v16[restrict 1], double v17[restrict 1], double v18[restrict 1], double v19[restrict 1]) {

  for (int i = 0; i <= 31998; ++i) {
    v00[i] = ((((((v02[i] + v09[i]) + v00[i]) + v07[i]) + v01[i]) + v08[i]) + v05[i]) + v09[i];
    v01[i] = ((((((v10[i] + v07[i]) + v10[i]) + v01[i]) + v10[i]) + v05[i]) + v02[i]) + v08[i];
    ;
    ;
    ;
    v02[i] = v04[i] + v00[i];
    v03[i] = v09[i] + v05[i];
    v04[i] = v06[i] + v10[i];
    v05[i] = v09[i] + v09[i];
    ;
    ;
    ;
    ;
    ;
    ;
  }
  return 0;
}
