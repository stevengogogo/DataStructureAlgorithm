#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "bigint.h"


bigint* newnumc(char* numb)
{
    //allocate storage for the bigint
    bigint* num = (bigint*)malloc(sizeof(bigint));

    int numbl = strlen(numb);
    int numbll = numbl-1;

    //allocate storage for the number, in the right length
    digit* out = (digit*)malloc(numbl);

    for(int i=0;i<numbl;i++)
    {
        out[i] = numb[numbll-i]  - CHARZERO_ABOVEINTZERO;
    }

    num->number = out;
    num->length = numbl;

    //return the new bigint 
    return num;
}