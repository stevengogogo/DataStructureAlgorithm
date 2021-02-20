#include <stdio.h>
#include <string.h>
#include "acutest.h"
#include "../bigint.h"

void
test_BigInt_element(void)
{
    char i[] = "12345";
    int len_i = strlen(i);
    int num;
    char str;

    bigint* a;
    
    a = newnumc(i);

    // Check all members of numbers
    for (int j=0;j< len_i; j++){
        str = i[len_i-j-1];
        num = str2int(str);
   
        TEST_CHECK(a->number[j] == num);
        TEST_MSG("BigInt->Number = %d ; Input= %c ", a->number[j], num);
    }

    // Check Length
    TEST_CHECK(a->length == strlen(i) );
    TEST_MSG("Size of BigInt = %d ; Input= %lu", a->length, strlen(i));

    
}

void test_display(void)
{
    char i[]= "12345678";
    bigint* BIGNUM = newnumc(i);
    char* str_BIGNUM = string(BIGNUM);


    TEST_CHECK(strcmp(str_BIGNUM,i)==0);
    TEST_MSG("string(BIGNUM)=%s", str_BIGNUM);

    print(BIGNUM);
}


// Run TESTs 
TEST_LIST = {
    { "Element of BigInt", test_BigInt_element },
    {"Display", test_display},
    {NULL, NULL} // Terminate the test
};