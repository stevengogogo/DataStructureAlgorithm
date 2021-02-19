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
    
}