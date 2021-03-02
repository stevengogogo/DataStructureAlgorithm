#ifndef BIGINT_H
#define BIGINT_H

#define MAX_DEC 256 

typedef struct 
{
    int number[MAX_DEC];
    int length;
} bigint;

bigint init_bigint(int number[], int length);


void copy_bigint(bigint*, bigint*);

bigint newnumc(char*);

bigint newnumint(int*, int );

bigint newnumint_eff(int,int);
//Manipulation
bigint add(bigint, bigint);

//Display
void print(bigint);

char* create_string(bigint);

int str2int(char);


#endif