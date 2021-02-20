#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "bigint.h"



bigint* newnumc(char* numb)
{
    //allocate storage for the bigint
    bigint* num = (bigint*)malloc(sizeof(bigint));

    int nlen = strlen(numb);

    //allocate storage for the number, in the right length

    for(int i=0;i<nlen;i++)
    {
        num->number[i] = str2int(numb[nlen-i-1])  ;
    }

    num->length = nlen;

    //return the new bigint 
    return num;
}


/*
Convert 1 char to int.
*/
int str2int(char numstr)
{
    // ASCII starts at 48
    int out = numstr - '0';
    return out;
}


/*Display*/
void print(bigint* num)
{
    int j;
    for (int i=0;i<num->length;i++)
    {
        j = num->length - i - 1;
        printf("%d",num->number[j]);
    }
}

char* string(bigint* num)
{   
    int j; 
    char* STR = (char*)malloc(num->length * sizeof(char));
    for (int i=0; i<num->length;i++)
    {
        j = num->length - i - 1;
        STR[j] = num->number[i] + '0';
    }
    return STR;
}