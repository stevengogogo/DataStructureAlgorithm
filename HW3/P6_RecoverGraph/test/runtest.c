#include <stdio.h>

#include "acutest.h"

#include "test_utils.h"


// Run TESTs 
TEST_LIST = {
    {"Utility", test_utils},
    {"Dyanmic Array", test_array},
    {"Queue",test_queue},
    {NULL, NULL} // Terminate the test
};