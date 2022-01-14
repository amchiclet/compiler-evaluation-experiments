#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern int scalar1;
extern int scalar2;
extern int scalar3;
extern int scalar4;
extern int scalar5;
extern int size;

int core(double Arr01[restrict 32000], double Arr02[restrict 32000], double Arr03[restrict 1], double Arr04[restrict 1], double Arr05[restrict 32000], double Arr06[restrict 1], double Arr07[restrict 32000], double Arr08[restrict 32000], double Arr09[restrict 32000], double Arr10[restrict 32000], double Arr11[restrict 32000], double Arr12[restrict 32000], double Arr13[restrict 32000], double Arr14[restrict 32000], double Arr15[restrict 32000], double Arr16[restrict 1], double Arr17[restrict 32000], double Arr18[restrict 1], double Arr19[restrict 1], double Arr20[restrict 1], double Arr21[restrict 1], double Arr22[restrict 1], double Arr23[restrict 1], double Arr24[restrict 1], double Arr25[restrict 1]) {

  for (int i = 0; i <= size - 1; ++i) {
    scalar2 = (scalar2 * Arr17[i] + Arr13[i] * Arr14[i]) + Arr09[i] * Arr10[i];
    scalar1 = (scalar1 * Arr10[i] + Arr01[i] * Arr14[i]) + Arr09[i] * Arr09[i];
    scalar5 = (scalar5 * Arr17[i] + Arr11[i] * Arr11[i]) + Arr07[i] * Arr14[i];
    scalar3 = (scalar3 * Arr05[i] + Arr01[i] * Arr17[i]) + Arr05[i] * Arr13[i];
    scalar4 = (scalar4 * Arr12[i] + Arr15[i] * Arr02[i]) + Arr14[i] * Arr08[i];
  }
  return 0;
}
