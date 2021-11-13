/**
 * @file main.c
 * @author Steven Shao-Ting Chiu (r07945001@ntu.edu.tw).
 * @brief  See https://stevengogogo.github.io/DSA-EvilEval/ for details.
 * @version 0.1
 * @date 2021-04-01
 * 
 * @copyright Copyright (c) 2021
 * 
 * - Credit
 *  - I did this project alone.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "utils.h"
#include "eqeval.h"

int main(){
    char input_s[MAX_INPUT];
    double ans;

    while(  fgets(input_s, MAX_INPUT, stdin)  ){
        if (strcmp(input_s, "\n") == 0 )
            break;
        ans = eval_string(input_s);
        printf("%15.15f\n", ans);  
    }

    return 0;
}


/* For testing
int main()
{
    
    FILE* fptr = fopen("test/data/input.txt", "r");
    FILE* fptr_ans = fopen("test/data/output.txt", "r");

    char input[MAX_INPUT+1];
    char output[MAX_INPUT+1];

    double ans_e;
    double ans;

    //Read one line 
    while(fgets(input, MAX_INPUT, fptr)){ 
    
    fgets(output, MAX_INPUT, fptr_ans); 

    //eval
    printf("%s", input);
    ans_e = eval_string(input);
    ans = atof(output);

    if (is_double_equal(ans_e,ans) == 0){
        printf("Real: %f; Measured: %f", ans, ans_e);
    }

    assert(is_double_equal(ans_e,ans));

    }

    fclose(fptr);
    fclose(fptr_ans);

    return 0;
}
*/