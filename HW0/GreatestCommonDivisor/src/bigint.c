#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <assert.h>
#include "include/bigint.h"
#include "include/utils.h"

bigint init_bigint(int number[], int length)
{
    bigint p;
    int len_eff=length; //effective length
    int first_n = 1;
    memset(p.number, 0, sizeof(p.number)); // Fill zeros
    for(int i=length-1; i>=0; i--){
        p.number[i] = number[i];

        if ((number[i] != 0) & (first_n==1)){
            len_eff = i + 1; //new length
            first_n = 0;
        }
        else if ((i==0) & (first_n==1))
        {
           len_eff = 0;
        }
        
    }

    p.length = len_eff;
    
    return p;
}

bigint init_bigint_zero(void){
    int z[] ={0};
    return init_bigint(z, 0);
}

void copy_bigint(bigint* dest, bigint* src){
    dest->length = src->length;
    for(int i=0;i<src->length;i++){
        dest->number[i] = src->number[i];
    }
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


int compare_bigint(bigint a, bigint b){
    if (a.length != b.length){
        return 0;
    }
    else{
        for(int i=0;i<a.length;i++){
            if (a.number[i] != b.number[i]){
                return 0;
            }
        }
        return 1;
    }
}

bigint add(bigint a, bigint b)
{
    if (compare_bigint(b, init_bigint_zero())==1){
        return a;
    }
    else if (compare_bigint(a, init_bigint_zero())==1){
        return b;
    }

    swap_minmax_bigint(&a, &b);

    bigint SUM = b;
    assert(SUM.length >= a.length);
    int length; 
    int carrier, s;

    //Add
    carrier = 0; 
    for (int i=0;i<b.length;i++){
        if (i<a.length){
            s = a.number[i] + b.number[i] + carrier;
        }
        else{
            s =  b.number[i] + carrier;
        }
        SUM.number[i] = s%10;
        carrier = s/10;

        if (carrier !=0 & i==(b.length-1)){
            SUM.number[b.length] = carrier ;
            SUM.length += 1;
        }
        if (carrier == 0 & i>=a.length){
            break;
        }
    }


    assert(SUM.length<=MAX_DEC);


    return SUM;

}

bigint multply_10(bigint a){
    
    return power10_bigint(a, 1);
}

bigint power10_bigint(bigint a, int power){
    int eff_digit = a.length + power;
    assert(eff_digit<=MAX_DEC);
    assert(power >= 0);
    if (power==0){
        return a;
    }
    if (compare_bigint(a, init_bigint_zero())== 1){
        return a;
    }
    bigint mul = init_bigint_zero();
    mul.length = eff_digit;

    for(int i=0;i<a.length;i++){
        mul.number[i+power] = a.number[i];
    }
    return mul;
}

bigint multiplication_bigint(bigint a, bigint b){
    bigint mul_bigint;
    bigint zero =init_bigint_zero();
    bigint sum = newnumc("0");
    if (compare_bigint(a, zero)==1){
        return zero;
    }
    else if(compare_bigint(b, zero)==1){
        return zero;
    }

    if (argmax_bigint(a,b)==1){
        swap_bigint(&a, &b);
    }
    int carry;
    int mul_e;

    for(int j=0;j<b.length;j++){
        mul_bigint = multiply_onedecimal_bingint(a, b.number[j]);
        mul_bigint = power10_bigint(mul_bigint, j);
        sum = add(sum , mul_bigint );
    }

    return sum;
}

bigint multiply_onedecimal_bingint(bigint a, int b){
    assert(b>=0 & b<10);
    if (b==0){
        return init_bigint_zero();
    }

    bigint mul = a;
    int carrier = 0;
    int sum;
    for(int i=0;i<mul.length;i++){
        sum = mul.number[i] * b + carrier; 
        mul.number[i] = sum % 10; 
        carrier = sum/10;
    }
    if (carrier != 0){
        mul.number[a.length] = carrier;
        mul.length += 1;
    }

    return mul;
}

bigint substraction_bigint(bigint minu, bigint subtra){
    assert(argmax_bigint(minu, subtra) == 0 );
    bigint diff;
    int carry=0;
    int minus_total;
    int eff_len = minu.length;
   
    for(int i=0; i<(minu.length);i++){
        minus_total = subtra.number[i] + carry;
        if (minu.number[i]>=minus_total){
            diff.number[i] = minu.number[i] - minus_total;
        } 
        else{
            //Borrow 10 
            minu.number[i+1] -=1;
            diff.number[i] = 10 + minu.number[i] - minus_total; 
        }
    }

    // Get effective digits
    for(int i=minu.length-1;i>=0; i--){
        if (diff.number[i]==0){
            eff_len -= 1;
        }
        else{
            break;
        }
    }
    diff.length = eff_len;
    return diff;
}

bigint divide_bigint_onedigit(bigint divd, int div){
    assert(div>=0);
    bigint quo_big = init_bigint_zero();
    int dec; //Decimal number
    int quo; //Quotient
    int rem=0; //remainder
    int quo_len;
    int c_first_n = 1;
    for(int i= divd.length -1 ; i>=0; i--){
        dec = divd.number[i] + 10*rem;
        quo = dec / div;
        rem = dec % div;

        quo_big.number[i] = quo;

        //Record the first digint
        if ((quo !=0) & (c_first_n==1)){
          quo_big.length = i+1;
          c_first_n = 0; //mark first non-zero 
        }
        else if ((c_first_n==1) & (i==0)){
           quo_big.length = 0;
        }
        
    }


    return quo_big;
}

void swap_bigint(bigint* a, bigint* b){
    bigint temp = *a;
    *a = *b;
    *b = temp;
}

void swap_minmax_bigint(bigint* a,bigint* b){
    if (argmax_bigint(*a,*b) == 0){
        swap_bigint(a, b);
    }

}

int argmax_bigint(bigint a, bigint b){
    if (a.length > b.length){
        return 0;
    }
    else if (a.length < b.length){
        return 1;
    }

    for(int i=a.length-1;i>=0;i--){
        if (a.number[i] > b.number[i]){
            return 0;
        }
        else if (a.number[i] < b.number[i]){
            return 1;
        }
    }

    return 0;
}




bigint max_bigint(bigint a, bigint b){
    int argmax = argmax_bigint(a,b);
    if (argmax==0){
        return a;
    }
    else{
        return b;
    }
}

bigint min_bigint(bigint a, bigint b){
       int argmax = argmax_bigint(a,b);
    if (argmax==0){
        return b;
    }
    else{
        return a;
    }
}


bigint gcd_bigint(bigint a, bigint b){
    bigint gcd;
    bigint ans=newnumc("1");
    bigint zero = init_bigint_zero();
    bigint n=a;
    bigint m=b;
    // m: max; n: min
    swap_minmax_bigint(&n, &m);

    while ( compare_bigint(n, zero) != 1 & compare_bigint(m,zero) != 1  ){
        if (is_even_bigint(n) & is_even_bigint(m)){
            ans = add(ans,ans);
            n = divide_bigint_onedigit(n,2);
            m = divide_bigint_onedigit(m,2);
        }
        else if (is_even_bigint(n)){
            n = divide_bigint_onedigit(n,2);
        }
        else if (is_even_bigint(m)){
            m = divide_bigint_onedigit(m,2);
        }
        
        swap_minmax_bigint(&n,&m);

        m = substraction_bigint(m,n);
    }

    gcd = multiplication_bigint(n, ans);
    //gcd = multiplication_bigint(n, ans);
    return gcd;
}

int is_even_bigint(bigint a){
    if (a.number[0]%2 == 0){
        return 1;
    }
    else{
        return 0;
    }
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

void close_string(char* big_str){
    free(big_str);
    big_str = NULL;
}


//Convert 1 char to int.
int str2int(char numstr)
{
    // ASCII starts at 48
    int out = numstr - '0';
    return out;
}