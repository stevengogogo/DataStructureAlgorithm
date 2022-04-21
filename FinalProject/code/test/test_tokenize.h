#ifndef TEST_TOKENIZE_H
#define TEST_TOKENIZE_H

#include "utils.h"
#include "acutest.h"
#include <string.h>

void test_popToken(void){
    char message[] = "I23 have1 A_ very- good) (dAy+";
    int n_token = 6;
    char tokenStr[6][300] ={ 
        "i23",
        "have1",
        "a",
        "very",
        "good",
        "day"
    };


    char token[2048];
    int iStr = 0;

    for (int i=0;i<n_token;i++){
        iStr = popToken(message, token, iStr);
        TEST_CHECK(strcmp(token, tokenStr[i]) == 0);
        TEST_MSG("Expected: %s ; Got: %s (%d)\n",tokenStr[i], token, iStr);
    }

    //When no more token left
    int iend = 0;
    iend = popToken(message, token, iStr);
    TEST_CHECK(iend == -1);
    TEST_CHECK(iStr = strlen(message)+1);
    TEST_CHECK( strncmp(token, "\0", strlen(token)) == 0 );
}

void test_token(){
    char message[] = "Dsa Final p-+ro%ject {} \" poopoo";
    int n_token = 6;
    char tokenStr[6][300] ={ 
        "dsa",
        "final",
        "p",
        "ro",
        "ject",
        "poopoo"
    };
    char token[2048];
    int iStr = 0;

    for (int i=0;i<n_token;i++){
        iStr = popToken(message, token, iStr);
        TEST_CHECK(strcmp(token, tokenStr[i]) == 0);
        TEST_MSG("Expected: %s ; Got: %s (%d)\n",tokenStr[i], token, iStr);
    }
}

void test_Regex(void){
    TEST_CHECK(isRegularExpr_ASCII('+')==0 );
    TEST_CHECK(isRegularExpr_ASCII('-')==0 );
    TEST_CHECK(isRegularExpr_ASCII('&')==0 );
    TEST_CHECK(isRegularExpr_ASCII('^')==0 );
    TEST_CHECK(isRegularExpr_ASCII('>')==0 );
    TEST_CHECK(isRegularExpr_ASCII('\'')==0 );
    TEST_CHECK(isRegularExpr_ASCII('\0')==0 );
    TEST_CHECK(isRegularExpr_ASCII('`')==0 );
    TEST_CHECK(isRegularExpr_ASCII('&')==0 );
    TEST_CHECK(isRegularExpr_ASCII('$')==0 );
    TEST_CHECK(isRegularExpr_ASCII('_')==0 );
    TEST_CHECK(isRegularExpr_ASCII('#')==0 );
    TEST_CHECK(isRegularExpr_ASCII('?')==0 );
    TEST_CHECK(isRegularExpr_ASCII('@')==0 );
    TEST_CHECK(isRegularExpr_ASCII(')')==0 );
    TEST_CHECK(isRegularExpr_ASCII('*')==0 );
    TEST_CHECK(isRegularExpr_ASCII('!')==0 );
    TEST_CHECK(isRegularExpr_ASCII('~')==0 );
    TEST_CHECK(isRegularExpr_ASCII(';')==0 );
    TEST_CHECK(isRegularExpr_ASCII(' ')==0 );

    TEST_CHECK(isRegularExpr_ASCII('a')==1 );
    TEST_CHECK(isRegularExpr_ASCII('A')==1 );
    TEST_CHECK(isRegularExpr_ASCII('4')==1 );
    TEST_CHECK(isRegularExpr_ASCII('0')==1 );
    TEST_CHECK(isRegularExpr_ASCII('E')==1 );
}


#endif