#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef unsigned long long uint64;
extern uint64 b;
extern uint64 b1;
extern uint64 bo;
extern uint64 b2;
extern float mod;
extern int off;
extern int i;
extern uint64 C4VERT;
extern int value;
extern int j;
extern uint64 C4HORIZ;
extern uint64 C4UP_R;
extern uint64 C4UP_L;
extern uint64 C3VERT;
extern uint64 C3HORIZ;
extern uint64 C3UP_R;
extern uint64 C3UP_L;
extern uint64 C2VERT;
extern uint64 C2HORIZ;
extern uint64 C2UP_R;
extern uint64 C2UP_L;

void loop()
{
#pragma scop

    for(k = 0; k < 2; k++)
    {
        if(k == 0)
        {
            b = b1;
            bo = b2;
            mod =(- 1) +((float )off) / '\n';
        }
        else
        {
            b = b2;
            bo = b1;
            mod = 1 +((float )off) / '\n';
        }
        for(i = 0; i <(6 - 3) * 7; i++)
        {
            if((b & C4VERT << i) == C4VERT << i) value +=((int )1000) * mod;
        }
        for(i = 0; i < 6; i++)
        {
            for(j = 0; j < 7 - 3; j++)
            {
                if((b & C4HORIZ << j + i * 6) == C4HORIZ << j + i * 6) value +=((int )1000) * mod;
            }
        }
        for(i = 0; i < 6 - 3; i++)
        {
            for(j = 0; j < 7 - 3; j++)
            {
                if((b & C4UP_R << j + i * 6) == C4UP_R << j + i * 6) value +=((int )1000) * mod;
            }
        }
        for(i = 0; i < 6 - 3; i++)
        {
            for(j = 0; j < 7 - 3; j++)
            {
                if((b & C4UP_L << j + i * 6) == C4UP_L << j + i * 6) value +=((int )1000) * mod;
            }
        }
        for(i = 0; i <(6 - 3) * 7; i++)
        {
            if((b & C3VERT << i) == C3VERT << i && !(bo & C4VERT << i)) value +=((int )20) * mod;
        }
        for(i = 0; i < 6; i++)
        {
            for(j = 0; j < 7 - 2; j++)
            {
                if((b & C3HORIZ << j + i * 6) == C3HORIZ << j + i * 6) value +=((int )20) * mod;
            }
        }
        for(i = 0; i < 6 - 3; i++)
        {
            for(j = 0; j < 7 - 3; j++)
            {
                if((b & C3UP_R << j + i * 6) == C3UP_R << j + i * 6) value +=((int )20) * mod;
            }
        }
        for(i = 0; i < 6 - 3; i++)
        {
            for(j = 0; j < 7 - 3; j++)
            {
                if((b & C3UP_L << j + i * 6) == C3UP_L << j + i * 6) value +=((int )20) * mod;
            }
        }
        for(i = 0; i <(6 - 3) * 7; i++)
        {
            if((b & C2VERT << i) == C2VERT << i && !(bo & C4VERT << i)) value +=((int )5) * mod;
        }
        for(i = 0; i < 6; i++)
        {
            for(j = 0; j < 7 - 1; j++)
            {
                if((b & C2HORIZ << j + i * 6) == C2HORIZ << j + i * 6) value +=((int )5) * mod;
            }
        }
        for(i = 0; i < 6 - 3; i++)
        {
            for(j = 0; j < 7 - 3; j++)
            {
                if((b & C2UP_R << j + i * 6) == C2UP_R << j + i * 6) value +=((int )5) * mod;
            }
        }
        for(i = 0; i < 6 - 3; i++)
        {
            for(j = 0; j < 7 - 3; j++)
            {
                if((b & C2UP_L << j + i * 6) == C2UP_L << j + i * 6) value +=((int )5) * mod;
            }
        }
    }

#pragma endscop
}
