#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int term;
extern int pinctr;
typedef struct netbox
{
    struct netbox *nterm;
    int terminal;
    int extint;
    int xpos;
    int ypos;
    int newx;
    int newy;
    short row;
    short cell;
    short net;
    char pinloc;
    char unequiv;
    char flag;
    char layer;
}* NBOXPTR;
extern NBOXPTR * restrict tearray;

void loop()
{
#pragma scop

    for(term = 1; term <= pinctr; term++)
    {
        tearray[term] =((NBOXPTR )((void *)0));
    }

#pragma endscop
}
