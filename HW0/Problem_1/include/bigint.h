#ifndef BIGINT_H
#define BIGINT_H

typedef int digit; 
#define MAX_DEC 256 

typedef struct 
{
    int* number;
    int length;
} bigint; 

bigint newnumc(char*);

bigint newnumint(int*, int );
//Manipulation
bigint add(bigint*, bigint*);

//Display
void print(bigint);

char* string(bigint);

int str2int(char);


#endif