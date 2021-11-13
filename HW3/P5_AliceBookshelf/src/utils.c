#include "utils.h"

//Choose the bigger one
int argmax(int a, int b){
    if (b>a)
        return 1;
    else 
        return 0;
}

int max(int a, int b){
    return a>b ? a : b;
}

