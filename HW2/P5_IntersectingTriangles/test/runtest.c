#include <stdio.h>

#include "acutest.h"

#include "test_utils.h"
#include "test_intersects.h"




// Run TESTs 
TEST_LIST = {
    {"Utility", test_utils},
    {"load data", load_data},
    {"test parsing", testParseData},
    {"test Data", testData},
    {NULL, NULL} // Terminate the test
};