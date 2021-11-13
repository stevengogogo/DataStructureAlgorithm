#include "include/utils.h"

//Choose the bigger one
extm max(int* a, int* b)
{
    int big, arg;
    if (*a > *b)
    {
        big = *a; arg=0;
    }
    else if (*a<*b)
    {
         big = *b; arg=1;
    }
    else 
    {
        big = *a; arg=0;
    }

    extm val = {big, arg};

    return val;
}

extm min(int* a, int* b)
{
    extm val_max = max(a, b);

    int extreme;
    int arg;
    if (val_max.arg == 0) {
        extreme = *b;
        arg = 1;
    }
    else {
        extreme = *a;
        arg = 0;
    }
 

    extm val_min = {
       extreme,
       arg
    };


    return val_min;
}

/*Compare two string. if identical returns 0. otherwise, return 0*/
int striden(char* a, char* b){
    int diff;
    int len_sh = strcmp(a,b);

    if  (len_sh == 0) {
        diff = strncmp(a,b, strlen(a));
        return diff;
    }
    else{
        return len_sh;
    }
}

//File IO
char* init_cwd(void){
    size_t str_size = sizeof(char) * 1024;
    char *cwd = (char*)malloc(str_size);
    if (getcwd(cwd,str_size) != NULL){
        return cwd;
    }
    else{
        perror("Error: ");
        return NULL;
    }
}

void close_cwd(char* cwd){
    free(cwd);
    cwd = NULL;
}

FILE* openreadfile(char filename[]){
    FILE *fptr;
    fptr = fopen(filename, "r");
    if (fptr == NULL){
        printf("Error: Filename %s doesn't exist\n", filename); 
        assert(fptr!=NULL);
    }
    return fptr;
}

void closereadfile(FILE* fptr){
    fclose(fptr);
    fptr = NULL;
}