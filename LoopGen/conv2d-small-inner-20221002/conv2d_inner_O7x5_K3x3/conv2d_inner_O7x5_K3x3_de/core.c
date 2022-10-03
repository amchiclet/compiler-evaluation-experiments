#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern int IFM;
extern int IMG;
extern int OFM;
extern int SH;
extern int SW;

int core(double (*restrict filter)[5][5][3][3], double (*restrict input)[512][5][15][11], double (*restrict output)[512][5][7][5]) {

  for (int img = 0; img <= IMG - 1; img += 1) {
    for (int ifm = 0; ifm <= IFM - 1; ifm += 1) {
      for (int ofm = 0; ofm <= OFM - 1; ofm += 1) {
        for (int oj = 0; oj <= 7 - 1; oj += 1) {
          for (int oi = 0; oi <= 5 - 1; oi += 1) {
            for (int kj = 0; kj <= 3 - 1; kj += 1) {
              for (int ki = 0; ki <= 3 - 1; ki += 1) {
                (*input)[img][ifm][oj * SH + kj][oi * SW + ki] = (*input)[img][ifm][oj * SH + kj][oi * SW + ki] + (*output)[img][ofm][oj][oi] * (*filter)[ofm][ifm][kj][ki];
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
