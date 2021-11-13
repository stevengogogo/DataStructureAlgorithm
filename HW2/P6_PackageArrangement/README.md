# Package Arrangement

Keywords: `Queue`, `Stack`, `Binary Tree (search, insert, delete, remove, balance)`

## Usage

See [Problem Statement](Problem.pdf)

## Problem statements

- `L` production lines
- `N` packages
- `O` Operations


## Strategy

![image](https://user-images.githubusercontent.com/29009898/117527886-ce728680-b001-11eb-81c1-351902775993.png)


- Production line
  - Binomial Max Heap
    - Doubly linked list
  - Deque
    - First-in-First out
    - Doubly Linked list
      ```julia
      struct
        int[] array
        int* next_array
        int* prev_array
      end
      ```
      ![image](https://user-images.githubusercontent.com/29009898/117526184-0378dc00-aff6-11eb-9412-193ce3edf516.png)

- Peaking a production line
  - `getFirst`: `O(1)`
  - `getLast`: `O(1)`
  - `getMax`: `O(1)`

- Operation
  - `PopFirst`: `O(n)`
  - `PopLast`: `O(n)`
  - `PopMax`: `O(log n)`

- Merge Production line
  - Deque
## Queue


## Stack 


## Binary Tree Operation


### What is a "balanced" binary tree?



**Ref**: 
- [Balancing a binary search tree (GO)](https://appliedgo.net/balancedtree/)




## AVL Tree


**Ref**
- [Balancing a binary search tree (GO)](https://appliedgo.net/balancedtree/)
- [AVL Tree: Insertion (GreekforGeek)](https://www.geeksforgeeks.org/avl-tree-set-1-insertion/)
- [AVL Tree: Deletion (GreekforGeek)](https://www.geeksforgeeks.org/avl-tree-set-2-deletion/)
- [資料結構與演算法：AVL Tree](https://josephjsf2.github.io/data/structure/and/algorithm/2019/06/22/avl-tree.html)

### Time complexity with AVL Tree

|Operation|Time|
|:---:|:---:|
|Search|O(log n)|
|Insert|O(log n)|
|Delete|O(log n)|

- Advantage of using AVL Tree
  - Guarantee: O(log n) for binary search

**Ref**:
- [資料結構與演算法：AVL Tree](https://josephjsf2.github.io/data/structure/and/algorithm/2019/06/22/avl-tree.html)



## Idea

- Merge 要求 `log(n)`

## Hints

- 用 Heap: 快速找到 max, first, last
- Time complexity of merge: <O(n)
    - 方法: https://abitofcs.blogspot.com/2019/06/merging-heaps-in-olog-n.html
    - https://cs.stackexchange.com/questions/82793/merge-2-binary-heaps
    - https://medium.com/100-days-of-python/day-06-binomial-heap-88ca2edb8255
    - https://en.m.wikipedia.org/wiki/Binomial_heap


## Heap Operations

<img width="368" alt="Screen Shot 2021-05-08 at 12 03 07 PM" src="https://user-images.githubusercontent.com/29009898/117526088-5d2cd680-aff5-11eb-81df-c135e8654434.png">
<img width="392" alt="Screen Shot 2021-05-08 at 12 03 30 PM" src="https://user-images.githubusercontent.com/29009898/117526093-69189880-aff5-11eb-9402-9edd42a60745.png">
<img width="341" alt="Screen Shot 2021-05-08 at 12 03 41 PM" src="https://user-images.githubusercontent.com/29009898/117526099-6fa71000-aff5-11eb-87a3-b8877f276d8f.png">
<img width="437" alt="Screen Shot 2021-05-08 at 12 03 52 PM" src="https://user-images.githubusercontent.com/29009898/117526106-76358780-aff5-11eb-86ac-a091dee90265.png">
<img width="335" alt="Screen Shot 2021-05-08 at 12 04 14 PM" src="https://user-images.githubusercontent.com/29009898/117526117-83527680-aff5-11eb-9021-f2b2f5dac965.png">


## Free a binary tree

```
deallocate (node):
    //do nothing if passed a non-existent node
    if node is null
        return

    //now onto the recursion
    deallocate(left node)
    deallocate(right node)

    free node
```

Ref: [stackoverflow](https://stackoverflow.com/questions/9181146/freeing-memory-of-a-binary-tree-c)


## Returning a void function

Ref: [web](https://www.cs.fsu.edu/~cop3014p/lectures/ch7/index.html)

## Function pointer

```c

#include <stdio.h>
// A normal function with an int parameter
// and void return type
void fun(int a)
{
    printf("Value of a is %d\n", a);
}
  
int main()
{ 
    void (*fun_ptr)(int) = fun;  // & removed
  
    fun_ptr(10);  // * removed
  
    return 0;
}
```

Ref: [GreekforGeek](https://www.geeksforgeeks.org/function-pointer-in-c/)



### Array of function pointers

```c
int (*fun[3])(packData, int)=  {PeekFirstPack, PeekLastPack, PeekMaxPack};
```

### What are Mutually Dependent Structures in C?

- Partial declaration

- Ref: [What are Mutually Dependent Structures in C?](https://www.sanfoundry.com/c-tutorials-mutually-dependent-structures/)



## Leftist tree






Ref:
1. https://tmt514.gitbooks.io/2016-09/content/tree-ds/leftist-tree.html
2. http://sunmoon-template.blogspot.com/2014/12/leftist-tree.html
3. https://www.humblec.com/c-implementation-leftist-tree/
4. [Tutorial: Leftist Tree](https://www.dgp.toronto.edu/public_user/JamesStewart/378notes/10leftist/)


## References
1. Stack, Queue and Heap. [[GitBook](https://stephanosterburg.gitbook.io/scrapbook/coding/coding-interview/data-structures/heaps-stacks-queues)]
2.

