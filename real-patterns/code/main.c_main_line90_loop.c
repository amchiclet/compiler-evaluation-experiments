#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef struct
{
    int width;
    int height;
    float data[];
} F2D;
extern F2D * restrict s;
extern int j;
extern F2D * restrict u;
extern F2D * restrict v;

void loop()
{
#pragma scop

    for(i = 0; i < s -> width; i++)
    {
        for(j = 0; j < u -> height; j++) u -> data[j * u -> width + i] = u -> data[j * u -> width + i] * s -> data[0 * s -> width + i];
        for(j = 0; j < v -> height; j++) v -> data[j * v -> width + i] = v -> data[j * v -> width + i] * s -> data[0 * s -> width + i];
    }

#pragma endscop
}
