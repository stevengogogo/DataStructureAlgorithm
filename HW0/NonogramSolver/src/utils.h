/**
 * @file utils.h
 * @brief general usage
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//IO
/** Print current directory*/
void print_cwd(void);

/*Compare two string. if identical returns 0. otherwise, return 0*/
int striden(char* a, char* b);

//Convert 1 char to int.
int str2int(char numstr);
void int2str(char* s,int num);

//Cleaner
void killstr(char*);

//find: return index of the key. return -1 if the array doesn't contain the key
int findfirst_int_arr(int arr[], int arr_size, int key);


/**
 * @brief Dynamical Array
 * @param array Interger array
 * @param len length of data
 * @param maxlen maximum storage
 */
typedef struct{
    int* array;
    int len;
    int maxlen;
}dymarr;

void init_dymarr(dymarr*,int init_size);
void close_dymarr(dymarr*);
void insert_arr_dymarr(dymarr*, int src[], int src_len);
void insert_dymarr(dymarr*, int val);
int pop_dymarr(dymarr*);

/** Find all id of a key in array. Return a dynamical array*/
dymarr* init_ids_int_arr(int arr[], int arr_size, int key);
/** Kill a dynamical array with found IDs. */
void close_ids_int_arr(dymarr*);
/** Convert single char to int. */
int str2int(char numstr);
/** Initiation of interger to string*/
void int2str(char* s,int num);
/** Cleaner */
void killstr(char*);


//FlipFlop

//**Rising flip flop. return 1 when switch ON. And change the init_state*/
int rising_FlipFlop(int* init_state, int new_state);

int rising_FlipFlop_noupdate(int init_state, int new_state);
int falling_FlipFlop_noupdate(int init_state, int new_state);


#endif