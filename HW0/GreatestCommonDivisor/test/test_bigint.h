#ifndef TEST_BIGINT_H
#define TEST_BIGINT_H

#include <string.h>
#include "acutest.h"
#include "assert.h"
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

    TEST_CHECK(newnumc("0").length == 0);
    TEST_CHECK(newnumc("1").length == 1);
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
    bigint z = init_bigint_zero();
    bigint c = add(a,b);
    bigint ans = newnumc("125");

    TEST_CHECK(compare_bigint(a, add(a,b)) == 1);
    TEST_CHECK(striden(create_string(c), create_string(ans)));
}

void test_substraction(void){
    bigint a = newnumc("00000232343342342");
    bigint b = newnumc("9999999");
    bigint ans = newnumc("232333342343");
    bigint ans_p;

    ans_p = substraction_bigint(a,b);
    TEST_CHECK(compare_bigint(ans_p, ans)==1);

    bigint a2 = newnumc("232343342342");
    bigint b2 = newnumc("232343342342");
    bigint ans2 = init_bigint_zero();
    bigint ans_p2;

    ans_p2 = substraction_bigint(a2,b2);
    TEST_CHECK(compare_bigint(ans_p2, ans2)==1);
    TEST_MSG("%s - %s = %s . but got %s", create_string(a2), create_string(b2), create_string(ans2), create_string(ans_p2));
}

void test_init_bigint(void){
    int a[] = {1,2,3,4};

    bigint p = init_bigint(a,4);
    bigint z = init_bigint_zero();

    TEST_CHECK(z.length == 0);
    TEST_CHECK(p.length == 4);
}

void test_compare(void){
    bigint a = newnumc("0000000003434341341412234234");
    bigint b = newnumc("3434341341412234234");
    bigint c = newnumc("3434341341412234234000000000");
    bigint d1 = newnumc("0");
    bigint d2 = newnumc("000000000000");
    

    TEST_CHECK(compare_bigint(a,b)==1);
    TEST_CHECK(compare_bigint(d1,d1)==1);
    TEST_CHECK(compare_bigint(d1,d2)==1);
    TEST_CHECK(compare_bigint(b,c)==0);
    TEST_CHECK(compare_bigint(a,c)==0);
}
void test_division(void){

    //Define problem
    bigint divident1 = newnumc("3434341341412234234");
    bigint divident2 = newnumc("1");
    bigint divident3 = newnumc("0");
    int divisor=2;
    bigint quotient1, quotient2, quotient3;
    bigint quo_real1 = newnumc("1717170670706117117");
    bigint quo_real2 = newnumc("0");
    bigint quo_real3 = newnumc("0");
    //Calculation
    quotient1 = divide_bigint_onedigit(divident1, divisor);
    quotient2 = divide_bigint_onedigit(divident2, divisor);
    quotient3 = divide_bigint_onedigit(divident3, divisor);
    //Test
    TEST_CHECK(compare_bigint(quotient1, quo_real1)==1);
    TEST_MSG("%s / %d = %s . but got %s", create_string(divident1), divisor, create_string(quo_real1), create_string(quotient1));
    TEST_CHECK(compare_bigint(quotient2, quo_real2)==1);
    TEST_CHECK(compare_bigint(quotient3, quo_real3)==1);
}

void test_swap(void){
    bigint a = newnumc("3434341341412234234");
    bigint b = newnumc("0");
    bigint a2 = newnumc("0");
    bigint b2 = newnumc("3434341341412234234");

    swap_bigint(&a, &b);
    TEST_CHECK(compare_bigint(a,a2)==1);
    TEST_CHECK(compare_bigint(b,b2)==1);
}

void test_swapminmax(void){
    bigint a = newnumc("23532");
    bigint b = newnumc("23332");
    swap_minmax_bigint(&a, &b);

    TEST_CHECK(compare_bigint(a,b)==0);
}

void test_minmax(void){
    bigint a2 = newnumc("001212132313");
    bigint b2 = newnumc("00000003434341341");

    TEST_CHECK(argmax_bigint(a2,b2) == 1);
    TEST_CHECK( compare_bigint(max_bigint(a2,b2), b2) == 1);
    TEST_CHECK( compare_bigint(min_bigint(a2,b2), a2) == 1);
}

void test_even(void){
    bigint a = newnumc("001212132312");
    bigint a2 = newnumc("001212132319");
    TEST_CHECK(is_even_bigint(a) == 1);
    TEST_CHECK(is_even_bigint(a2) == 0);
}

void test_multiplication(void){


    bigint a = newnumc("2343242423423424");
    //bigint b = newnumc("9990");
    //bigint ans = newnumc("23408991810000005760");
    bigint b = newnumc("234324244");
    bigint ans = newnumc("549078509377421720691456");

    /*
            2343242423423424
                   234324244
    549078509377421720691456
    539078409377421720691456
    */

    bigint ans_p = multiplication_bigint(a,b);
    TEST_CHECK(compare_bigint(ans,ans_p)==1);
    TEST_MSG("%s * %s = %s . but got %s", create_string(a), create_string(b), create_string(ans), create_string(ans_p));

    //Multiply with 10;
    bigint a1 = newnumc("2343242423423424");
    bigint b1 = newnumc("234324242342342400");
    bigint c1 = power10_bigint(a1,2);
    TEST_CHECK(compare_bigint(c1, b1) == 1 );
    TEST_MSG("%s * 10 = %s . but got %s", create_string(a1), create_string(b1), create_string(c1));
}

void test_multiply_onedecimal(void){
    bigint a = newnumc("999999999999");
    int b = 9;
    int c = 0;
    bigint ab_r = newnumc("8999999999991");
    bigint ac_r = init_bigint_zero();
    bigint ab = multiply_onedecimal_bingint(a, b);
    bigint ac = multiply_onedecimal_bingint(a, c);

    TEST_CHECK(compare_bigint(ab,ab_r) == 1);
    TEST_CHECK(compare_bigint(ac,ac_r)==1);
}

void test_gcd(void){
    bigint a = newnumc("23532");
    bigint b = newnumc("23332");
    bigint gcd_real = newnumc("4");
    bigint gcd = gcd_bigint(a,b);

    TEST_CHECK(compare_bigint(gcd,gcd_real) == 1);
    TEST_MSG("GCD(%s,%s) = %s . but got %s", create_string(a), create_string(b), create_string(gcd_real), create_string(gcd));
    TEST_CHECK(compare_bigint(gcd_bigint(a,b), gcd_bigint(multiply_onedecimal_bingint(a,2), b)) == 1);
    TEST_CHECK(compare_bigint(gcd_bigint(a,b), gcd_bigint(substraction_bigint(a,b), b)) == 1);

}


void print_error(bigint a, bigint b, bigint an, bigint anp){
        char *arg[4];
        bigint ARG[4] = {a,b,an,anp} ;
        for(int i=0;i<4;i++){
            arg[i] = create_string(ARG[i]);
        }
        //Print error message
        TEST_MSG("gcd(%s,%s)=%s. But got %s\n", arg[0], arg[1], arg[2], arg[3]);

        for (int i=0;i<4;i++){
            close_string(arg[i]);
        }
    }
void test_gcd_data(void){
    char a[256], b[256], ans[256];
    bigint A,B,ANS, ANS_p;
    char line[300];
    FILE *fptr; 

    fptr = openreadfile("test/data/gcd.txt");

    while (fgets(line, sizeof(line), fptr) != NULL){
        sscanf(line,"%s%s%s",a,b,ans);
        //Create Bigint from string
    A = newnumc(a);
        B = newnumc(b);
        ANS = newnumc(ans);
        ANS_p = gcd_bigint(A,B);

        TEST_CHECK(compare_bigint(ANS, ANS_p) == 1);
        if (compare_bigint(ANS, ANS_p) != 1){
            print_error(A,B,ANS,ANS_p);
        }
    }


    closereadfile(fptr);
}


#endif