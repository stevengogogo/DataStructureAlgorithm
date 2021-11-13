#include "utils.h"

//Choose the bigger one
int argmax(int a, int b){
    if (a>b)
        return 0;
    else 
        return 1;
}


dymArr init_Arr(int size){
    assert(size>=1);
    int* is = (int*)malloc(size*sizeof(int));
    dymArr arr = {
        .i = is,
        .len = 0,
        .size = size
    };
    return arr;
}

void kill_dymArr(dymArr* arr){
    arr->size=0;
    arr->len=0;
    free(arr->i);
};

void clear_Arr(dymArr* arr){
    arr->len = 0;
}

void append_dymArr(dymArr* arr, int val){
    //Augement size
    if((arr->len+1) > arr->size){
      int new_size = (arr->size)*2 + 1;
      arr->i = realloc(arr->i, sizeof(int)*new_size);
      arr->size = new_size;
    }

    arr->i[arr->len] = val;
    ++(arr->len);
}

int get_item(dymArr arr, int i){
    return arr.i[i];
}

int pop_item(dymArr* p){
    if(p->len==0)
        return EMTY_QUE_SIG;
    int val = p->i[p->len-1];
    --p->len;
    return val;
}


// Queue

que init_que(int size){
    que q;
    q.arr = init_Arr(size);
    q.head = -1;
    q.tail = -1;
    return q;
}

void kill_que(que* q){
    kill_dymArr(&q->arr);
}

void enque(que* q, int val){
    append_dymArr(&q->arr, val);
    if(q->head == -1){ //first element
        ++(q->head);
    }
    q->tail = q->arr.len - 1;
}

int deque(que* q){
    if(q->head > q->tail || q->head==-1){
        return EMTY_QUE_SIG;
    }

    int val = get_item(q->arr, q->head);
    ++(q->head);
    return val;
}

int peek_que(que* q){
    if(q->head > q->tail || q->arr.len==0)
        return EMTY_QUE_SIG;
    else 
        return q->arr.i[q->head];
}