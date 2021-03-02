#ifndef TEST_BIGINT_H
#define TEST_BIGINT_H


#include "acutest.h"
#include "include/bigint.h"
#include "include/utils.h"


void test_create_bigint_from_ints(void){
    int a[] ={1,2,3,4,4,5,0,0,0};
    int len_a = 9;
    int a_[] = {1,2,3,4,4,5 };
    int len_a_ = 5;
    bigint big = newnumint(a, len_a);

    print(big);
    //TEST_ASSERT(big.length == 6);

    for (int i=0;i< len_a_;i++)
    {
        TEST_ASSERT(big.number[i]== a_[i]);
        TEST_MSG("Bigint.%d; Input.%d at i=%d", big.number[i], a_[i], i);
    }

}

void
test_BigInt_element(void)
{
    char i[] = "12345";
    int len_i = strlen(i);
    int num;
    char str;

    bigint a;
    
    a = newnumc(i);

    // Check all members of numbers
    for (int j=0;j< len_i; j++){
        str = i[len_i-j-1];
        num = str2int(str);
   
        TEST_CHECK(a.number[j] == num);
        TEST_MSG("BigInt.Number = %d ; Input= %c ", a.number[j], num);
    }

    // Check Length
    TEST_CHECK(a.length == strlen(i) );
    TEST_MSG("Size of BigInt = %d ; Input= %lu", a.length, strlen(i));

    
}

void test_display(void)
{
    char i[]= "12345678";
    bigint BIGNUM = newnumc(i);
    char* str_BIGNUM = create_string(BIGNUM);

    TEST_CHECK(str_BIGNUM[sizeof(i)/sizeof(i[0])]== '\0');
    TEST_CHECK(strcmp(str_BIGNUM,i)==0);
    TEST_MSG("string(BIGNUM)=%s", str_BIGNUM);

    print(BIGNUM);

}


void test_ADD(void)
{
    bigint a = newnumc("123");
    bigint b = newnumc("2");
    bigint c = add(a,b);
    bigint ans = newnumc("125");

    TEST_CHECK(striden(create_string(c), create_string(ans)));
}

void test_init_bigint(void){
    int a[] = {1,2,3,4};

    bigint p = init_bigint(a,4);
    bigint z = init_bigint_zero();

    TEST_CHECK(z.length == 1);
    TEST_CHECK(p.length == 4);
}


#endif