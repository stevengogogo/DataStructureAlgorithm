/**
 * @file test_list.h
 * @brief 
 * @version 0.1
 * @date 2021-05-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef TEST_LINKEDLIST_H
#define TEST_LINKEDLIST_H

#include "list.h"

void test_init(void){
    packData pd = init_packData(100,100);
    kill_packData(pd);
}

void test_linklist(void){
    packData pd = init_packData(100,100);

    //Poplast
    for(int i=0;i<40;i++)
        _insertlist(pd,0,i);

    for(int i=40;i<80;i++)
        _insertlist(pd, 23, i);

    for(int i=1;i<100;i++){
        _mergelist(pd, 0,i );
        
        TEST_CHECK(pd.lines[i].list.first == NULL);
        TEST_CHECK(pd.lines[i].list.last == NULL);
    }

    _popFirst(pd, 0);

    for(int i=1;i<80;i++)
        _popLast(pd, 0);


    kill_packData(pd);

    //PopFirst
    pd = init_packData(100,100);

    _mergelist(pd, 0,1);

    for(int i=0;i<101;i++)
        _insertlist(pd, 1, i);

    for(int i=0;i<101;i++)
        _popFirst(pd, 1);
 
    TEST_CHECK(pd.lines[0].list.first == NULL);
    TEST_CHECK(pd.lines[0].list.last == NULL);
    TEST_CHECK(pd.lines[1].list.first == NULL);
    TEST_CHECK(pd.lines[1].list.last == NULL);

    kill_packData(pd);
}


#endif