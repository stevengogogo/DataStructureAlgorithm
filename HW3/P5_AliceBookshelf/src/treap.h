/**
 * @file treap.h
 * @author Shao-Ting Chiu
 * @brief Implicit Treap Implementation
 * @version 0.1
 * @date 2021-05-30
 * @note This code inspired by https://github.com/radoslav11/Implicit-treap/blob/master/implicit_treap.cpp
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TREAP_H
#define TREAP_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

#define MAX_NODE 1600000
#define LEFT 0
#define RIGHT 1


/**
 * @brief 
 * @param key implicit key
 * @param priority
 * @param rev revert flat
 * @param size nodes below and including it
 * @param parent 
 * @param leaf 0: left; 1: right; 2 Parent
 */
typedef struct node {
    int pt;//for heap arrangement
    int key;//book position [implicit]
    int rev; //reverse
    int lazy;//waiting operation
    int size;//number of nodes under it
    int val; // book priority
    int max;
    int sum; // summation under the node
    struct node *parent;
    struct node *leaf[2];
} tnode;



/***Problem Setup***/
tnode* build_treap(int* p, int len);

/****Main Operation****/
void Insert(tnode**t, int prior, int pos);
void Delete(tnode**t, int k);
void Increase(tnode*t, int pL, int pR, int priorD);
/** Return largest element in interval [l,r]*/
int QueryLargest(tnode*t, int l , int r);
void Reverse(tnode**t, int l, int r);
void Remove(tnode**t);

/**Helper function**/
void _Insert(tnode**t, int prior, int pos);
void _Insert_at_start(tnode**t, int prior);
tnode* setNewNode(int p);
int get_val_at_pos(tnode* t, int pos);
int get_node_pos(tnode* ncur, tnode* leaf);
tnode* find_largest_minpos(tnode* t);
// Memory Management
void init_nodes();
void clear_nodes();


/****Treap Operation****/

/** Update the revert flag*/
void push(tnode* t);
void reset(tnode* t);
void combine(tnode** t, tnode* l, tnode* r);
// Split and Merge
void split(tnode* t, tnode** lt, tnode** rt, int key, int add);

/**
 * @brief Merge two treaps. Assume all kets in rt > lt
 * @param t new root
 * @param lt treap with smaller keys
 * @param rt treap with larger keys
 */
void merge(tnode** t, tnode* lt, tnode* rt);


//node info
int size(tnode* t);

//update
void updateRoot(tnode* t);
/** Link parent of t's leaves to t.*/
void UpdateLeafParent(tnode* t);
/** Update number of nodes below t (including t)*/
void UpdateSize(tnode* t);
void Operate(tnode** t);

//utils
void swapTnode(tnode** a, tnode** b);

static void print_tree_q(tnode* t, int len){
    int val;
    for(int i=0;i<len;i++){
        val = get_val_at_pos(t, i);
        printf("%d ", val);
    }
}

#endif