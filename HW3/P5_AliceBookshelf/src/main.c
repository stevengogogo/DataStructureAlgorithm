#include <stdio.h>
#include <stdlib.h>
#include "treap.h"
#include <time.h>
#include <assert.h>
#include "PriorityTree.h"

static int* gen_vec_rand(int len){
    srand(time(NULL));   
    int r = rand() % 100;    
    int* ps = (int*)malloc(len*sizeof(int));

    for(int i=0;i<len;i++){
        r = rand() % 100;
        ps[i] = r;
    }

    return ps;
}

static int max_vec(int* ps, int a, int b){
    int MAX= ps[0];
    for(int i=a;i<=b;i++){
        if(MAX<ps[i]){
            MAX = ps[i];
        }
    }
    return MAX;
}

static int print_vec(int* ps, int len){
    for(int i=0; i<len;i++){
        printf("%d", ps[i]);
        if(i!=len-1){
            printf(",");
        }
    }
}


int main()
{   
    /*
    init_nodes();
    //Build tree
    int p[] = {2,1,-2,3,14,-12,2,2,30000,2,2};
    int len = sizeof(p)/sizeof(p[0]);
    tnode* t = build_treap(p, len);
    int max = QueryLargest(t,0,len-1);

    //TEST_CHECK(max == 30000);
    //TEST_MSG("Got: %d", max);

    clear_nodes();
    */
    interface_arr();
    return 0;
}