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



int core(double v00[restrict 31999], double v01[restrict 31999], double v02[restrict 31999], double v03[restrict 31999], double v04[restrict 31999], double v05[restrict 31999], double v06[restrict 31999], double v07[restrict 31999], double v08[restrict 31999], double v09[restrict 31999], double v10[restrict 31999], double v11[restrict 31999], double v12[restrict 1], double v13[restrict 1], double v14[restrict 1], double v15[restrict 1], double v16[restrict 1], double v17[restrict 1], double v18[restrict 1], double v19[restrict 1]) {

  for (int i = 0; i <= 31998; ++i) {
    v00[i] = (((v01[i] + v03[i]) + v03[i]) + v02[i]) + v06[i];
    v01[i] = (((v01[i] + v05[i]) + v07[i]) + v11[i]) + v00[i];
    v02[i] = (((v07[i] + v06[i]) + v07[i]) + v01[i]) + v01[i];
    v03[i] = (((v02[i] + v06[i]) + v09[i]) + v08[i]) + v09[i];
    v04[i] = (((v09[i] + v03[i]) + v01[i]) + v10[i]) + v06[i];
    v05[i] = ((v06[i] + v01[i]) + v04[i]) + v05[i];
    v06[i] = ((v06[i] + v02[i]) + v04[i]) + v11[i];
    v07[i] = ((v08[i] + v02[i]) + v03[i]) + v00[i];
    v08[i] = ((v10[i] + v09[i]) + v07[i]) + v10[i];
    v09[i] = ((v09[i] + v09[i]) + v02[i]) + v04[i];
    v10[i] = ((v07[i] + v03[i]) + v06[i]) + v07[i];
    ;
    ;
    ;
    ;
  }
  return 0;
}
