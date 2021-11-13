#include <stdio.h>

#include "acutest.h"

#include "test_utils.h"
#include "test_stack.h"
#include "test_eqeval.h"


// Run TESTs 
TEST_LIST = {
    {"Stack Cycle", test_stack_cycle},
    {"Stack push pop", test_stack_push_pop},
    {"String: Parse", test_read_string},
    {"Convert String to Operator / Numbers", test_str2op},
    {"Evaluation", test_evaluation},
    {"Utility", test_utils},
    {NULL, NULL} // Terminate the test
};