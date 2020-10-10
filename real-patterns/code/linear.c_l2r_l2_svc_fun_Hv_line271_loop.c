#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
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
extern double * restrict wa;
extern int * restrict I;

void loop()
{
#pragma scop

    for(i = 0; i < this -> sizeI; i++) wa[i] = this -> C[I[i]] * wa[i];

#pragma endscop
}
