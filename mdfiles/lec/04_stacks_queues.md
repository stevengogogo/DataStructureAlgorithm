# Stacks and Queues

<iframe width="560" height="315" src="https://www.youtube.com/embed/5FRFTQtK9Hw" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

---

## What we have done?

- linked list: 是比較 flexible 的方式
- Application
    - Sparse vector
- Trading space (next, pointer) for flexibility (memory allocation, operations)

## Asymptotic Notation

<img src="https://user-images.githubusercontent.com/29009898/111262451-42765b00-865f-11eb-9fef-3ae85b72c6c4.png" height=300>

- $f(n)$ 是資料量
- $f(n) = O(g(n))$
    - $f$ 怎麼跑都不會超過 $g$
- $\lim_{n\rightarrow \infty} \frac{f(n)}{g(n)} \leq c$

## More Intuitions of Big-$O$

- $O$ 是一個集合, 只要 $\in$ 都可以成立
    - $f(n) = O(g(n))$ 意思是 $f(n) \in O(g(n))$

- 性質
    - $f(n) \in O(g(n)) \leftarrow \lim_{n \rightarrow \infty} \frac{f(n)}{g(n)} \leq c$
- 舉例
    - $\in$: $n=O(n)$
    - $\leq$ : $n^2 = O(n^{2.5})$

- 把常數丟掉

- 求極值
    <img width="1145" alt="Screen Shot 2021-03-16 at 2 07 08 PM" src="https://user-images.githubusercontent.com/29009898/111263472-e8769500-8660-11eb-818e-e950cca84421.png">

## Formal Definition of Big-O

$$f(n) = O(g(n))$$

if-and-only-if, exist positive $n_0$ such that **$f(n)\leq c\cdot g(n)$** for all $n \geq n_0$

<img width="882" alt="Screen Shot 2021-03-16 at 2 47 08 PM" src="https://user-images.githubusercontent.com/29009898/111267118-7dc85800-8666-11eb-80aa-54a6165e9079.png">


## Definitoins of Aymptotic Notations

<img width="868" alt="Screen Shot 2021-03-16 at 2 50 45 PM" src="https://user-images.githubusercontent.com/29009898/111267524-ff1fea80-8666-11eb-980b-c3bb02c3529e.png">


- Big-O is the worse case scenerio.


## Seven functions as $g$

- 1: Constant
- $log n$: logarithmic (dose base matter? No.)
- $n$: linear
- $nlogn$
- $n^2$: square
- $n^3$: cubic 
- $2^n$: exppnential


## Analysis of Sequential search

```pseudo
for i = 1 to A.length
    if A[i] = key
        return i
return FALL
```

- Best case: 1
- Worst case: n
- linear complexity

## Analysis of Binary Search

- Best case: $\Theta(1)$
- Worst case: $\Theta(log n)$

### Input/Output

- Input: *any* integer array $A$ with size $n$, an integer array
- Output: `SUCCEED` / `FAIL`


## Sequential and Binary Search

<img width="873" alt="Screen Shot 2021-03-16 at 3 07 06 PM" src="https://user-images.githubusercontent.com/29009898/111269224-47400c80-8669-11eb-8f5b-0c09f2714620.png">

- Direct Seq Search: $O(n)$
- Sort and binary search: $O(n^2)$ time for selection sort and $O(log n)$


## Some properties of Big-O

### 封閉率

> ![tip]
> if $f_1(n) = O(g_2(n))$, $f_2(n) = O(g_2(n))$ then $f_1(n) + f_{2}(n) = O(g_2(n))$
>

### 併吞率

if $f(n) = a_{m}n^m$, $f(n) = O(n^{m})$

### 遞移率

- Binary-search: $O(log n)$
    - 也可以是: $O(n)$. 只要比 $log n$ 都成立
    - 通常希望 $O$ 寫出最接近的 worst case

## Comparison of complexity

<img width="775" alt="Screen Shot 2021-03-16 at 3 26 47 PM" src="https://user-images.githubusercontent.com/29009898/111271340-07c6ef80-866c-11eb-89d2-1990251e604c.png">

<img width="755" alt="Screen Shot 2021-03-16 at 4 49 30 PM" src="https://user-images.githubusercontent.com/29009898/111281550-06032900-8678-11eb-9c2b-4d3e77d3fed2.png">



## Appendix

- Master Theorem
![](https://img2018.cnblogs.com/blog/1263789/202002/1263789-20200201165308306-1640439629.png)

## Debugging a long-running segmentation is difficult

- 有 `segmentatoin fault` 是容易 debug 的
- 如果是跑很久才出現的，非常困難


# Stack

## Stack 的目的

- 放寬條件: Last-in-first-out
- 達到:
    - 放進去: Push
    - 拿出來: Pop

## Stack solution to paranthese

<img width="791" alt="Screen Shot 2021-03-16 at 3 59 07 PM" src="https://user-images.githubusercontent.com/29009898/111274926-8c1b7180-8670-11eb-85e0-8c1239eb0a85.png">

---

## Syllabus Update

### 期中期末考
- 不是上機考
- 手寫