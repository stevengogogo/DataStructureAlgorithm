#ifndef TEST_UTILS_H
#define TEST_UTILS_H

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


#endif