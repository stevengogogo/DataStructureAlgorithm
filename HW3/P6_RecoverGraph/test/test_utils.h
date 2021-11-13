#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "acutest.h"
#include "utils.h"

void test_utils(void)
{
    int a, b;
    a = 1; b= 2;
    
    TEST_CHECK(argmax(a,b)  == 1 );
}


#endif