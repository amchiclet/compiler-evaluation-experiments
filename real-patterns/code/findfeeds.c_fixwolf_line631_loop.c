#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
struct netbox
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
};

typedef struct netbox * NBOXPTR;
struct termbox
{
    struct termbox *nextterm;
    NBOXPTR termptr;
    int cellterm;
    int ei;
    short net;
    short txpos[2];
    short typos[2];
    short ue;
};

typedef struct termbox * TEBOXPTR;
struct tilebox
{
    short left;
    short right;
    short bottom;
    short top;
    TEBOXPTR termsptr;
};

typedef struct tilebox * TIBOXPTR;
struct cellbox
{
    char *cname;
    char corient;
    char orflag;
    int cxcenter;
    int cycenter;
    short cclass;
    short cheight;
    short clength;
    short border;
    short cblock;
    short numterms;
    short padside;
    TIBOXPTR tileptr;
};

typedef struct cellbox * CBOXPTR;
extern CBOXPTR * restrict newarray;
extern CBOXPTR * restrict carray;

void loop()
{
#pragma scop

    for(i = 1; i <= n; i++)
    {
        newarray[i] = carray[i];
    }

#pragma endscop
}
