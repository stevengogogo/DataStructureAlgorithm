/**
 * @file test_utils.h
 * @author Steven Chiu
 * @brief Test utility functions
 * @version 0.1
 * @date 2021-04-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "acutest.h"
#include "utils.h"

void test_utils(void)
{
    int arr[] = {-100,2,3,3,1000,1,3,61,-232,23,1,0,3,4,5,6,2,4,4};
    int len = sizeof(arr)/sizeof(arr[0]);

    quicksort(arr, 0, len-1);
    
    for(int i=0;i<len-1;i++)
        TEST_CHECK(arr[i] <= arr[i+1]); // Monotonous
}

void test_swap(void){
    int a = 3;
    int b = 2;
    swap(&a, &b);
    TEST_CHECK(a==2);
    TEST_CHECK(b==3);
}

void test_array_insert(void){
    int a[] = {1,2,3,4,5,56,2};
    int aIn[] = {30, 1,2,3,4,5,56};
    int aLen = 7;
    int b[] = {1,-1,-1,-1,-1};
    int bIn[] = {1,2,3,4,5};
    int bIn2[] = {1,2,3,4,5,20};
    int bmaxL = 5;
    int bLen = 1;
    
    // Insert A
    insert_arr(a, 0, 30, aLen);
    TEST_CHECK( compare_array(a, aIn, aLen)==1 );

    // Insert B
    for (int i=bLen; i<bmaxL;i++)
        insert_arr(b, i, i+1, ++bLen);

    TEST_CHECK( compare_array(b, bIn, bLen)==1 );
    TEST_CHECK( bLen == bmaxL);

    // Append
    append_arr(b, 20, ++bLen);
    TEST_CHECK(b[bLen-1] == 20);
    TEST_CHECK( compare_array(b, bIn2, bLen) == 1);
}

void test_binary_search(void){
    int arr[]={-12,0,1,1,2,3,4,5,6,7,8,11,11};
    int aLen = sizeof(arr)/sizeof(arr[0]);

    TEST_CHECK(BinarySearch_MinBigger(arr, aLen, -13) == 0);
    TEST_CHECK(BinarySearch_MinBigger(arr, aLen, -12) == 1);

    TEST_CHECK(BinarySearch_MinBigger(arr, aLen, 11) == (aLen-1));

    TEST_MSG("Expected: %d, Got %d",(aLen-1),BinarySearch_MinBigger(arr, aLen, (aLen-1)));

    TEST_CHECK(BinarySearch_MinBigger(arr, aLen, 100) == (aLen-1));
    TEST_MSG("Expected: %d, Got %d",(aLen-1),BinarySearch_MinBigger(arr, aLen, (aLen-1)));
    
    // arr[4] == 2 is the first element bigger than 1;
    TEST_CHECK(BinarySearch_MinBigger(arr, aLen, 1) == 4);
    TEST_MSG("Got %d",BinarySearch_MinBigger(arr, aLen, 1));

    // arr[9] == 8 is the first element bigger than 6
    TEST_CHECK(BinarySearch_MinBigger(arr, aLen, 6) == 9); 
    TEST_MSG("Got %d",BinarySearch_MinBigger(arr, aLen, 6));
}

void test_binarySearch_maxSmaller(void){
    int arr[] = {-123,2,3,4,5,6,7,7,8,8,9,9,10,11};
    int len = sizeof(arr)/sizeof(arr[0]);
    int I;


    TEST_CHECK(BinarySearch_MaxSmaller(arr, len, -123)
               == -1);
    TEST_MSG("Got %d", BinarySearch_MaxSmaller(arr, len, -123));

    TEST_CHECK(BinarySearch_MaxSmaller(arr, len, 7)
               == 5);
    TEST_MSG("Got %d", BinarySearch_MaxSmaller(arr, len, 7));
    
    TEST_CHECK(BinarySearch_MaxSmaller(arr, len, 9)
               == 9);
    TEST_MSG("Got %d", BinarySearch_MaxSmaller(arr, len, 10));

    TEST_CHECK(BinarySearch_MaxSmaller(arr, len, 12)
               == 13); // the last one is smaller
    
    TEST_CHECK(BinarySearch_MaxSmaller(arr, len, -124)
               == -1); // no one is smaller
    
    //Screening
    int Isort, Iscreen;
    for (int i=-200; i<200;i++){
        //Location
        I = BinarySearch_MaxSmaller(arr, len, i);
        //Number of smaller items
        Isort = NumItemSmaller_Sorted(arr, len, i);
        Iscreen = NumItemSmaller_Screen(arr, 0, len-1, i);

        TEST_CHECK(Isort==Iscreen);

        if (I==-1){
            TEST_CHECK(arr[0] >= i);
            TEST_CHECK(Isort==0);
            TEST_MSG("got Isort = %d; I =%d", Isort, I);
        }
        if (I!=-1){
            TEST_CHECK(I == (Isort-1));
            TEST_CHECK(i > arr[I] );
            if (I<len-1)
                TEST_CHECK(arr[I+1] >= i);
                TEST_MSG("Got arr[I]=%d, arr[I+1] = %d, i=%d", arr[I], arr[I+1], i);
        }
    }


   

}

void test_binary_search2(void){
    int arr[]={-100,-100,-12,0,1,1,2,2,3,3,3,3,4,5,6,7,7,8,11,11};
    int aLen = sizeof(arr)/ sizeof(arr[0]);
    int Max = 102;
    int Min = -Max;
    int i_; // result of Binary search

    for(int key=Min; key<Max; key++){
        i_ = BinarySearch_MinBigger(arr, aLen, key);

        if (i_==0){
            TEST_CHECK(arr[i_] >= key);
            TEST_MSG("Value at %d = %d (key=%d)", i_, arr[i_], key);
        }
        else if (i_ == aLen-1) {
            TEST_CHECK( arr[i_] <= key );
            TEST_MSG("Value at %d = %d (key=%d)", i_, arr[i_], key);
        }
        else {
            TEST_CHECK( arr[i_] > key );
            TEST_CHECK( arr[i_-1] <= key);
            TEST_MSG("Value at (%d,%d) = (%d, %d) (key=%d)", i_ -1, i_, arr[i_ - 1],arr[i_], key);
        }
    }
}

void test_remove_arr(void){
    int arr[]={-100,-100,-12,0,1,1,2,2,3,3,3,3,4,5,6,7,7,8,12,11};
    int len = sizeof(arr)/sizeof(arr[0]);

    remove_arr(arr, 0, len);
    --len;
    remove_arr(arr, 0, len);
    --len;
    remove_arr(arr, len-1, len);
    --len;

    TEST_CHECK(arr[0] == -12);
    TEST_MSG("Got: %d", arr[0]);

    TEST_CHECK(arr[len-1] == 12);
    TEST_MSG("Got: %d", arr[len-1]);
}

void test_reverse(void){
    int arr[] = {1,2,2,3,4,5};
    int arrR[] = {1,2,4,3,2,5};
    int len = sizeof(arr)/sizeof(arr[0]);
    reverse_arr(arr,2, 4);
    TEST_CHECK(compare_array(arr, arrR, len));
}

#endif