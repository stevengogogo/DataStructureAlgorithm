#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct {
    int extreme;
    int arg;
} extm;

extm max(int*,int*);
extm min(int*,int*);

int striden(char*,char*);

/*Get current directory. Default max length=1000*/
char* init_cwd(void);
void close_cwd(char*);

FILE* openreadfile(char filename[]);
void closereadfile(FILE* fptr);

#endif