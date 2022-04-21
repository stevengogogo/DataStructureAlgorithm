#include <stdio.h>

#include "acutest.h"

#include "test_utils.h"
#include "test_tokenize.h"
#include "test_GenericStack.h"
#include "test_dymarr.h"
#include "test_FindSimilar.h"
#include "test_GroupAnalysis.h"
#include "test_FS_spurious_hit.h"

// Run TESTs 
TEST_LIST = {
    {"Utility", test_utils},
    //Tokenize
    {"Tokenize", test_popToken},
    {"Tokenize2", test_token},
    {"Regular Expression", test_Regex},
    {"Test GA data",test_data_GA},
    //Generic Array
    //{"Generic Array (int)", test_dynamic_universal_array},
    //{"Int array insert", array_compare},
    //{"Int uArray append", test_uarray_append_int},
    //{"Int array append", test_array_append_int},
    //{"Long uArray append", test_uarray_append_long},
    //{"Long array append", test_array_append_long},
    //{"Struct uArray append", test_uarray_append_struct},
    //{"Struct array append", test_array_struct},
    //Dynamic Array,
    {"Dyanmic Array", test_array},
    {"Queue",test_queue},
    {"Read email", readmail},
    {"Power", test_power},
    {"Char 2 number", test_char2num},
    {"Quick sort", test_sort},
    {"Matrix", test_matrix},
    {"Find Similar: data", test_FS_data},
    {"FS: data 2", test_data_2},
    {"Matrix ushort",void_test_matrix},
    //{"FS check spurious hit", test_check_spurious},
    //{"FS check spurious hit QID91: email 1099 vs 91 ", test_check_spurious2},
    /*
    {"Find Similar: Memory", memory_allocation_FS},
    {"Find Similar: init", test_init_FS},
    {"Find Similar: init content", test_init_content_FS},
    {"Find Similar: append hash",test_append_hash},
    {"Find Similar: summary", test_summary_FS},
    {"Find Similar: Rabin Karp", test_RabinKarp_hashing},
    {"Find Similar: Preprocessing", test_summarize},
    {"Find Similar: data", test_FS_data},
    //{"Find Similar: Preprocessing (Benchmark)", test_summarize_benchmark},
    {"Find Similar: Token history", test_tokenhash},
    */
    {NULL, NULL} // Terminate the test
};