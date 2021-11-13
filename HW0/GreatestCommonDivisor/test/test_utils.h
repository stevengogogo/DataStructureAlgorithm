#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <unistd.h>
#include "acutest.h"
#include "include/utils.h"

void test_utils(void)
{
    int a, b;
    a = 1; b= 2;
    extm m = max(&a,&b);
    extm MIN = min(&a, &b);
    TEST_CHECK(m.extreme  == b );
    TEST_CHECK(MIN.extreme == a);
}

void test_str_identical(void){
    char a[] = "23232";
    char b[] = "23236";
    char c[] = "232";
    char d[] = "23232";

    TEST_CHECK(striden(a,b) != 0);
    TEST_CHECK(striden(a,c) != 0);
    TEST_CHECK(striden(a,d) == 0);
}

void test_cwd(void){
    char *cd;
    cd = init_cwd();
    TEST_CHECK(cd != NULL);
    close_cwd(cd);
}


#endif