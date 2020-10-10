#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int no_of_outputs;
extern int field_number;
extern int * restrict output_field_index;
extern int output_classes;
extern float  outputs[1024] ;
extern float value;
extern int k;
extern int network_outputs;

void loop()
{
#pragma scop

    for(j = 0; j < no_of_outputs; j++)
    {
        if(field_number == output_field_index[j])
        {
            if(j < 1024 - 1)
            {
                if(output_classes <= 0)
                {
                    outputs[j] = value;
                }
                else
                {
                    for(k = 0; k < network_outputs; k++)
                    {
                        if(k !=((int )value))
                        {
                            outputs[k] = 0.25f;
                        }
                        else
                        {
                            outputs[k] = 0.75f;
                        }
                    }
                }
                break;
            }
        }
    }

#pragma endscop
}
