/**
 * @file test_dataArrange.h
 * @version 0.1
 * @date 2021-05-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef TEST_DATAARRANGE_H
#define TEST_DATAARRANGE_H

#include "list.h"
#include "acutest.h"

void test_peek(void){
    packData pd = init_packData(100,100);
    pack* pk = NULL;
    int (*fun[3])(packData, int)=  {PeekFirstPack, PeekLastPack, PeekMaxPack};

    for (int i=1;i<=20;i++)
        PushPack(pd, i-1, i);
    
    for (int i=0;i<3;i++){
        TEST_CHECK((*fun[i])(pd, 0)==1);
    }

    for (int i=0;i<3;i++){
        TEST_CHECK((*fun[i])(pd, 99)==EMPTY);
    }
    

    for(int i=19;i>0;i--){
        MergeLines(pd, 0, i);
        TEST_CHECK(pd.lines[i].avail == 0);
        TEST_CHECK(pd.lines[i].heap == NULL);
        TEST_CHECK(pd.lines[i].list.first == NULL);
    }


    TEST_CHECK(PeekFirstPack(pd, 0)==1);
    TEST_CHECK(PeekLastPack(pd, 0)==2);
    TEST_CHECK(PeekMaxPack(pd, 0)==20);
    for (int i=0;i<3;i++){
        TEST_CHECK((*fun[i])(pd, 2)==EMPTY);
    }

    TEST_CHECK(PopFirstPack(pd, 0) == 1);
    TEST_CHECK(PopLastPack(pd, 0) == 2);
    TEST_CHECK(PopMaxPack(pd, 0) == 20);

    TEST_CHECK(pd.packs[1].avail==0);
    TEST_CHECK(pd.packs[2].avail==0);
    TEST_CHECK(pd.packs[20].avail==0);


    kill_packData(pd);
}

void test_func_pointer(void){
    packData pd = init_packData(100,100);
    pack* pk = &pd.packs[1]; // Pack ID: 1
    PushPack(pd, 0, 1);
    TEST_CHECK( (*(pk->popfunc))(pd, pk->line) == pk->ID);
}


#endif