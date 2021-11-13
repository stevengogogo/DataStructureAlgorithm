#include <stdio.h>

#include "acutest.h"

#include "test_utils.h"
#include "test_linkedarray.h"


// Run TESTs 
TEST_LIST = {
    {"Utility", test_utils},
    {"Util: Swap", test_swap},
    {"Utils: Array Insrtion", test_array_insert},
    {"Utils: Binary Search", test_binary_search},
    {"Utils: Binary Search Screen", test_binary_search2},
    {"Utils: Binary search Maxsmaller", test_binarySearch_maxSmaller},
    {"Utils: remove element", test_remove_arr},
    {"Utils: reverse array", test_reverse},
    {"LnkArr Initiation", test_init},    
    {"find", test_find},
    {"Insert", test_insert_LArray},
    {"Insert Random", test_insertRandom},
    //{"Insert Ordered/Indexed Equality",test_insert_OrderedIndexed},
    {"Delete", test_delete},
    {"Reverse", test_reverseLA},
    //{"Random reverse", randomReverse},
    {"Flipnodes", test_flipnodes},
    {"Query", test_query},
    {"Query Val", test_query},
    {"IDR", test_IDR},
    {NULL, NULL} // Terminate the test
};