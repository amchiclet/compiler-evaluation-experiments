#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int l;
struct feature_node
{
    int index;
    double value;
};

struct problem
{
    int l;
    int n;
    double *y;
    struct feature_node **x;
    double bias;
};

struct tagl2r_l2_svc_fun
{
    double *C;
    double *z;
    double *D;
    int *I;
    int sizeI;
    const struct problem *prob;
};

extern struct tagl2r_l2_svc_fun* restrict this;
extern double * restrict C;
extern double * restrict y;

void loop()
{
#pragma scop

    for(i = 0; i < l; i++) if(this -> z[i] < 1)
        {
            this -> z[this -> sizeI] = C[i] * y[i] *(this -> z[i] - 1);
            this -> I[this -> sizeI] = i;
            this -> sizeI++;
        }

#pragma endscop
}
