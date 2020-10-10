#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef struct hash
{
    char *hname;
    int hnum;
    struct hash *hnext;
}* HASHPTR;
extern HASHPTR * restrict hashtab;

void loop()
{
#pragma scop

    for(i = 0; i < 3001; i++)
    {
        hashtab[i] =((HASHPTR )((void *)0));
    }

#pragma endscop
}
