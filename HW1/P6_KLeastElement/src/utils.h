/**
 * @file utils.h
 * @author Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief General Utilities for C language
 * @version 0.1
 * @date 2021-04-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef UTILS_H
#define UTILS_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int min;
    int max;
} MinMax;

/** * QuickSort. Reference: This function is modified from https://openhome.cc/Gossip/AlgorithmGossip/QuickSort3.htm#C */
void quicksort(int arr[], int left, int right);

/** * Combine fragments. This function is modifed from: https://openhome.cc/Gossip/AlgorithmGossip/QuickSort3.htm#C */
int partition(int number[], int left, int right);

/** * Switch the value store in `x` and `y`. */
void swap(int* x, int* y);

/** @brief Insert a value in an array with a iven length.
 *  @warning The arr[length-1] is the place holder, and will be replaced.
 *  @note i_ means the index starts at 0.
 *  @param arr array to be inserted
 *  @param i_ the position to be inserted, starts at 0 -> (length - 1)
 *  @param x the value to be inserted.
 *  @param length length of an array, the last element arr[length-1] is the place holder for the new value.
 *  @return the number of relocations
 */
int insert_arr(int arr[], int i_, int x, int length);

/** * Insert a value at the end of the array*/
void append_arr(int arr[], int x, int length);
/** * Remove arr[i] and shift one step to the left [i,end]*/
void remove_arr(int arr[], int i, int length);
/** * Reverse array in given region [str, end]*/
int reverse_arr(int arr[], int str, int end);
/** * Compare two arrays
 * @return 0: Different; 1:same in the given length
 */
int compare_array(int A[], int B[], int length);


/**
 * @brief Find the minimum i which fullfills arr[i] > key.
 * @warning If all arr[i] < key. Return length-1
 * @param arr 
 * @param length 
 * @param key 
 * @return @i_. 
 * @note This function is inspired by [GreekforGeek](https://www.geeksforgeeks.org/first-strictly-greater-element-in-a-sorted-array-in-java/)
 */
int BinarySearch_MinBigger(int* arr, int length, int key);

/**
 * @brief Find the maximum location i which fullfills arr[i] < key
 * @note How many members **smaller** than `key` ? It is `(i+1)` where i is the return. Support arr[i] (exception: i=-1) 
 * @return int i location starts from 0, -1 for all the member is bigger or equal to the key
 */
int BinarySearch_MaxSmaller(int* arrSorted, int length, int key);

/**
 * @brief Measure how many item is smaller than key in a sorted array. 
 * @details This method uses the binary search (O(logn)) that is faaster than \ref NUmItemSmaller_screen. However, it requires sorted array. 
 * @param arrSorted Sorted array
 * @param length 
 * @param key value to be compared
 * @return int number of item smaller than key
 */
int NumItemSmaller_Sorted(int* arrSorted, int length, int key);

/**
 * @brief Measure how many item is smaller than key in an array. 
 * @details This method uses screening method to count how many item is smaller than the key. O(n)
 * @warning `end` is not the length. Use index
 * @param arr 1D array
 * @param str start point. `arr[str]`
 * @param end end point. `arr[end]` 
 * @param key value to be compared
 * @return int number of item smaller than the `key`.
 */
int NumItemSmaller_Screen(int* arr, int str, int end, int key);

/** Find min and max in an array [can be unsorted]*/
MinMax findMinMax(int* arr, int str, int end);
int update_MinMax(MinMax* dst, int min, int max);

/*TESTING*/
typedef struct {
    int* arr;
    int len;
} array;
array init_array();
int insert_array(array*, int i, int x);
int delete_array(array*, int i);
int reverse_array(array*, int l, int r);
int query_array(array* list, int l, int r, int k);
#endif