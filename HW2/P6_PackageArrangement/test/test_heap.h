/**
 * @file test_heap.h
 * @brief 
 * @version 0.1
 * @date 2021-05-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef TEST_HEAP_H
#define TEST_HEAP_H

#include "list.h"
#include "acutest.h"

void test_heap(void){
    packData pd = init_packData(100,100);
    int a;

    //Heap insertion
    for (int i=1;i<=40;i++){
        _insertHeap(pd, 0, i);
    }

    //Heap extraction
    for (int i=40;i>=1;i--){
        a = _popMaxHeap(pd, 0);
        TEST_CHECK(i == a );
        TEST_MSG("Exp: %d ; Got: %d",i, a);
    }

    TEST_CHECK(pd.lines[0].heap == NULL);

    kill_packData(pd);
}


void test_heapMerge(void){
    packData pd = init_packData(100,100);
    int a;

    //Heap insertion
    for (int i=1;i<=20;i++){
        PushPack(pd, 0, i);
    }
    for (int i=21;i<=40;i++){
        PushPack(pd, 1, i);
    }

    _mergeHeap(pd, 0, 1);

    TEST_CHECK(pd.lines[1].heap == NULL);


    //Heap extraction
    for (int i=40;i>=1;i--){
        a = _popMaxHeap(pd, 0);
        TEST_CHECK(i == a );
        TEST_MSG("Exp: %d ; Got: %d",i, a);
    }

    TEST_CHECK(pd.lines[0].heap == NULL);

    kill_packData(pd);
}



#endif