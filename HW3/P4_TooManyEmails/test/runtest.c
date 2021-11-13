#include <stdio.h>

#include "acutest.h"

#include "test_utils.h"
#include "test_GarbleFilter.h"
#include "test_TextCompress.h"

// Run TESTs 
TEST_LIST = {
    //Utils
    {"Utility", test_utils},
    {"Dyanmic Array", test_array},
    {"Queue",test_queue},
    {"Ascii convertion", test_ascii},
    //Garble Text Filter
    {"Get occurrence", text_occurrence},
    {"Find garble text", find_garble_text},
    {"Find smallest leftest garble region",find_leftsmall_garble_text},
    {"Find smallest leftest garble region 2",find_leftsmall_garble_text2},
    {"Slice text", test_slice_text},
    {"Garble text filter", text_garblefilter},
    //Text compression
    {"Text compression: hash", text_hash},
    {"Text compression: print", text_compressed},
    {"Text compression: print2", test_compressed2},
    {NULL, NULL} // Terminate the test
};