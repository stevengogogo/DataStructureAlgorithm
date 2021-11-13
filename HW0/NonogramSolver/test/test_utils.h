/**
 * @file test_utils.h
 */

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "acutest.h"
#include "utils.h"

void test_utils_flipflop(void){
    int init = 0;
    TEST_ASSERT(rising_FlipFlop(&init, 0) == 0 );
    init = 1;
    TEST_ASSERT(rising_FlipFlop(&init, 0) == 0 );
    init = 0;
    TEST_ASSERT(rising_FlipFlop(&init, 1) == 1 );
    init = 1;
    TEST_ASSERT(rising_FlipFlop(&init, 1) == 0 );

    TEST_ASSERT(rising_FlipFlop_noupdate(1,0) == 0);
    TEST_ASSERT(rising_FlipFlop_noupdate(1,1) == 0);
    TEST_ASSERT(rising_FlipFlop_noupdate(0,1) == 1);
    TEST_ASSERT(rising_FlipFlop_noupdate(0,0) == 0);

    TEST_ASSERT(falling_FlipFlop_noupdate(0,0) == 0);
    TEST_ASSERT(falling_FlipFlop_noupdate(0,1) == 0);
    TEST_ASSERT(falling_FlipFlop_noupdate(1,0) == 1);
    TEST_ASSERT(falling_FlipFlop_noupdate(1,1) == 0);
}

void test_utils_find_ID(void)
{
    dymarr* ids;
    int arr[] = {1,2,3,4,2,1,4,2};
    int arr_size = 7;
    int key = 1;
    int id_r[] = {0,5}; //location of keys;

    ids = init_ids_int_arr(arr, arr_size, key);
    
    TEST_ASSERT(ids->len == sizeof(id_r)/sizeof(id_r[0]));
    //Comapre all elements
    for(int i=0;i<ids->len;i++){
        TEST_ASSERT(ids->array[i] == id_r[i]);
    }
    TEST_ASSERT(ids->maxlen > ids->len);

    //Clean
    close_ids_int_arr(ids);
}

void test_dymarr(void){
    dymarr a;
    int init_size = 10;
    int arr[] = {2,3,4,5,6,7,8,9,10,11,12};
    int arr_len = 11; 
    int init_val=1;
    
    //Initiation with length =0; maxsize=10
    init_dymarr(&a, init_size);
    TEST_ASSERT(a.maxlen==init_size);
    TEST_ASSERT(a.len==0);
    
    //Insert a value
    insert_dymarr(&a, init_val);
    TEST_ASSERT(a.len==1);
    TEST_ASSERT(a.array[0]==init_val);

    //Insert an array
    insert_arr_dymarr(&a, arr, arr_len);
    TEST_ASSERT(a.len= (1+arr_len));
    TEST_ASSERT(a.maxlen > init_size);

    //Pop and remove
    TEST_ASSERT(pop_dymarr(&a) == arr[arr_len-1]);
    TEST_ASSERT(a.len == arr_len);

    close_dymarr(&a);
}


#endif