#include "utils.h"


int* init_arr(int len){
    int* array = (int*)malloc(len*sizeof(int));
    return array;
}

void kill_arr(int* array){
    free(array);
}

void copy_arr(int* dst, int* src, int left, int right){
    int j = 0;
    for(int i=left; i<right;i++){
        dst[j] = src[i];
        ++j;
    }
}

int argmax(int n0, int n1){
    if (n1>n0)
        return n1;
    else 
        return n0;
}

void swap(int* a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int ChooseMax(int a, int b){
    if (a>b)
        return a;
    else 
        return b;
}

TriProb ParseData(char* filePath){
    FILE *fp;
    TriProb tp;

    fp = fopen(filePath, "r");
    assert(fp!=NULL);

    //Get length
    fscanf(fp, "%d", &tp.n); 

    tp.ps = (int*)malloc(tp.n*sizeof(int));
    tp.qs = (int*)malloc(tp.n*sizeof(int));
    tp.rs = (int*)malloc(tp.n*sizeof(int));

    for(int i=0;i<tp.n;i++){
        fscanf(fp, "%d", &tp.ps[i]); 
    }

    for(int i=0;i<tp.n;i++){
        fscanf(fp, "%d", &tp.qs[i]); 
    }

    for(int i=0;i<tp.n;i++){
        fscanf(fp, "%d", &tp.rs[i]); 
    }

    //Get Solution
    fscanf(fp, "%d", &tp.sol); 


    fclose(fp);

    return tp;
}

void int2str(int i, char *s) {
  sprintf(s,"%d",i);
}