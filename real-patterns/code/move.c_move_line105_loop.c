#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int iel;
extern int nelt;
extern int  mt_to_id[2400] ;
extern int  id_to_mt[2400] ;

void loop()
{
#pragma scop

    for(iel = 0; iel < nelt; iel++)
    {
        mt_to_id[iel] = iel;
        id_to_mt[iel] = iel;
    }

#pragma endscop
}
