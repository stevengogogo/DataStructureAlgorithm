/**
 * @file test_interface.h
 * @version 0.1
 * @date 2021-05-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef TEST_INTERFACE_H
#define TEST_INTERFAXCE_H

#include "acutest.h"
#include "list.h"

void test_stringOp(void){
    char a[20] = "push";
    TEST_CHECK(_getopID(a) == PUSH);
    TEST_CHECK(_getopID("merge") == MERGE);
}



#endif