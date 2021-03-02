#include <stdio.h>
#include <string.h>
#include "include/utils.h"

//Choose the bigger one
extm max(int* a, int* b)
{
    int big, arg;
    if (*a > *b)
    {
        big = *a; arg=0;
    }
    else if (*a<*b)
    {
         big = *b; arg=1;
    }
    else 
    {
        big = *a; arg=0;
    }

    extm val = {big, arg};

    return val;
}

extm min(int* a, int* b)
{
    extm val_max = max(a, b);

    int extreme;
    int arg;
    if (val_max.arg == 0) {
        extreme = *b;
        arg = 1;
    }
    else {
        extreme = *a;
        arg = 0;
    }
 

    extm val_min = {
       extreme,
       arg
    };


    return val_min;
}

/*Compare two string. if identical returns 0. otherwise, return 0*/
int striden(char* a, char* b){
    int diff;
    int len_sh = strcmp(a,b);

    if  (len_sh == 0) {
        diff = strncmp(a,b, strlen(a));
        return diff;
    }
    else{
        return len_sh;
    }
}