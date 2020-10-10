#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int neuron;
extern int NNTOT;
typedef float real;
extern real * restrict tempvecC;
extern int ** restrict vectors;
extern int vec;
extern int ** restrict newvectors;
extern real n;
enum WFALSE_enum {WFALSE=0,WTRUE=1};;
typedef enum WFALSE_enum wbool;
extern wbool status;

void loop()
{
#pragma scop

    for(neuron = 0; neuron < NNTOT; ++neuron) if((tempvecC[neuron] =((real )(vectors[vec][neuron] - newvectors[vec][neuron])) * n) != 0.0) status = WFALSE;

#pragma endscop
}
