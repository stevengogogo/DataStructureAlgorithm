/**
 * @file utility.h
 * @brief Helper function for testing
 * @version 0.1
 * @date 2021-06-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef UTILITY_H
#define UTILITY_H

#include "treap.h"
#include "acutest.h"
#include "stdbool.h"
#include <time.h>

static void tree_validate(tnode* t, int* c){
    if (t==NULL)
        return;
    *c = *c + 1;
    for(int i=0;i<2;i++){
        if(t->leaf[i] != NULL){
            //Priority
            TEST_CHECK(t->pt >= t->leaf[i]->pt);
        }
    }

     //Key
    if (t->leaf[LEFT] != NULL){
        TEST_CHECK(t->pt >= t->leaf[LEFT]->pt);
        TEST_CHECK(t->key >= t->leaf[LEFT]->key);
        TEST_MSG("Root: %d;Left: %d", t->key, t->leaf[LEFT]->key);
    }

    if(t->leaf[RIGHT] != NULL){
        TEST_CHECK(t->pt >= t->leaf[RIGHT]->pt);
        TEST_CHECK(t->key <= t->leaf[RIGHT]->key);
        TEST_MSG("Root: %d;RIGHT: %d", t->key, t->leaf[RIGHT]->key);
    }

    tree_validate(t->leaf[0], c);
    tree_validate(t->leaf[1], c);
}

static void print_tree(tnode* t){
    if (t==NULL){
        return;
    }
    print_tree(t->leaf[0]);
    printf("%d ",t->val);
    print_tree(t->leaf[1]);
}

static void print_tree_by_query(tnode* t, int len){
    int val;
    for(int i=0;i<len;i++){
        val = get_val_at_pos(t, i);
        printf("%d ", val);
    }
}

static void check_heap(tnode* t){
     if (t==NULL){
        return;
    }

    check_heap(t->leaf[LEFT]);
    if(t->leaf[LEFT]!=NULL)
        TEST_CHECK(t->pt > t->leaf[LEFT]->pt);

    if(t->leaf[RIGHT]!=NULL)
        TEST_CHECK(t->pt > t->leaf[RIGHT]->pt);

    check_heap(t->leaf[RIGHT]);
}

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

#endif 