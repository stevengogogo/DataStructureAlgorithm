#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <assert.h>
#include "include/bigint.h"
#include "include/utils.h"

bigint init_bigint(int number[], int length)
{
    bigint p;
    memset(p.number, 0, sizeof(p.number)); // Fill zeros
    for(int i=0; i<length; i++){
        p.number[i] = number[i];
    }

    p.length = length;
    
    return p;
}

bigint init_bigint_zero(void){
    int z[] ={0};
    return init_bigint(z, 1);
}



//Create new biginteger from string
bigint newnumc(char* numb)
{

    int nlen = strlen(numb);
    int number[MAX_DEC];
    bigint num;
    //allocate storage for the number, in the right length

    for(int i=0;i<nlen;i++)
    {
        number[i] = str2int(numb[nlen-i-1]);
    }

    num = init_bigint(number,nlen);

    //return the new bigint 
    return num;
}

bigint newnumint(int int_arr[],int length)
{

    int non_zero_start = length-1;
    bigint num;
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

    num = init_bigint(number, non_zero_start + 1);

    return num;
}

/* Return Bigint with effective number. */
/*
bigint effective_num(bigint ovnum)
{
  int eff_i = ovnum->length;
  for (int i=ovnum->length-1; i>0; i-- ){
      if (ovnum->number[i] == 0){
        eff_i--;
      }
      else{
        break;
      }
  }

  ovnum->length = eff_i + 1;
  
}
*/

bigint add(bigint a, bigint b)
{
    extm len_max;
    len_max = max(&(a.length), &(b.length));

    int shorter_len;
    bigint SUM = init_bigint_zero();
    int length; 
    int carrier, s;

    // Get shorter length
    if (len_max.arg == 0) { // a is bigger
        shorter_len = b.length;
    }
    else {
        shorter_len = a.length;
    }
    
    //Add
    carrier = 0; 
    for (int i=0;i<shorter_len;i++){
        s = a.number[i] + b.number[i] + carrier;
        if (s < 10){
            SUM.number[i] = s;
            carrier = 0;
        }
        else {
            SUM.number[i] = s % 10;
            carrier = 1;
        }
    }

    return SUM;

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


char* create_string(bigint num)
{   
    int j; 
    char* STR = (char*)malloc((num.length + 1) * sizeof(char));
    STR[ num.length ] = '\0';
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