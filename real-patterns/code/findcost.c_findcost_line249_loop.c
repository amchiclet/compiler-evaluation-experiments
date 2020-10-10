#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int net;
extern int numnets;
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
struct dimbox
{
    NBOXPTR netptr;
    char *name;
    char dflag;
    char feedflag;
    char ignore;
    int old_total;
    int new_total;
    int xmin;
    int newxmin;
    int xmax;
    int newxmax;
    int ymin;
    int newymin;
    int ymax;
    int newymax;
    short Lnum;
    short newLnum;
    short Rnum;
    short newRnum;
    short Bnum;
    short newBnum;
    short Tnum;
    short newTnum;
    short numpins;
    double Vweight;
    double Hweight;
};

typedef struct dimbox * DBOXPTR;
extern struct dimbox * restrict dimptr;
extern DBOXPTR * restrict netarray;
extern int  net_pin_num[11] ;

void loop()
{
#pragma scop

    for(net = 1; net <= numnets; net++)
    {
        dimptr = netarray[net];
        if((dimptr -> numpins) >= 10)
        {
            net_pin_num[10]++;
        }
        else
        {
            net_pin_num[dimptr -> numpins]++;
        }
    }

#pragma endscop
}
