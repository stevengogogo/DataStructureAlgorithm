#include "utils.h"


void quicksort(int arr[], int left, int right){
    if (left< right){
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

int insert_arr(int arr[], int i_, int x, int length){
    assert(length >= 0); // Don't allow empty array

    int moveNum = length - 1 - i_;

    // Relocate elements
    for (int j=(length-2); j>= i_; j--)
        arr[j+1] = arr[j];

    arr[i_] = x;

    return moveNum;
}

void append_arr(int arr[], int x, int length){
    insert_arr(arr, length-1, x, length);
}

void remove_arr(int arr[], int i, int length){
    for(int j=i; j<length-1;j++){
        arr[j] = arr[j+1];
    }
}

int reverse_arr(int arr[], int str, int end){
    assert(str>=0);
    assert(end>=0);
    int STR = str;
    int END = end;
    int flip = 0;

    if (STR > END){
        swap(&STR, &END);
        ++flip;
    }
    while (STR < END)
    {
        swap(&arr[STR], &arr[END]);
        STR++;
        END--;
    }  
    return flip;
}

int compare_array(int A[], int B[], int length){
    for (int i=0;i<length;i++){
        if(A[i] != B[i])
            return 0;
    }
    return 1;
}


int BinarySearch_MinBigger(int* arr, int length, int key){
    int low = 0;
    int high = length - 1;
    int mid;
    assert(high>=low);

    int ans = length -1 ;

    while(high >= low){
        mid = (high+low) / 2;
        if (key >= arr[mid]){
            low = mid + 1;
        }
        else{
            ans = mid;
            high = mid - 1;
        }
    }

    return ans;
}

int BinarySearch_MaxSmaller(int* arr, int length, int key){
    int low = 0;
    int high = length - 1;
    int mid;
    assert(high>=low);

    int ans = -1;

    while(high >= low){
        mid = (high+low) / 2;
        if (key <= arr[mid]){
            high = mid - 1;
        }
        else{
            ans = mid;
            low = mid + 1;
        }
    }

    return ans;
}

int NumItemSmaller_Sorted(int* arrSorted, int length, int key){
    int Isort = BinarySearch_MaxSmaller(arrSorted, length, key) + 1;
    return Isort;
}

int NumItemSmaller_Screen(int* arr, int str, int end, int key){
    int numSmaller = 0;
    if (str>end)
        swap(&str, &end);
    for (int i=str; i<=end; i++){
        if (arr[i] < key)
            ++numSmaller;
    }
    return numSmaller;
}

MinMax findMinMax(int* arr, int str, int end){
    if(str>end){
        swap(&str, &end);
    }
    MinMax mx = {
        .max = arr[str],
        .min = arr[end]
    };
    int val;
    //Search
    for(int i=str;i<=end;i++){

        val = arr[i];

        if (mx.max < val)
            mx.max = val;
        
        if (mx.min > val)
            mx.min = val;    
    }

    return mx;
}

/** * Update minmax*/
int update_MinMax(MinMax* dst, int min, int max){
    int isChanged = 0; 

    if (dst->max < max){
        dst->max = max;
        ++isChanged;
    }
    if(dst->min > min){
        dst->min = min;
        ++isChanged;
    }
    return isChanged;
}


/*TESTING*/
array init_array(){
    array list;
    int* arr = (int*)malloc(sizeof(int)*100006);
    list.len = 0;
    list.arr = arr;
    return list;
}
int insert_array(array* list, int i, int x){
    ++(list->len);
    insert_arr(list->arr, i-1, x, list->len);
    return list->len;
};

int delete_array(array* list, int i){
    remove_arr(list->arr, i-1,list->len);
    --(list->len);
    return list->len;
}
int reverse_array(array* list, int l, int r){
    reverse_arr(list->arr, l-1, r-1);
    return list->len;
}

int query_array(array* list, int l, int r, int k){
    array cpy = init_array(); 
    memcpy(cpy.arr, list->arr, list->len * sizeof(int) ); 

    quicksort(cpy.arr, l-1, r-1);
    int val = cpy.arr[l-1 + k-1];
    free(cpy.arr);

    return val;
}