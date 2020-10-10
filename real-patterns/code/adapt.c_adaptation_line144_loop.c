#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int miel;
extern int nelt;
extern int iel;
extern int  mt_to_id[2400] ;
extern int  id_to_mt[2400] ;

void loop()
{
#pragma scop

    for(miel = 0; miel < nelt; miel++)
    {
        iel = mt_to_id[miel];
        id_to_mt[iel] = miel;
    }

#pragma endscop
}
