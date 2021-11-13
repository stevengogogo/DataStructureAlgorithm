#ifndef PRIORITYTREE_H
#define PRIORITYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include "treap.h"
#include "array.h"
#include "utils.h"

// Problem Setup
static void interface(void){
    init_nodes();
    int N=0;
    int Q=0;
    int res;
    int op;
    int prior,k,l,r;
    int num_node;
    //Setup N/Q
    scanf("%d%d",&N, &Q);
    num_node = N;
    
    //Set initial priorities
    int* p = (int*)malloc(N*sizeof(int));
    for(int i=0;i<N;i++)
        scanf("%d", &p[i]);

    //Inital Treap
    tnode* t = build_treap(p, N);

    //Operation
    for(int i=0;i<Q;i++){
        scanf("%d", &op);
        if(op == 1){
            scanf("%d", &prior);
            scanf("%d", &k);
            Insert(&t, prior, k-1);
            ++num_node;
        }
        else if(op==2){
            scanf("%d", &k);
            Delete(&t, k-1);
            --num_node;
        }
        else if(op==3){
            scanf("%d", &l);
            scanf("%d", &r);
            scanf("%d", &prior);
            Increase(t, l-1, r-1, prior);
        }
        else if(op==4){
            scanf("%d", &l);
            scanf("%d", &r);
            res = QueryLargest(t, l-1 ,r-1);
            printf("%d", res);
            printf("\n");
        }
        else if(op==5){
            scanf("%d", &l);
            scanf("%d", &r);
            Reverse(&t, l-1 ,r-1);
        }
        else if(op==6){
            Remove(&t);
            --num_node;
        }
        else{//Error
            clear_nodes();
        }
    }

    clear_nodes();
}


static void interface_arr(void){
    init_nodes();
    int N=0;
    int Q=0;
    int res;
    int op;
    int prior,k,l,r;
    int num_node;
    //Setup N/Q
    scanf("%d%d",&N, &Q);
    num_node = N;
    
    //Set initial priorities
    int* p = (int*)malloc(N*sizeof(int));
    for(int i=0;i<N;i++)
        scanf("%d", &p[i]);

    //Inital Treap
    array t = create_array(MAX_NODE);
    Build_arr(&t, p, N);

    //Operation
    for(int i=0;i<Q;i++){
        scanf("%d", &op);
        if(op == 1){
            scanf("%d", &prior);
            scanf("%d", &k);
            Insert_arr(&t, prior, k);
            ++num_node;
        }
        else if(op==2){
            scanf("%d", &k);
            Delete_arr(&t, k);
            --num_node;
        }
        else if(op==3){
            scanf("%d", &l);
            scanf("%d", &r);
            scanf("%d", &prior);
            Increase_arr(&t, l, r, prior);
        }
        else if(op==4){
            scanf("%d", &l);
            scanf("%d", &r);
            res = QueryLargest_arr(&t, l ,r);
            printf("%d", res);
            printf("\n");
        }
        else if(op==5){
            scanf("%d", &l);
            scanf("%d", &r);
            Reverse_arr(&t, l ,r);
        }
        else if(op==6){
            Remove_arr(&t);
            --num_node;
        }
        else{//Error
            clear_nodes();
           
        }
    }

    clear_nodes();
}



#endif