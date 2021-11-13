#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "acutest.h"
#include "utils.h"

#define MAX_NODES 1000000

void test_utils(void)
{
    int a, b;
    a = 1; b= 2;
    
    TEST_CHECK(argmax(a,b)  == 1 );
}

void test_array(void){
    dymArr arr = init_Arr(1);

    for(int i=0;i<MAX_NODES;i++)
        append_dymArr(&arr, i);

    TEST_CHECK(arr.size >= MAX_NODES);
    TEST_CHECK(arr.len == MAX_NODES);
    for(int i=0;i<MAX_NODES;i++)
        TEST_CHECK(get_item(arr, i) == i);

    kill_dymArr(&arr);
}

void test_queue(void){
    que q = init_que(1);
    for(int i=0;i<MAX_NODES;i++)
        enque(&q, i);

    TEST_CHECK(q.tail >= MAX_NODES-1);
    TEST_CHECK(q.head == 0);

    for(int i=0;i<MAX_NODES;i++)
        TEST_CHECK(deque(&q) == i);
    TEST_CHECK(deque(&q) == EMTY_QUE_SIG);
    TEST_CHECK(q.head-1 == q.tail);
    TEST_MSG("q.head: %d; q.tail %d", q.head, q.tail);
    TEST_CHECK(q.arr.len == MAX_NODES);
    TEST_CHECK(q.arr.size >= MAX_NODES);
    kill_que(&q);
}

#endif