/**
 * @file utils.h
 * @author Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief General Utilities for C language
 * @version 0.1
 * @date 2021-03-08
 * @note 
 * Reference
 * 1. Universal Stack is modified from: https://github.com/igniting/generic-stack
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h> // tolower
#define INIT_NUM_ARRAY_ELEMENT 10
#define EMTY_QUE_SIG -121242
#define MAX_N_MAIL 11000
typedef unsigned char byte;

/************Math************/

/**
 * @brief Get arg max
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int argmax(int a,int b);

/**
 * Check `val` is in [lower,upper]
 */
bool inDomainInt(int val, int lower, int upper);

/************Tokenize************/

/**
 * @brief Pop token from message. 
 * 
 * @param token Buffer string. Token will be saved here. `\0` if no token left
 * @param message main text
 * @param iStr reading head
 * @return int updated reading head `iStr`. -1: end of string
 */
int popToken(char message[], char token[], int iStr);

/**
 * @brief Judge a character belong to regular expression or not
 * @note Regular expression: %[a-zA-Z0-9]
 * @return true 
 * @return false 
 */
bool isRegularExpr_ASCII(int);
bool isNumber_ASCII(int);
bool isUpperCase_ASCII(int);
bool isLowerCase_ASCII(int);
/**
 * @brief [0-9] -> [0-9]; [a-z] -> [10-35]; otherwise: ASCII
 * @param c 
 * @return int 
 */
int char2num(char c);

/************Dynamic Array (Int) Stack**************/
//dynamic array
typedef struct{
    int len;
    int size;
    int* i;
} dymArr;

//init and kill
void init_dymArr(dymArr*, int size);
void kill_dymArr(dymArr*);
void resize_dymArr(dymArr*, int new_max_size);

//clear
void clear_Arr(dymArr*);

//append
/**Append at last*/
void append_dymArr(dymArr*, int val);
/** Get the item of arr[i]*/
int get_item(dymArr, int i);
/** Get the last item
 * @return last element. If no item left, return `EMTY_QUE_SIG`
*/
int pop_item(dymArr*);

/*************Queue************/
typedef struct{
    dymArr arr;
    int head;
    int tail;
} que;

que init_que(int size);
void kill_que(que*);
void enque(que*, int val);
int deque(que*);
int peek_que(que*);

/************Generic Dynamic Array************/

/** Generic copy*/
void copy_item_array(void* dstArr, int locDst,void* srcArr, int locSrc, size_t size);

/** Universal dynamic Array*/
typedef struct uArray{
    int len;
    size_t eleSize;
    byte* memory;
    int num_maxEle;
} uArray;



void init_uArray(uArray* arr, size_t eleSize);
int len_uArray(uArray* arr);
void get_uArray(uArray* arr, int i,void* item);
void set_uArray(uArray* arr, int i,void* item);
void remove_uArray(uArray* arr, int i);
void insert_uArray(uArray* arr, int i,void* item);
void append_uArray(uArray* arr, void* item);
void update_size_uArray(uArray* arr, int new_max_item);
void kill_uArray(uArray* arr);


/*Sorting*/
/** * QuickSort to increasing order. Reference: This function is modified from https://openhome.cc/Gossip/AlgorithmGossip/QuickSort3.htm#C */
void quicksort(int arr[], int left, int right);

/** * Combine fragments. This function is modifed from: https://openhome.cc/Gossip/AlgorithmGossip/QuickSort3.htm#C */
int partition(int number[], int left, int right);

/** * Switch the value store in `x` and `y`. */
void swap(int* x, int* y);

/*Matrix*/
typedef struct Matrix{
    int* m;
    int nrow;
    int ncol;
} Matrix;

void init_Matrix(Matrix* M, int nrow, int ncol);
void kill_Matrix(Matrix* M);
void set_Matrix(Matrix* M, int r, int c, int val);
int get_Matrix(Matrix*M, int r, int c);



#endif