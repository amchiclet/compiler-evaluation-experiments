#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int nfft;
extern double xr;
extern double * __restrict__ din1;
extern double xi;
extern double yr;
extern double * __restrict__ din2;
extern double yi;
extern double * __restrict__ dinout;

void loop()
{
  int __j_0__ = j;
  
#pragma scop
  for (__j_0__ = 3; __j_0__ <= nfft - 1; __j_0__ += 2) {
    xr = din1[__j_0__];
    xi = din1[__j_0__ + 1];
    yr = din2[__j_0__];
    yi = din2[__j_0__ + 1];
    dinout[__j_0__] += xr * yr - xi * yi;
    dinout[__j_0__ + 1] += xr * yi + xi * yr;
  }
  
#pragma endscop
  j = __j_0__;
}
