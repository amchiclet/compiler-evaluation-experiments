#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern unsigned long i;
extern unsigned long len;
typedef unsigned char * POINTER;
extern POINTER restrict output;
extern POINTER restrict input;

void loop()
{
#pragma scop

    for(i = 0; i < len; i++) output[i] = input[i];

#pragma endscop
}
