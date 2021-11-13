# Problem 1: Greatest Common Divisor of Big Integers (Programming)

## Binary Algorithm

<img width="1343" alt="Screen Shot 2021-03-04 at 7 33 08 PM" src="https://user-images.githubusercontent.com/29009898/109957840-7462f580-7d20-11eb-9d7e-22b054703eb7.png">


## Usage

Use keyboard to set up two numbers for GCD calculation (<= 256 digits for each)
```bash
make RUN
12 3
3
```

## Prerequisite 

See [manual](https://github.com/stevengogogo/CProjectTemplate).


## 字元輸入 `scanf` 


```c
#include <stdio.h>

int main(void) {
    int input;

    printf("請輸入數字：");
    scanf("%d", &input);

    printf("你輸入的數字：%d\n", input);

    return 0;
}
```

- 告知程式儲存資料的變數位址，為此，必須使用 `&` 取址運算子
- **字元陣列名稱**本身就有**位址資訊**，故不用 `&` 來取址


## Memory Management

`malloc`,   `free`, `calloc` 和 `realloc` 是 C 語言配置記憶體空間的方法.

- Stack
    - > 到目前為止，變數建立後會配置記憶體空間，這類資源是配置在記憶體的堆疊區（Stack），生命週期侷限於**函式執行期間**，也就是函式執行過後，配置的空間就會自動清除。

- Heap
    - > 若要將函式執行結果傳回，不能直接傳回這類被自動配置空間的位址，因為函式執行過後，該空間就會釋出，函式呼叫者後續若透過位址取用這些資源，會發生不可預期的結果，例如，不能直接將區域建立的變數位址或陣列位址傳回。

    - > 然而程式運行後，資源之間的互用關係錯綜複雜，有些資源「無法預期」被使用的生命週期，因為無法預期，也就有賴於開發者自行管理記憶體資源，也就是開發者得自行在需要的時候配置記憶體，這些記憶體會被配置在堆積區（Heap），不會自動清除，開發者得在不使用資源時自行釋放記憶體。

### 範例

- `malloc`: 配置空間但不回傳值
    -  配置一個 `int` 大小的記憶體
        ```c
        int *p = malloc(sizeof(int));
        ```
    - Array
        ```c
        ptr = (float*) malloc(100 * sizeof(float));
        ```
        > The above statement allocates 400 bytes of memory. It's because the size of float is 4 bytes. And, the pointer ptr holds the address of the **first byte** in the allocated memory.

- `calloc`: 配置空間與初始值
    ```c
    int *p = calloc(1, sizeof(int));
    ```
- `free`: 釋放記憶體
    ```c
    int *p = malloc(100);
    free(p);
    ```


## Fill the array: [`memset` function](https://www.geeksforgeeks.org/memset-c-example/)

```c
int number[5];
memset(number, 0, sizeof(number)); //zero array
```

## Division in English

![https://www.learnalberta.ca/content/memg/videos/Divisor02/Divisor02-poster.jpg]()

## File IO

### Read from a text file

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int num;
   FILE *fptr;

   if ((fptr = fopen("C:\\program.txt","r")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }

   fscanf(fptr,"%d", &num);

   printf("Value of n=%d", num);
   fclose(fptr); 
  
   return 0;
}
```

## 如何安全清除記憶體

> 當 heap 在釋放之前配置的記憶體時，並不一定會把這些釋放的記憶體直接還給系統，它通常會把這些釋放的記憶體先保留下來，等到程式接下來又需要配置動態記憶體時，再拿出來繼續使用。

### 記憶體重複釋放(Double Free)

```c
char *name = (char*) malloc(...);
// ...
free(name);     // First free
// ...
free(name);     // Double free
```

當遇到別名的 pointer 時更難檢查. 

- Double free 的解決方法

```c
char *name = (char*) malloc(...);
// ...
free(name);
name = NULL;
```

- 避免資料外洩

```c
char *name = (char*)malloc(...);
// ...
memset(name,0,sizeof(name));
free(name);
```

但會對效能造成負擔


## Result

![Screen Shot 2021-03-14 at 9 27 02 PM](https://user-images.githubusercontent.com/29009898/111070284-07174780-850c-11eb-94ae-6bc4ab86a209.png)

## Remarks

1. Fastest implementation in class is `2ms` (mine: `6ms`)
2. @sosiristseng recommended to store [0, 9999] in one `Int` to speed up the process. To say, merging the operation and exploiting the int data type can triple the speed.

---

## Reference
1. BigInt in C [[gist](https://gist.github.com/bloopletech/338338)]
2. 簡明 C 語言入門教學. [[link](https://blog.techbridge.cc/2020/05/03/simple-c-language-introduction-tutorial/)]
3. Simple MakeFile Tutorial. [[link](https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)]
4. 單元測試 - acutest. [[Github](https://github.com/mity/acutest), [C Example](https://github.com/mity/acutest/blob/master/examples/c-example.c)]
5. 字元輸入 `scanf`. [[blog](https://openhome.cc/Gossip/CGossip/PrintfScanf.html)]
6. `printf` 字元. [[tutorial](https://www.cplusplus.com/reference/cstdio/printf/)]
7. Memory Management
    - malloc、free、calloc 與 realloc. [[blog](https://openhome.cc/Gossip/CGossip/MallocFree.html)]
    - Syntax Example. [[tutorial](https://www.programiz.com/c-programming/c-dynamic-memory-allocation)]
    - Dynamic memory allocation. [[wiki](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation)]
8. Pointer 整理. [[blog](http://hackgrass.blogspot.com/2018/03/c-pointerint-foo-int-bar.html)]
9. Do not use sizeof for array parameters. [[GreekforGeek](https://www.geeksforgeeks.org/using-sizof-operator-with-array-paratmeters/)]
10. `Makefile` tutorial. [[tutorial](https://makefiletutorial.com/)]
11. `i++` or `++i`. [[web](https://nwpie.blogspot.com/2017/07/5-i-i.html)]
12. Free a struct. [[StackOverFlow](https://stackoverflow.com/questions/13590812/c-freeing-structs]]
    - constructor [[stack](https://stackoverflow.com/questions/537244/default-constructor-in-c)]
    - Build struct. [[stack](https://stackoverflow.com/questions/3774193/constructor-for-structs-in-c)]
13. Pass an array to function. [[issue](https://github.com/stevengogogo/DataStructureAlgorithm/issues/3)]
)]
14. Flexible array in struct. [[greekforgeek](https://www.geeksforgeeks.org/variable-length-arrays-in-c-and-c/)]
15. Read text file. [[Pragramiz](https://www.programiz.com/c-programming/c-file-input-output), [GreekforGeek](https://www.geeksforgeeks.org/basics-file-handling-c/)]
16. 如何安全清除記憶體 `free`. [[Blog](https://blog.gtwang.org/programming/memory-deallocation-issues-in-c/)]
17. C language doesn't suuport nested function. [[GreekforGeek](https://www.geeksforgeeks.org/nested-functions-c/)]
