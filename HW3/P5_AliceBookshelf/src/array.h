#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

typedef struct{
    int* i;
    int len;
    int size;
} array;

static array create_array(int size){
    array a;
    a.i = (int*)malloc(size*sizeof(int));
    a.len = 0;
    a.size = size;
    return a;
}

static array kill_array(array* arr){
    free(arr->i);
    arr->len = 0;
    arr->size = 0;
}

static void Build_arr(array* arr, int* is, int len){
    for(int i=0;i<len;i++){
        arr->i[i+1] = is[i];
    }
    arr->len = len;
    assert(arr->len < arr->size);
}

static void Insert_arr(array* arr, int prior, int pos){
    ++arr->len;
    assert(arr->size>arr->len);
    
    for(int i = arr->len; i>pos+1; i--){
        arr->i[i] = arr->i[i-1];
    }
    arr->i[pos+1] = prior;
}

static void Delete_arr(array* arr, int k){
    for(int i=k; i<arr->len;i++){
        arr->i[i] = arr->i[i+1];
    }
    --arr->len;
}

static void Increase_arr(array* arr, int l, int r, int prior){
    for(int i=l;i<=r;i++){
        arr->i[i] += prior;
    }
}

static int QueryLargest_arr(array* arr, int l, int r){
    int max = arr->i[l];
    for(int  i=l;i<=r;i++){
        if(max<arr->i[i]){max = arr->i[i];}
    }
    return max;
}

static void Reverse_arr(array* arr, int l, int r){
    int temp;
    for(int i=l;i<= (l+r)/2;i++){
        temp = arr->i[l+ r-i];
        arr->i[l+r-i] = arr->i[i];
        arr->i[i] = temp;
    }
}

static void Remove_arr(array* arr){
    int argmax= 1;
    int max = arr->i[argmax];
    for(int  i=1;i<=arr->len;i++){
        if(max<arr->i[i]){max = arr->i[i];argmax=i;}
    }

    Delete_arr(arr, argmax);
}

static int compare_arr(array arr, int* comp){
    for(int i=0;i<arr.len;i++){
        if(arr.i[i+1] != comp[i]){
            return 0;
        }
    }
    return 1;
}

static void print_arr(array arr){
    for(int i=1;i<=arr.len;i++){
        printf("%d ", arr.i[i]);
    }
    printf("\n");
}


#endif