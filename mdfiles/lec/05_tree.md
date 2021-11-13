# Tree / Heap



<iframe width="560" height="315" src="https://www.youtube.com/embed/lyLHbkKWcHE" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

---


## What we have done?

- Stack:
  - LIFO
- Queue

## Data Structures

<img width="630" alt="Screen Shot 2021-03-30 at 1 28 49 PM" src="https://user-images.githubusercontent.com/29009898/112938247-dd8d2b80-915b-11eb-8b7d-795a8e9949af.png">

- Deque
    ![](https://i2.wp.com/learnersbucket.com/wp-content/uploads/2019/08/Deque-Data-Structure-1.png?fit=768%2C500&ssl=1)
    [Tutorial](https://learnersbucket.com/tutorials/data-structures/deque-data-structure-with-doubly-linked-list/)


## Formal Definition of trees

$$T = (root; T_1, T_2,...,T_n)$$

- Recursive definition
- Sub-trees $(T_1,..., T_n)$ disjoint
- Recursion termination?
    - When to stop?
    - 走到要停的地方
    - Subtree -> Leaf

## Structure of tree

<img width="538" alt="Screen Shot 2021-03-30 at 1 42 49 PM" src="https://user-images.githubusercontent.com/29009898/112939312-d23aff80-915d-11eb-9394-2eb5ca299d6b.png">

- 一個樹只有一個 root
- 沒有 subtree 的 node -> leaf
- Internal node -> 還沒到 leaf
- `Level`
  - 從 `0` 開始. 又稱為 `depth`
- 家族關係
  - `parent`
  - `child`
  - `sibling`

## Representing Trees with Linked Lists

<img width="321" alt="Screen Shot 2021-03-30 at 2 54 58 PM" src="https://user-images.githubusercontent.com/29009898/112946275-e683fa00-9167-11eb-8cf4-7c0b6e4d833e.png">

- 左邊: 最小的 Binary tree
- 右邊: 最大的 Binary tree

$$h+1 \leq n \leq 2^{h+1} - 1$$


- 如果 $n=1$ 則
  - $\log_2(n+1) -1 \leq h \leq n-1 $

- 樹的演算法複雜度與 `depth` 有關係
  - 如果有 n 個 data , 可以用 $\log_2(n+1) - 1$ 來得到



![](https://qph.fs.quoracdn.net/main-qimg-d37edec64bc1790d4ce47aaea6f77675)

- Perfect binary tree
  - a binary tree where all levels are completely filled
- Complete binary tree
  - a binary tree where all levels except the last one are completely filled and the last level is filled from left to right.


## Depth

|最少|最多|
|:---:|:---:|
|$\log_2(n+1) - 1$|$n-1$|



##  Indexing

<img width="609" alt="Screen Shot 2021-03-30 at 3 31 43 PM" src="https://user-images.githubusercontent.com/29009898/112950594-0833b000-916d-11eb-957f-9a8f8dd58e1e.png">


- 往下走
  - 左邊
    - $*2$
  - 右邊
    - $*2+1$
- 往上走  
  - `/2`
  - <img width="717" alt="Screen Shot 2021-03-30 at 3 37 31 PM" src="https://user-images.githubusercontent.com/29009898/112951358-d838dc80-916d-11eb-8f82-45ef188c6aad.png">

- 接近 `Full binary tree` 適合用 array 表達
  - Complete binary tree

### 練習

Complete binary tree 最多和最少幾個 node. node 數目和高度關係是什麼?

## Priority Queue: An Exmaple of Binary Tree

- 每次拿要拿最重要的出來


### Design of Priority Queue with `Tree`


<img width="787" alt="Screen Shot 2021-03-30 at 4 02 43 PM" src="https://user-images.githubusercontent.com/29009898/112954834-5cd92a00-9171-11eb-9f3c-b141cf61f86a.png">


- Entry point of a tree
  - 把最大的放在 `root`
  - 最快速得到最大值

- `removeLargest` needs 2nd largest to replace
  - Fast removal: put **2nd larget** close to next entry points

- max tree
  - root key $\geq$ other node's key
  - Every sub-tree is max tree




---

## Quiz 講解

### Week 5 - Question 3

- 迷宮問題
  - `Stack` 可以找到不見得是最短的
  - `Queue` 可以找到最短的
- 多出口迷宮
  - `Stack` 會找到**字母順序最短**的出口
  - `Queue` **最短**的出口


### Week 5 - Question 1

- `Queue` 可以用兩個 `stack` 模擬
  - linear time
- 跟自動機有關

### Project

- 課內的 data structure
- 不會有 time limit exceed (1min) 解越多越高分

---

## Appendix

### Appier

- 林軒田老師的公司: [Appier](https://www.104.com.tw/company/1a2x6biwai)



### Course Reading

- Representing rooted trees [10.4]
- 

### Further Reading  

- [Tutorial: Automata theory 自動機](https://www.tutorialspoint.com/automata_theory/index.htm)
- [Tutorial: Compiler](https://www.tutorialspoint.com/compiler_design/index.htm)


