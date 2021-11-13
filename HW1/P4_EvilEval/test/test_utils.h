#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "acutest.h"
#include "utils.h"

void test_utils(void)
{
    double a = 12.00000000333;
    double b = 12.00000000333;
    TEST_ASSERT(is_double_equal(a,b)==1);
}


#endif