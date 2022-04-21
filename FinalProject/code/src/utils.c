#include "utils.h"

/************Math************/

//Choose the bigger one
int argmax(int a, int b)
{
   if (a>b){
       return 0;
   }
   else{
       return 1;
   }
}

bool inDomainInt(int val, int lower, int upper){
    if(val<=upper && val>=lower)
        return true;
    else
        return false;
}

/************Tokenize************/
int popToken(char message[], char token[], int iStr){
    char c;
    int asc; //ascii number
    //No string left
    if (iStr < 0){
        token[0] = '\0';
        return -1;
    }

    int i = 0; //token[i]
    while(message[iStr] != '\0' ){
        c = message[iStr];
        asc = (int)c; //ascii number

        if (isRegularExpr_ASCII(asc)){
            if (isUpperCase_ASCII(c))
                c = tolower(c);
            token[i] = c;
            ++i;
            ++iStr;
        }
        else{
            if (i==0){
                ++iStr;
                continue;
            }
            else 
                break;
        }
    }

    if (message[iStr] == '\0'){ // EOF
        iStr= -1;
    }

    token[i] = '\0'; //end of token

    return iStr;
}

bool isRegularExpr_ASCII(int asc){
    if(isNumber_ASCII(asc))
        return true;
    else if(isUpperCase_ASCII(asc))
        return true;
    else if(isLowerCase_ASCII(asc))
        return true;
    else
        return false;
}

bool isNumber_ASCII(int asc){
    return inDomainInt(asc, 48, 57);
}

bool isUpperCase_ASCII(int asc){
    return inDomainInt(asc, 65, 90);
}

bool isLowerCase_ASCII(int asc){
    return inDomainInt(asc, 97, 122);
}

int char2num(char c){
    if(isNumber_ASCII(c)){
        return (int)c - '0';
    }
    else if(isLowerCase_ASCII(c)){
        return (int)c - 'a' + 10;
    }
    else{
        return (int)c;
    }
}

/********Dynamic Array (Int) stack*********/

void init_dymArr(dymArr* arr, int size){
    assert(size>=1);
    int* is = (int*)malloc(size*sizeof(int));
    if(is==NULL){
        fprintf(stderr, "Init Error: Insufficient Memory.\n");
        exit(1);
    }

    arr->i = is;
    arr->len = 0;
    arr->size = size;
}

void kill_dymArr(dymArr* arr){
    arr->size=0;
    arr->len=0;
    free(arr->i);
};

void resize_dymArr(dymArr* arr, int new_max_size){
    arr->size = new_max_size;
    arr->i = realloc(arr->i, sizeof(int)*new_max_size);
}

void clear_Arr(dymArr* arr){
    arr->len = 0;
}

void append_dymArr(dymArr* arr, int val){
    ++(arr->len);
    //Augement size

    if((arr->len+1) > arr->size){
      int new_size = (arr->size)*2 + 1;
      arr->i = realloc(arr->i, sizeof(int)*new_size);
      arr->size = new_size;
      if(arr==NULL){
        fprintf(stderr, "Append Error: Insufficient Memory.\n");
        exit(1);
       }
    }

    arr->i[arr->len - 1] = val;
}

int get_item(dymArr arr, int i){
    return arr.i[i];
}

int pop_item(dymArr* arr){
    if(arr->len==0)
        return EMTY_QUE_SIG;
    int val = arr->i[arr->len-1];
    --arr->len;

    return val;
}


/*************Queue************/

que init_que(int size){
    que q;
    init_dymArr(&q.arr,size);
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



/************Generic Array************/

void copy_item_array(void* dstArr, int locDst,void* srcArr, int locSrc, size_t size){
    //Start point
    int start_dst = locDst*size;
    int start_src = locSrc*size;

    if (size=sizeof(int)){
        *(int*)(dstArr+start_dst) = *(int*)(srcArr+start_src);
    }
    else if (size=sizeof(long)){
        //printf("f");
        *(long*)(dstArr+start_dst) = *(long*)(srcArr+start_src);
    }
    else{
        //Copy
        memcpy((byte*)(dstArr+start_dst), (byte*)(srcArr+start_src), size);
        //*(byte*)(srcArr+j+start_src) = *(byte*)(dstArr+j+start_dst);
    }
}

void init_uArray(uArray* arr, size_t eleSize){
    byte* mem = (byte*)malloc(eleSize*INIT_NUM_ARRAY_ELEMENT);
    
    //Check memory is allocated
    if(mem==NULL){
        fprintf(stderr, "Stack Init Error: Insufficient Memory.\n");
        exit(1);
    }

    //Initiation
    arr->eleSize = eleSize;
    arr->len = 0;
    arr->memory = mem;
    arr->num_maxEle=INIT_NUM_ARRAY_ELEMENT;
}

int len_uArray(uArray* arr){
    return arr->len;
}

void get_uArray(uArray* arr, int i,void* item){
    //Check i domain
    if (i>=len_uArray(arr) || i<0){
        fprintf(stderr, "Invalid index with array length %d. Got i=%d\n", arr->len, i);
        exit(1);
    }

    //Copy item
    copy_item_array(item, 0, arr->memory, i, arr->eleSize);
}

void set_uArray(uArray* arr, int i,void* item){
    //Check i domain
    if (i>=len_uArray(arr) || i<0){
        fprintf(stderr, "Invalid index with array length %d. Got i=%d\n", arr->len, i);
        exit(1);
    }

    //Copy item
    copy_item_array(arr->memory, arr->len-1, item, 0, arr->eleSize);
}

void remove_uArray(uArray* arr, int I){
    
    for(int i=arr->len-1;i>I;i--){
        copy_item_array(arr->memory, i-1, arr->memory, i, arr->eleSize);
    }

    --arr->len;

    //Shrink memory
    if(arr->len < arr->num_maxEle/2-10){
        update_size_uArray(arr, arr->num_maxEle/2);
    }
}

void insert_uArray(uArray* arr, int I,void* item){

    //For empty array 
    if(arr->len == 0 && I==0){
        append_uArray(arr, item);
        return;
    }

    ++arr->len;
    //Extend memory
    if(arr->len == arr->num_maxEle){
        update_size_uArray(arr, arr->num_maxEle*2+1);
    }

    //Shift right
    for(int i=I;i<arr->len-1;i++){
        copy_item_array(arr->memory, i+1, arr->memory, i, arr->eleSize);
    }


}

void append_uArray(uArray* arr, void* item){
    ++arr->len;
    //Augment size
    if(arr->len == arr->num_maxEle){
        update_size_uArray(arr, arr->num_maxEle*2+1);
    }   

    copy_item_array(arr->memory, arr->len-1, item, 0, arr->eleSize);
}

void update_size_uArray(uArray* arr, int new_max_item){
    arr->num_maxEle = new_max_item;
    arr->memory = realloc(arr->memory, arr->eleSize*arr->num_maxEle);
    if(arr->memory==NULL){
        fprintf(stderr, "Update size error: Invalid Memory allocation with size %d\n", arr->num_maxEle);
        exit(1);
    }
}

void kill_uArray(uArray* arr){
    free(arr->memory);
    arr->eleSize = 0;
    arr->len = 0;
    arr->num_maxEle = 0;
}

/**Sorting**/

void quicksort(int arr[], int left, int right){
    if (left < right){
        int q = partition(arr, left, right);
        quicksort(arr, left, q-1);
        quicksort(arr, q+1, right);
    }
}

int partition(int arr[], int left, int right){
    int i = left-1;
    int j;
    for(j=left; j < right; j++){
        if(arr[j] <= arr[right]){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i+1], &arr[right]);

    return i+1;
}

void swap(int* x, int* y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

/*matrix*/
void init_Matrix(Matrix* M, int nrow, int ncol){
    int* m = (int*)calloc(ncol*nrow, sizeof(int));
    M->m = m;
    M->ncol = ncol;
    M->nrow = nrow;
}

void kill_Matrix(Matrix* M){
    free(M->m);
    M->ncol = 0;
    M->nrow = 0;
}

void set_Matrix(Matrix* M, int r, int c, int val){
    int offset = r*M->ncol + c;
    M->m[offset] = val;
}

int get_Matrix(Matrix*M, int r, int c){
    int offset = r*M->ncol + c;
    return M->m[offset];
}
