#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long jr;
extern long n_r_true;
extern double yr;
extern double h_r;
extern long jb;
extern long jrb;
extern long expand;
extern long jrb1;
extern double yb;
extern long ir;
extern double * __restrict__ ing_r;

void loop()
{
  int __jr_0__ = jr;
  int __ir_1__ = ir;
  
#pragma scop
  for (__jr_0__ = 0; __jr_0__ <= n_r_true - ((long )1) - 1; __jr_0__ += 1) {{
      yr = h_r * ((double )__jr_0__);
      jb = ((long )yr);
      jrb = jb * expand;
      jrb1 = (jb + 1) * expand;
      yb = ((double )jb);
    }
    for (__ir_1__ = 0; __ir_1__ <= n_r_true - 1; __ir_1__ += 1) {
      ing_r[__ir_1__ + __jr_0__ * n_r_true] = ing_r[__ir_1__ + jrb1 * n_r_true] * (yr - yb) + ing_r[__ir_1__ + jrb * n_r_true] * (yb + ((double )1.0) - yr);
    }
  }
  
#pragma endscop
  jr = __jr_0__;
  ir = __ir_1__;
}
