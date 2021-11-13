# Nonogram Solver

[![Ubuntu](https://github.com/stevengogogo/NonogramSolver/actions/workflows/ci.yml/badge.svg)](https://github.com/stevengogogo/NonogramSolver/actions/workflows/ci.yml)[![codecov](https://codecov.io/gh/stevengogogo/NonogramSolver/branch/main/graph/badge.svg?token=5F6B6C9M1K)](https://codecov.io/gh/stevengogogo/NonogramSolver)[![Doxygen Action](https://github.com/stevengogogo/NonogramSolver/actions/workflows/doc.yml/badge.svg)](https://github.com/stevengogogo/NonogramSolver/actions/workflows/doc.yml)[![Dev](https://img.shields.io/badge/docs-dev-blue.svg)](https://stevengogogo.github.io/NonogramSolver/)


![](https://user-images.githubusercontent.com/29009898/110197098-19e2aa00-7e84-11eb-8e0c-396e6a0056a3.png)


## Greedy Alogrithm

![](https://user-images.githubusercontent.com/29009898/111065412-813bd200-84f4-11eb-9a3b-3383689e0812.png)

## How to measure the number of segments?

- Fills on the edge doesn't count

|Line|# Segments|Fills|Holes|
|---|---|---|---|---|
|`[0,0,0,0]`|0|`[]`|`[1,2,3,4]`|
|`[1,0,0,0]`|1|`[0]`|`[2,3,4]`|
|`[1,1,0,0]`|1|`[0,1]`|`[2,3]`|
|`[0,0,1,0]`|1|`[2]`|`[0,1,3]`|
|`[1,0,1,0]`|2|`[0,2]`|`[1,3]`|
|`[0,1,1,0]`|1|`[1,2]`|`[0,3]`|
|`[1,1,1,0]`|1|`[0,1,2]`|`[3]`|
|`[0,0,0,1]`|1|`[3]`|`[0,1,2]`|
|`[1,0,0,1]`|2|`[0,3]`|`[1,2]`|
|`[0,1,0,1]`|2|`[1,3]`|`[0,2]`|
|`[1,1,0,1]`|2|`[0,1,3]`|`[2]`|
|`[0,0,1,1]`|1|`[2,3]`|`[0,1]`|
|`[1,0,1,1]`|2|`[0,2,3]`|`[1]`|
|`[0,1,1,1]`|1|`[1,2,3]`|`[0]`|
|`[1,1,1,1]`|1|`[0,1,2,3]`|`[]`|

- Need a function that `f(arrFills) = # of segments`
  - idea ON-OFF flip flop
    - Add one when `0->1` occurs; reset when `1->0`
    - Time complexity: O(n)

```julia
#Julia
function seg_conunt(arr)
  count = 0 
  n_seg = 0
  for i in arr
    if count == 0
      if i == 1
        count = 1
        n_seg += 1
      end
    else
      if i == 0
        count = 0
      end
    end
  end

  return n_seg
end
```

## Create 2D array with double pointer and one malloc call

```c
#include<stdio.h> 
#include<stdlib.h> 
  
int main() 
{ 
    int r=3, c=4, len=0; 
    int *ptr, **arr; 
    int count = 0,i,j; 
  
    len = sizeof(int *) * r + sizeof(int) * c * r; 
    arr = (int **)malloc(len); 
  
    // ptr is now pointing to the first element in of 2D array 
    ptr = (int *)(arr + r); 
  
    // for loop to point rows pointer to appropriate location in 2D array 
    for(i = 0; i < r; i++) 
        arr[i] = (ptr + c * i); 
  
    for (i = 0; i < r; i++) 
        for (j = 0; j < c; j++) 
            arr[i][j] = ++count; // OR *(*(arr+i)+j) = ++count 
  
    for (i = 0; i < r; i++) 
        for (j = 0; j < c; j++) 
            printf("%d ", arr[i][j]); 
  
    return 0; 
} 
```

## Git tag

- Add tag
    ```sh
    git tag -a v0.0.1 -m "my version 1.4"
    ```
- Push tag
    ```sh
    git push origin v0.0.1
    ```

## Header files
> It is not recommended to put function definitions in a header file. Ideally there should be only function declarations. Purpose of this code is to only demonstrate working of header files. 

## Implementation of dynamic 1D array

```c
typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}
```

Usage

```c
Array a;
int i;

initArray(&a, 5);  // initially 5 elements
for (i = 0; i < 100; i++)
  insertArray(&a, i);  // automatically resizes as necessary
printf("%d\n", a.array[9]);  // print 10th element
printf("%d\n", a.used);  // print number of elements
freeArray(&a);
```
https://stackoverflow.com/questions/3536153/c-dynamically-growing-array

Use `realloc` to increase or shrink the size.


## How to read line in a file 

```c
void read_file(void){

    FILE *stream = fopen("test/data/output_1.txt", "r");
    char line[80];

    while ((fscanf(stream, "%[^\n]", line))!= EOF)
    {
        fgetc(stream); // Reads in '\n' character and moves file
        // stream past delimiting character
        printf("%s \n", line);
    }

    fclose(stream);
}

```

## Add test file 

'input_3.txt'
![](https://courses.engr.illinois.edu/cs440/fa2018/MPs/mp3/assignment3.html)


## Reference
1. 2D array construction. [[GreekforGeek](https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/)]
2. Git tag. [[Blog](https://git-scm.com/book/zh-tw/v2/Git-%E5%9F%BA%E7%A4%8E-%E6%A8%99%E7%B1%A4)]
3. Integer to string: `itoa`. [[Blog](https://www.cnblogs.com/oomusou/archive/2007/01/06/613413.html)]
4. Compare with `memcpy` [[Tutorial](http://tw.gitbook.net/c_standard_library/c_function_memcmp.html)]
    - 不能用於 struct [[reason](https://stackoverflow.com/questions/141720/how-do-you-compare-structs-for-equality-in-c)]
6. Memory management in C [[tutorial](https://www.guru99.com/c-dynamic-memory-allocation.html#5)]
7. fscanf: reading file in C. [[greekforgeek](https://www.geeksforgeeks.org/scanf-and-fscanf-in-c-simple-yet-poweful/)]
8. How to pass 2D array. [[GreekforGeek](https://www.geeksforgeeks.org/pass-2d-array-parameter-c/)]

