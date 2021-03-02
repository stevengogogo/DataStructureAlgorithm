#include <stdio.h>

#include "acutest.h"

#include "test_bigint.h"
#include "test_utils.h"


// Run TESTs 
TEST_LIST = {
    {"Generate Integers to Bigint",test_create_bigint_from_ints},
    { "Element of BigInt", test_BigInt_element },
    {"Display", test_display},
    {"Utility", test_utils},
    {NULL, NULL} // Terminate the test
};