#include "utils.h"


int chooseMax(int a, int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}

int chooseMin(int a, int b){
    if(a<b){
        return a;
    }
    else{
        return b;
    }
}

int inBound(int comp, int min, int max){
    if (comp>min && comp<max){
        return 1;
    }
    else{
        return 0;
    }
}