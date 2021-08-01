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

extern int inner_loops;

int core(double Dex1[restrict 1001], double Dex12[restrict 1], double Ex1[restrict 1001], double Ex12[restrict 1], int Ir[restrict 1001], int Ir2[restrict 1001], double Rx[restrict 1001], double Rx2[restrict 1001], double Vx[restrict 1001], double Vx2[restrict 1001], double Xi[restrict 1001], double Xi2[restrict 1], double Xtra[restrict 40], double Xtra2[restrict 28], double Xx[restrict 1001], double Xx2[restrict 1001]) {

  for (int k = 0; k <= inner_loops; ++k) {
    Vx[k] = (Vx[k] + Ex1[k]) + (Xx[k] - Xi[k]) * Dex1[k];
    ;
    Xx[k] = (Xx[k] + Vx[k]) + Xtra[27];
    Xx2[k] = (Xx2[k] + Vx2[k]) + Xtra2[27];
    Ir[k] = Xx[k];
    ;
    Rx[k] = Xx[k] - Ir[k];
    ;
    Ir[k] = (Ir[k] & 2048 - 1) + 1;
    Ir2[k] = (Ir2[k] & 2048 - 1) + 1;
    Xx[k] = Rx[k] + Ir[k];
    Xx2[k] = Rx2[k] + Ir2[k];
  }
  return 0;
}
