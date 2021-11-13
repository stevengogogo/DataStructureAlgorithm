#ifndef TEST_STACK_H
#define TEST_STACK_H

#include "acutest.h"
#include "utils.h"
#include "stack.h"

#define MAX_INPUT 2000000

void test_stack_cycle(void){
    stack_nopor sd;
    opor pr;
    Operator op = MULT;

    //Initiation
    init_stack_nopor(&sd, MAX_INPUT);

    // Update order base
    update_stack_orderbase(&sd, op);
    
    
    // Push and smash
    push_stack_num(&sd, 0);
    push_stack_op(&sd, op);

    //Calculation: Default 0
    TEST_ASSERT(get_eq_answer(&sd)==0);

    //Destroy
    kill_stack_nopor(&sd);
}



void test_stack_push_pop(void){


}
#endif