#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern unsigned long i;
extern unsigned long len;
typedef unsigned char * POINTER;
extern POINTER restrict output;
extern int value;

void loop()
{
#pragma scop

    for(i = 0; i < len; i++) ((char *)output)[i] =((char )value);

#pragma endscop
}
