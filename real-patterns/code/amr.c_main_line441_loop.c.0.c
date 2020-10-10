#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long j;
extern long n;
extern long i;
extern long jj;
extern double * __restrict__ out;
extern double weight[4 + 1][4 + 1];
extern double * __restrict__ in;
extern long ii;

void loop()
{
  int __j_0__ = j;
  int __i_1__ = i;
  int __jj_2__ = jj;
  int __ii_3__ = ii;
  
#pragma scop
  for (__j_0__ = 2; __j_0__ <= n - ((long )2) - 1; __j_0__ += 1) {
    for (__i_1__ = 2; __i_1__ <= n - ((long )2) - 1; __i_1__ += 1) {
      for (__jj_2__ = - 2; __jj_2__ <= 2; __jj_2__ += 1) {
        out[__i_1__ + __j_0__ * n] += weight[0 + 2][__jj_2__ + 2] * in[__i_1__ + (__j_0__ + __jj_2__) * n];
      }
      for (__ii_3__ = - 2; __ii_3__ <= ((long )0) - 1; __ii_3__ += 1) {
        out[__i_1__ + __j_0__ * n] += weight[__ii_3__ + 2][0 + 2] * in[(__i_1__ + __ii_3__) + __j_0__ * n];
      }
      for (__ii_3__ = 1; __ii_3__ <= 2; __ii_3__ += 1) {
        out[__i_1__ + __j_0__ * n] += weight[__ii_3__ + 2][0 + 2] * in[(__i_1__ + __ii_3__) + __j_0__ * n];
      }
    }
  }
  
#pragma endscop
  j = __j_0__;
  i = __i_1__;
  jj = __jj_2__;
  ii = __ii_3__;
}
