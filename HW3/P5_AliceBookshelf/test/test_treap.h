/**
 * @file test_treap.h
 * @brief Test Treap operation
 * @version 0.1
 * @date 2021-06-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TEST_INSERT_H
#define TEST_INSERT_H

#include "treap.h"
#include "utility.h"
#include "acutest.h"

void test_build(void){
    init_nodes();

    int len = 10;
    int p[] = {7,2,1,2,4,-12,2,2,2,2};
    int EST;

    tnode* t = build_treap(p, len);
    TEST_CHECK(t!=NULL);
    //TEST_CHECK(t->leaf[RIGHT]!=NULL);
    //tree_validate(t, &c);
    //TEST_CHECK(c==4);
    //TEST_MSG("length: %d / REAL: %d", c, len);

    for(int i=0;i<len;i++){
        EST = get_val_at_pos(t, i);
        TEST_CHECK(EST == p[i]);
        TEST_MSG("Real: %d / EST: %d", p[i], EST);
    }

    //Heap Property
    check_heap(t);
    //Print Priorities
    print_tree(t);


    //Test largest
    int MAX = QueryLargest(t, 4, len);
    TEST_CHECK(MAX == 4);


    clear_nodes();
}

void test_insert_at_start(void){
    init_nodes();

    int len = 10;
    int n=100;
    int p[] = {7,2,1,2,4,-12,2,2,2,2};
    int EST;

    tnode* t = build_treap(p, len);

    Insert(&t, 99,1);
    int MAX = QueryLargest(t, 0, len);
    TEST_CHECK(MAX == 99);
    TEST_MSG("Got: %d; Real: %d", MAX, 99);

    Insert(&t, n, -1);
    print_tree_by_query(t, len+2);
    MAX = QueryLargest(t, 0, len);
    TEST_CHECK(MAX == n);
    TEST_MSG("Got: %d; Real: %d", MAX, n);

    clear_nodes();
}


void test_delete(void){
    init_nodes();

    //Build tree
    int len = 10;
    int p[] = {7,2,1,2,4,-12,2,2,2,2};
    tnode* t = build_treap(p, len);

    /*DELETION*/

    //Original
    int MAX = QueryLargest(t, 0, len-1);
    TEST_CHECK(MAX == 7);
    TEST_MSG("Got: %d", MAX);

    //Delete first item
    Delete(&t, 1-1);
    MAX = QueryLargest(t, 0, len-2);
    TEST_CHECK(MAX == 4);
    TEST_MSG("Got: %d", MAX);

    //Delete fourth item
    Delete(&t, 4-1); 
    MAX = QueryLargest(t, 0, len-3);
    TEST_CHECK(MAX == 2);
    TEST_MSG("Got: %d", MAX);
    print_tree(t);

    //Delete All
    for(int i=2;i<len;i++){
        Delete(&t, 0);
    }
    TEST_CHECK(t==NULL);
    if (t!=NULL)
        TEST_MSG("Got t.val: %d", t->val);

    clear_nodes();
}

void test_increase(void){
    init_nodes();

    //Build tree
    int len = 10;
    int p[] = {7,2,1,2,4,-12,2,2,2,2};
    tnode* t = build_treap(p, len);

    Increase(t, 1, len, 20);//()
    int MAX = QueryLargest(t, 0, len-1);
    TEST_CHECK(MAX == 24);
    TEST_MSG("Got: %d", MAX);
    

    int q = get_val_at_pos(t, 5);
    TEST_CHECK(q == 8);
    TEST_MSG("Got: %d", q);
    print_tree_by_query(t, len);

    clear_nodes();

}

void test_reverse(void){
    init_nodes();

    //Build tree
    int len = 10;
    int p[] = {7,2,1,2,4,-12,2,2,2,2};
    tnode* t = build_treap(p, len);

    Reverse(&t, 1, 9);
    print_tree_by_query(t, len);

    clear_nodes();

}

void test_find_largest(void){
    init_nodes();

    //Build tree
    int len = 10;
    int p[] = {7,2,1,2,14,-12,2,2,2,2};
    tnode* t = build_treap(p, len);

    int pos = get_node_pos(t->leaf[1], NULL);
    printf("Pos: %d", pos);



    tnode* largest = find_largest_minpos(t);
    pos = get_node_pos(largest, NULL);
    TEST_CHECK(largest->val == 14);
    TEST_MSG("Got: %d", largest->val); 
    TEST_CHECK(pos == 4);
    TEST_MSG("Got: %d", pos); 

    clear_nodes();

}

void test_remove_largest(void){
    init_nodes();
    //Build tree
    int len = 10;
    int p[] = {7,2,1,2,14,-12,2,2,2,2};
    tnode* t = build_treap(p, len);

    Remove(&t);

    TEST_CHECK(QueryLargest(t,0,len-1) == 7);
    TEST_CHECK(get_val_at_pos(t, 4) == -12);

    Remove(&t);
    Remove(&t);
    print_tree_by_query(t, len-3);
    TEST_CHECK(get_val_at_pos(t, 0) == 1);
    TEST_MSG("Got: %d", get_val_at_pos(t, 0));



    clear_nodes();

}


void test_maximum(void){

    /*TEST 1*/
    init_nodes();
    //Build tree
    int p[] = {2,1,-2,3,14,-12,2,2,30000,2,2};
    int len = sizeof(p)/sizeof(p[0]);
    tnode* t = build_treap(p, len);
    int max = QueryLargest(t,0,len-1);

    TEST_CHECK(max == 30000);
    TEST_MSG("Got: %d", max);

    clear_nodes();
}

void test_maximum_2(void){
    init_nodes();
    //Build tree
    int ps[] = {18300, 29753, 2980, 22690, -7762, -4779, -25393, 29411, -1922, -29893, -25148, -15353, -5610, -3094, -10506};
    //int len = 10;
    //int* ps = gen_vec_rand(len);
    int len = sizeof(ps)/sizeof(ps[0]);
    int MAX;
    int real;
    //Build tree by adding one by one
    tnode* t = NULL;

    for(int k=0;k<len;k++){
        Insert(&t, ps[k], k);
        MAX = QueryLargest(t, 0, k);
        real = max_vec(ps, 0, k);
        TEST_CHECK(MAX == real);
        TEST_MSG("Got: %d ; Real: %d at i=%d", MAX, real,k);
    }

    print_vec(ps, len);

    clear_nodes();
}


void test_maximum_random(void){
    //Build tree
    init_nodes();
    int len = 5;
    int* ps = gen_vec_rand(len);
    int MAX;
    int real;
    //Build tree by adding one by one
    tnode* t = NULL;
    int valid = 1;



    for(int k=0;k<len;k++){
        Insert(&t, ps[k], k);
        MAX = QueryLargest(t, 0, k);
        real = max_vec(ps, 0, k);
        TEST_CHECK(MAX == real);
        TEST_MSG("Got: %d ; Real: %d at i=%d", MAX, real,k);

        if(MAX!=real)
            valid = 0;
    }

    if(!valid){
        printf("\n");
        print_vec(ps, len);
        printf("\n");
    }


    free(ps);
    clear_nodes();
}


void test_remove_2(void){
    init_nodes();
    //Build tree
    int ps[] = {18300, 29753, 2980, 22690, -7762, -4779, -25393, 29411, -1922, -29893, -25148, -15353, -5610, -3094, -10506};
    //int len = 10;
    //int* ps = gen_vec_rand(len);
    int len = sizeof(ps)/sizeof(ps[0]);
    int MAX;
    int real;
    //Build tree by adding one by one
    tnode* t = build_treap(ps, len);

    Increase(t, 6, 10, 10000);
    Insert(&t, 29410, 8);
    Remove(&t);
    TEST_CHECK(QueryLargest(t, 0,len-1) == 29753);

    

    print_vec(ps, len);

    clear_nodes();
}


#endif
