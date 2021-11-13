#ifndef TEST_LIST_H
#define TEST_LIST_H

#include "acutest.h"
#include "list.h"
#include <stdio.h>

void test_node_init(void){


    node* a = init_node(3);
    node* b = init_node(2);
    list l = {
        .str = a,
        .end = b
    };

    a->data = 3;
    a->ngb[0] = NULL;
    a->ngb[1] = b;

    b->ngb[0] = a;
    b->ngb[1] = NULL;

    TEST_ASSERT( leave(&l) == 1);
    TEST_ASSERT( l.end == a );
    TEST_ASSERT( l.str == a );

    TEST_ASSERT( leave(&l) == 1);
    TEST_ASSERT( l.end == NULL );
    TEST_ASSERT( l.str == NULL );
    //kill_node(a);
    //kill_node(b);
}


void test_kill_list(void){


    list l = init_list();

    enter(&l, 3);
    enter(&l, 4);

    kill_list(&l);
    TEST_ASSERT( l.end == NULL );
    TEST_ASSERT( l.str == NULL );

    TEST_ASSERT(leave(&l) == -1); //release null line
    //kill_node(a);
    //kill_node(b);
}

void test_flag(void){
    node* a = init_node(3);
    node* b = init_node(2);


    TEST_ASSERT(get_flag2node(a) == -1);
    TEST_ASSERT(get_flag2null(a) == 2);

    //link
    a->data = 3;
    a->ngb[0] = NULL;
    a->ngb[1] = b;

    b->ngb[0] = a;
    b->ngb[1] = NULL;

    TEST_ASSERT(get_flag2node(a) == 1);
    TEST_ASSERT(get_flag2null(a) == 0);
}


void test_migrate(void){
    list line[2];

    for (int i=0;i<2;i++)
        line[i] = init_list();

    for (int i=0; i<100; i++)
        enter(&line[0], i);
    for (int i=0; i<45; i++)
        leave(&line[0]);

    migrate(&line[0], &line[1]);

    TEST_ASSERT(line[0].str == NULL);
    TEST_ASSERT(line[0].end == NULL);
    TEST_ASSERT(line[1].str != NULL);
    TEST_ASSERT(line[1].end != NULL);
    
    for (int i=0;i<2;i++)
        kill_list(&line[i]);
}

#endif