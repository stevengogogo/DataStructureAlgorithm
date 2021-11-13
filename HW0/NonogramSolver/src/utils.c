/**
 * @file utils.c
 */

#include "utils.h"

//IO
void print_cwd(void){
    char buf[80];
    getcwd(buf, sizeof(buf));
    printf("current working directory : %s\n", buf);
}

/*Compare two string. if identical returns 0. otherwise, return 0*/
int striden(char* a, char* b){
    int diff;
    int len_sh = strcmp(a,b);

    if  (len_sh == 0) {
        diff = strncmp(a,b, strlen(a));
        return diff;
    }
    else{
        return len_sh;
    }
}


//Convert 1 char to int.
int str2int(char numstr)
{
    // ASCII starts at 48
    int out = numstr - '0';
    return out;
}

void int2str(char* s,int num){
    sprintf(s, "%d", num);
}



/*Free Str object*/
void killstr(char* str){
    free(str);
    str = NULL;
}


/*Dynamical Array*/
void init_dymarr(dymarr* a,int init_size){
    int* ap = (int*)malloc(init_size*sizeof(int));
    assert(ap!=NULL);
    a->array = ap;
    a->len = 0;
    a->maxlen = init_size;
}

void close_dymarr(dymarr* a){
    free(a->array);
    a->array = NULL;
    a->len = 0;
    a->maxlen = 0;
}

void insert_arr_dymarr(dymarr* a, int src[], int src_len){
    for(int i=0;i<src_len;i++){
        insert_dymarr(a, src[i]);
    }
}

void insert_dymarr(dymarr* a, int val){
    a->len += 1;
    if(a->len == a->maxlen){
        a->maxlen += 10;
        a->array = realloc(a->array, a->maxlen*sizeof(int) );
        assert(a->array != NULL);
    }
    a->array[a->len-1] = val;
}

int pop_dymarr(dymarr* a){
    int last_val = a->array[a->len-1];
    a->len -= 1;
    assert(a>=0);

    //Release the memory
    if (a->len < (a->maxlen - 10)){
        a->maxlen -= 10;
        a->array = realloc(a->array, a->maxlen*sizeof(int) );
    }
    return last_val;
}


int findfirst_int_arr(int arr[], int arr_size, int key){
    for(int i=0;i<arr_size;i++){
        if (arr[i] == key){
            return i;
        }
    }
    return -1;
}

dymarr* init_ids_int_arr(int arr[], int arr_size, int key){
    dymarr* ids;
    init_dymarr(ids, arr_size);
    
    //Linear searching the id
    for(int i=0;i<arr_size;i++){
        if(arr[i] == key)
            insert_dymarr(ids, i);
    }
    return ids;
}

void close_ids_int_arr(dymarr* a){
    close_dymarr(a);
}


// Flip Flop

/** Rising Flip flop. Return 1 when new state is rising. Noted that this fucntion update the init_state*/
int rising_FlipFlop(int* init_state, int new_state){
    int output;
    output = rising_FlipFlop_noupdate(*init_state, new_state);
    *init_state = new_state; //update
    return output;
}

/**Rising Flip flop but doesn't update the init_state*/
int rising_FlipFlop_noupdate(int init_state, int new_state){
    int output;
    if (init_state<new_state)
        output=1;
    else
        output=0;
    return output;
}


int falling_FlipFlop_noupdate(int init_state, int new_state){
    int output;
    if (init_state>new_state)
        output=1;
    else
        output=0;
    return output;
}

