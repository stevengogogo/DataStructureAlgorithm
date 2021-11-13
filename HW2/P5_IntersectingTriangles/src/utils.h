/**
 * @file utils.h
 * @author Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief General Utilities
 * @version 0.1
 * @date 2021-04-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {
    int n;
    int sol;
    int* ps;
    int* qs;
    int* rs;
} TriProb;

int* init_arr(int len);
void kill_arr(int*);

/** Noted that `right` is not included*/
void copy_arr(int* dst, int* src, int left, int right);

/** Return index of max element*/
int argmax(int n0, int n1);

void swap(int* a, int *b);

int ChooseMax(int a, int b);

TriProb ParseData(char* filePath);


void int2str(int , char *);
#endif