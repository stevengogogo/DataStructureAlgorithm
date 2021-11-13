# Heap

<iframe width="560" height="315" src="https://www.youtube.com/embed/DRchPyf4shk" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

---

## What have we learned last week?

- Stacks implemented on Array
- Stack 常用 array 實現. 省下記憶體空間
- But sometimes, for storing **complex data structure**, linked list can be used in this scenerio.

## Dynamic array of stack

- 當記憶體滿了, 增加
    <img width="513" alt="Screen Shot 2021-03-23 at 1 47 21 PM" src="https://user-images.githubusercontent.com/29009898/112099331-4b76a780-8bde-11eb-8abe-9ae14b018405.png">
- 增加這個操作的時間複雜度?
    - [Efficiency of growing a dynamic array by a fixed constant each time?](https://stackoverflow.com/questions/19146037/efficiency-of-growing-a-dynamic-array-by-a-fixed-constant-each-time)
- 放在尾端的 linked list 的缺點
    - single linked list 倒退很難
    - single linked list 尾巴必須是終止符號
- Stack 是一種概念, 用 array 實作是一種方法 / linked list 也是

## Implement a linked list

```c
typedef struct {
    int data;
    struct node* next;
} node;
```

- 第一部分 `data`: 存資料
- 第二部份 `node*`: 下個資料的欄位

## Agile Development

- 快速反應需求
- 相比: waterfall development
    <img src="https://d2q275vdzul5bt.cloudfront.net/vassets/c26e1264e5f5966c21553b49145c6e1935d2d350/PM-agile-waterfall.jpg" height=300>

## Stack for Expressoin Evaluation

$$a/b - c + d * e - a * c$$

- Precedence (優先權): $\{*,/\}$ first; $\{+,-\}$ later
- Postfix
- 大部分 compiler 會用 parse tree 來翻譯成機器碼


## Java to C

- Stack 


## A general maze algorithm

<img width="735" alt="Screen Shot 2021-03-23 at 3 52 47 PM" src="https://user-images.githubusercontent.com/29009898/112111931-d3b17880-8bef-11eb-9348-075f5cf261d8.png">

- Stack version
    - Depth-first search
- Queue version
    - Breadth-first search
    - Shortest way out

- A* Algorithm [[link](http://blog.minstrel.idv.tw/2004/12/star-algorithm.html)]

## Queues

- Object
    - A container that holds some elements
- Action
    - Enqueue (to the rear), dequeue (from the front)
- First-in-first-out (FIFO)

## Queues Implemented on Circular Array

- Enqueue: 把東西塞進去
- Dequeue: 把東西拿出來


### 用 growable array 會發生的問題

- 浪費空間
    - dequeue 的空間無法使用
      <img width="727" alt="Screen Shot 2021-03-23 at 4 08 33 PM" src="https://user-images.githubusercontent.com/29009898/112113630-05c3da00-8bf2-11eb-927c-aeba0b1f4ddb.png" height=300>
- 用 circular array 來平衡
    - 用取餘數來循環
       <img width="643" alt="Screen Shot 2021-03-23 at 4 10 19 PM" src="https://user-images.githubusercontent.com/29009898/112113802-43c0fe00-8bf2-11eb-8b47-c411fd0cf7e2.png" height=300>


## Deques

- Deque = Stack + Queue + Push_front
- Implementation
    - Circular array (難)
    - doubly-linked list (簡單)