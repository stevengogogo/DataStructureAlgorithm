#include <stdio.h>

#include "acutest.h"

#include "test_utils.h"
#include "test_treap.h"

// Run TESTs 
TEST_LIST = {
    {"Utility", test_utils},
    {"array", array_operation},
    {"Treap: Insertion and build", test_build},
    {"Treap: Insertion at start", test_insert_at_start},
    {"Treap: Deletion", test_delete},
    {"Treap: Increase", test_increase},
    {"Treap: Reverse", test_reverse},
    {"Treap: Find largest position (with minimum key)", test_find_largest},
    {"Treap: Remove Largest", test_remove_largest},
    {"Treap: Remove 2", test_remove_2},
    {"Treap: Maximum Consistency", test_maximum},
    {"Treap: Maximum Consistency 2", test_maximum_2},
    //{"Treap: Maximum Consistency (Random)", test_maximum_random},
    {NULL, NULL} // Terminate the test
};