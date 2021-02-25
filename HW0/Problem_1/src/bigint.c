#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <assert.h>
#include "include/bigint.h"
#include "include/utils.h"

//Create new biginteger from string
bigint newnumc(char* numb)
{

    int nlen = strlen(numb);
    int number[MAX_DEC];
    //allocate storage for the number, in the right length

    for(int i=0;i<nlen;i++)
    {
        number[i] = str2int(numb[nlen-i-1]);
    }

    bigint num = {
        .number = number,
        .length = nlen
    };

    //return the new bigint 
    return num;
}

bigint newnumint(int* int_arr,int length)
{

    int non_zero_start = length-1;

    //Get first non-zero site
    for (int i=length-1; i>=0; i--){
        assert(int_arr[i] >=0);
        assert(int_arr[i] <10);

        if (int_arr[i] == 0){
            continue;
        }
        else{
            non_zero_start = i;
            break;
        }
    }

    int number[non_zero_start+1];

    for (int i=0; i<non_zero_start+1; i++){
        number[i]  = int_arr[i];
    }

    bigint num = {
        number,
        non_zero_start + 1
    };

    return num;
}

bigint add(bigint* a, bigint* b)
{
    extm len_max;
    len_max = max(&(a->length), &(b->length));

    int shorter_len;
    int number[len_max.extreme+1];
    memset(number, 0, sizeof(number)); //zero array
    int length; 
    int carrier, s;

    // Get shorter length
    if (len_max.arg == 0) {
        shorter_len = b->length;
    }
    else {
        shorter_len = a->length;
    }
    
    //Add
    carrier = 0; 
    for (int i=0;i<shorter_len;i++){
        s = *(a->number) + *(b->number) + carrier;
        if (s < 10){
            number[i] = s;
            carrier = 0;
        }
        else {
            number[i] = s % 10;
            carrier = 1;
        }
    }

    // ToDO

}



void print(bigint num)
{
    int j;
    for (int i=0;i<num.length;i++)
    {
        j = num.length - i - 1;
        printf("%d",num.number[j]);
    }
}


char* string(bigint num)
{   
    int j; 
    char* STR = (char*)malloc(num.length * sizeof(char));

    for (int i=0; i<num.length;i++)
    {
        j = num.length - i - 1;
        STR[j] = num.number[i] + '0';
    }
 
    return STR;
}


//Convert 1 char to int.
int str2int(char numstr)
{
    // ASCII starts at 48
    int out = numstr - '0';
    return out;
}