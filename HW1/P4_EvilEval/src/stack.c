#include "stack.h"

int get_order(Operator op){
        switch (op)
    {
    case PLUS:
        return 0;
        break;
    case MINUS:
        return 0;
        break;
    case MULT:
        return 1;
        break;
    case DIV:
        return 1;
        break;
    case LP:
        return 2;
        break;
    case RP:
        return  -2;
        break;
    default: {
        perror("Error Order convertion");
        raise(SIGINT);
        break;
    }
    }
}


int is_parenthesis(Operator op){
    if (op==LP)
        return 1;
    else if(op==RP)
        return 1;
    else 
        return 0;
}


/*Initiation*/

void init_stack_nopor(stack_nopor* sd, int maxsize){
    opor init_op;

    sd->nums = (double*)malloc((maxsize+1+2)*sizeof(double));
    sd->opors = (opor*)malloc((maxsize+1)*sizeof(opor));
    assert(sd->nums != NULL);
    assert(sd->opors != NULL);
    sd->maxsize = maxsize;
    sd->order_base = 0;

    //Initiate operation
    init_op.op = PLUS;
    init_op.order = 0;

    sd->nums[0] = 0;
    sd->opors[0] = init_op;

    //Tops
    sd->top = 0; //insert 0+0
    sd->top_num = 0; // [0]
}



/*Destruction*/
void kill_stack_nopor(stack_nopor* st){
    free(st->nums);
    free(st->opors);
    st->nums = NULL;
    st->opors = NULL;
}



void update_stack_orderbase(stack_nopor* st, Operator op){
    if (is_parenthesis(op)){
        st->order_base += get_order(op);
    }
}

/*Pop*/
double pop_stack_num(stack_nopor* st){
    assert((st->top_num ) >=0 );
    double num;
    num = st->nums[st->top_num];
    --(st->top_num);
    return num;
}

opor pop_stack_opor(stack_nopor *st){
    assert(st->top>=0);
    opor pr;
    pr = st->opors[st->top];
    --(st->top);
    return pr;
}

/*Push*/
void push_stack_num(stack_nopor* st, double num){
    assert(st->top_num<st->maxsize);
    ++(st->top_num);//Append

    st->nums[st->top_num] = num;
}

void push_stack_op(stack_nopor* st, Operator op){
    assert(st->top < st->maxsize);
    assert(st->top >= 0);
    assert(op!=LP);
    assert(op!=RP);

    opor pr = {
        .op = op,
        .order = get_order(op)+st->order_base //Add order base
    };


    while((st->opors[st->top].order >= pr.order) && (st->top>=0) ){ 
        eval_stack_nopor_once(st);
    } //until op becomes the lartest

    ++(st->top);  // append
    st->opors[st->top] = pr;
}


/*Pop*/
void eval_stack_nopor_once(stack_nopor* st){
    assert(st->top >= 0);
    double a,b;
    double c;
    opor pr;

    // Get numbers
    b = pop_stack_num(st);
    a = pop_stack_num(st);

    // Get Operator
    pr = pop_stack_opor(st);
    
    // Eval 
    c = eval(pr.op, a, b);

    //Update
    push_stack_num(st, c);
}

void eval_stack_nopor(stack_nopor* st){
    while(st->top > 0){
        eval_stack_nopor_once(st);
    }

}

double get_eq_answer(stack_nopor* st){
    double ans;
    eval_stack_nopor(st);
    assert(st->top_num < 3);
    ans = eval(st->opors[0].op, 
               st->nums[0], 
               st->nums[1]
            );
    if (st->top_num==2){ //single value
        ans += st->nums[st->top_num];
    }
    return ans;
}

double eval(Operator op, double a, double b){
    switch (op)
    {
    case PLUS:
        return a + b ;
        break;
    case MULT:
        return a*b;
        break;
    case MINUS:
        return a-b;
    case DIV:
        return a/b;
    default: {
        perror("Error Symbol to convert to operator");
        raise(SIGINT);
        break; 
    }
    }
}

opor get_opor(Operator op , stack_nopor* st){
    opor pr;
    assert(is_parenthesis(op) == 0);
    pr.order = get_order(op) + st->order_base;
    pr.op = op;
    return pr;
};
