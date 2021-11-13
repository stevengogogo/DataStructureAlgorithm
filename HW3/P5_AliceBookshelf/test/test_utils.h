#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "acutest.h"
#include "utils.h"
#include "array.h"

void test_utils(void)
{
    int a, b;
    a = 1; b= 2;
    
    TEST_CHECK(argmax(a,b)  == 1 );
    TEST_CHECK(max(a,b) == 2);
    TEST_CHECK(max(b,a)==2);
}

void array_operation(void){
    array arr = create_array(10000);
    int list[] = {1,2,3,4,5,6};

    Build_arr(&arr, list, 6);
    TEST_CHECK(compare_arr(arr, list));

    Insert_arr(&arr, 20, 0);
    int list2[] = {20,1,2,3,4,5,6};
    TEST_CHECK(compare_arr(arr, list2));

    Insert_arr(&arr, 40, 7);
    int list3[] = {20,1,2,3,4,5,6,40};
    TEST_CHECK(compare_arr(arr, list3));

    Delete_arr(&arr, 1);
    int list4[] = {1,2,3,4,5,6,40};
    TEST_CHECK(compare_arr(arr, list4));
    TEST_CHECK(QueryLargest_arr(&arr, 1,7) == 40);

    Reverse_arr(&arr, 3,6);
    int list5[] = {1,2,6,5,4,3,40};
    TEST_CHECK(compare_arr(arr, list5));
    TEST_CHECK(QueryLargest_arr(&arr, 1,4) == 6);


    Remove_arr(&arr);
    int list6[] = {1,2,6,5,4,3};
    TEST_CHECK(compare_arr(arr, list6));
    TEST_CHECK(QueryLargest_arr(&arr, 1,6) == 6);

    kill_array(&arr);
}

#endif