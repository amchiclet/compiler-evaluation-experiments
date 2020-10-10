#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int miel;
extern int nelt;
extern int iel;
extern int  mt_to_id_old[2400] ;
enum false_enum {false=0,true=1};;
typedef enum false_enum logical;
extern logical  skip[2400] ;
extern logical  ifcoa[2400] ;
extern int  action[2400] ;
extern int  front[2400] ;
extern int mielnew;
extern int  mt_to_id[2400] ;

void loop()
{
#pragma scop

    for(miel = 0; miel < nelt; miel++)
    {
        iel = mt_to_id_old[miel];
        if(!skip[iel])
        {
            if(ifcoa[miel])
            {
                action[front[miel] - 1] = miel;
                mielnew = miel -(front[miel] - 1) * 7;
            }
            else
            {
                mielnew = miel - front[miel] * 7;
            }
            mt_to_id[mielnew] = iel;
        }
    }

#pragma endscop
}
