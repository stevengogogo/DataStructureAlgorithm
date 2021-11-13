#include <stdio.h>

#include "acutest.h"

#include "test_utils.h"
#include "test_list.h"


// Run TESTs 
TEST_LIST = {
    {"Utility", test_utils},
    {"Construct and kill a node", test_node_init},
    {"Kill list", test_kill_list},
    {"Flag Update", test_flag},
    {NULL, NULL} // Terminate the test
};