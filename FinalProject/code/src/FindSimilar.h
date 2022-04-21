/**
 * @file FindSimilar.h
 * @author Steven Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief Group Analysis. Use Jaccob's similarity with hash table to identify similar strings.
 * @version 0.1
 * @date 2021-06-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FINDSIMILAR_H
#define FINDSIMILAR_H
#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
#include "GroupAnalysis.h"

/**********Constant Variable***********/
#define Q_RABIN 7388607
#define D_RABIN 36
#define TOKEN_STRING_LENGTH 4000
#define ULONG  long
#define UINT  int
#define USHORT unsigned short
#define ushort unsigned short

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "api.h"

typedef struct Matrix_ushort {
    ushort** m;
    ushort* len;
    int nrow;
    int ncol;
} Matrix_ushort;

void init_Matrix_ushort(Matrix_ushort* M, int nrow, int ncol);
void kill_Matrix_ushort(Matrix_ushort* M);


typedef struct infoFS{
    Matrix_ushort hstack;
    double* num_unique;
    double* SimList;
} infoFs;


void init_FS(infoFs* info);
void kill_FS(infoFs* info);

/** Return location*/
int popTokenHash(char message[], char token[], int iStr, int* Hash);
void append_mHash(infoFs* info,mail* mails, int ID);

void proc_FS(infoFs* info, mail* mails, int n_mail);


int Hash_RK(char s[]);

void answer_FS(infoFs*info, mail* mails, int ID, int n_mail, double threshold, int* list, int* nlist);
void register_hash(infoFs* info, int ID, int hash);


#endif