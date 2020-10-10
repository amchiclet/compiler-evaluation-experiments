#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern long I;
extern long N7;
extern double X;
extern double T;
extern double T2;
extern double Y;

void loop()
{
#pragma scop

    for(I = 1; I <= N7; I++)
    {
        X = T * atan(T2 * sin(X) * cos(X) /(cos(X + Y) + cos(X - Y) - 1.0));
        Y = T * atan(T2 * sin(Y) * cos(Y) /(cos(X + Y) + cos(X - Y) - 1.0));
    }

#pragma endscop
}
