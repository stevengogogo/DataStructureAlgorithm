# Performance Evaluation

<iframe width="560" height="315" src="https://www.youtube.com/embed/C15ytqWQEdA" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

---

## Online judge:  可以加速到 0.0002ms?

<img width="652" alt="Screen Shot 2021-03-09 at 1 41 27 PM" src="https://user-images.githubusercontent.com/29009898/110424065-26157400-80dd-11eb-90c4-e75d97130eae.png">


## Ordered array

### Sequential search algorithm with cut

<img width="590" alt="Screen Shot 2021-03-09 at 1 45 43 PM" src="https://user-images.githubusercontent.com/29009898/110424424-beabf400-80dd-11eb-8900-5e1916f6f717.png">

- 尋找 `5`
    > Sequential search 尋找 `5` 從頭開始一個一個找, 找到 `>5` 斷掉.

- 尋找 `6`
    > 尋找 `6` 直接砍半, 沒找到代表沒有

### Binary search algorithm
使用 ordered array. 一次砍掉一半的人. 快速建立在 sorting

> [!tip]
> 一定要 Binary search 嗎？不能用三分, 四分?
>
> - 多分法比較是有用途的. 
> - 多分法要拿多個位置一次拿出來, 二分法是一次比一個

> [!tip] 多分法適合用 parallel processing 嗎?
>
>  是



> [!tip] Parser 
>
> Parser 是把 code 的結構抓出來, 把寫的程式翻譯成樹狀結構
> NLP 中: Parser 是把語言中的主詞等抓出來

## Singly Linked List

![image](https://user-images.githubusercontent.com/29009898/110426127-7cd07d00-80e0-11eb-9662-ce677331a26d.png)

- `Array` 和 `linked list` 是 DSA 的兩大基石: 常常考, 要會分辨

### Application: Polynomial computation

- Polynomial function 

$$f(x) = 5x^{9} - 7x^{4} + 3$$

- Storage
|Element|$5x^9$|$-7x^4$|$+3$|
|---|---|---|---|
|Storage|`(5,9)`|`(-7,4)`|`(1,3)`|


#### Solution 1: 2D array

|Constant|Power|
|:---:|:---:|
|5|9|
|-7|4|
|3|0|

> [!warning]
> what if append $4x$
> Ordered array 要重排, 但如果 array 滿了

|<img width="763" alt="Screen Shot 2021-03-09 at 2 21 40 PM" src="https://user-images.githubusercontent.com/29009898/110427466-c4f09f00-80e2-11eb-82d2-80bc9a14f34a.png">|<img width="761" alt="Screen Shot 2021-03-09 at 2 22 54 PM" src="https://user-images.githubusercontent.com/29009898/110427579-f10c2000-80e2-11eb-93c5-ddc55cab8db8.png">|
|---|---|

- Linked list
    - 每一次存資料都要說下一個點在那裡
    > [!tip]
    > link list 是個花力氣 construct 的東西, 但是能夠方便放置 (`flexibility`). `allocate` 任何一個東西再連上就好. 
    > 相比 array 需要重新排序

    > [!warning]
    > linked list 要收拾記憶體很花力氣, 一個一個找

    >[!warning]
    > 最後一個要告訴結束 (`NULL` *回家*)
    > <img width="763" alt="Screen Shot 2021-03-09 at 2 32 10 PM" src="https://user-images.githubusercontent.com/29009898/110428457-3c72fe00-80e4-11eb-8e2b-dd56e1f1a03e.png">


> [!tip] 如果需要 sorting 的話, linked list 會比 array 好嗎?
> 
> 速度上 linked list 會比較慢, 因為記憶體不連續. **linked list 很慢**. linked list 主要好處是 **flexibility**

> [!warning]
> linked list 會浪費記憶體

## Differences between `List` / `Array` / `Struct` ?

- list
    - 有 data
    - 有 pointer (1 or 2 個)
    - 記憶體不連續
- array:
    - same type and indexed
    - 記憶體連續

- struct: 
    - 是一種把 多個 data variables 組合的方式
    - 類似 `tuple`
    - 記憶體連續

<!-- panels:start -->
<!-- div:title-panel -->

### Int and Struct can be the same

<!-- div:left-panel -->

```c
int a=1;
```



<!-- div:right-panel -->

```c
struct a {
    int num;
};
struct a = {1};
```

<!-- panels:end -->

<img width="1435" alt="Screen Shot 2021-03-09 at 3 06 33 PM" src="https://user-images.githubusercontent.com/29009898/110431656-0a17cf80-80e9-11eb-87d7-40611542dc4a.png">


## Singly Linked List as ADT: Maintenance

|Maintenance|Access|
|:---:|:---:|
|<img width="789" alt="Screen Shot 2021-03-09 at 3 30 56 PM" src="https://user-images.githubusercontent.com/29009898/110434179-747e3f00-80ec-11eb-80c1-1906dcada0ba.png">|<img width="765" alt="Screen Shot 2021-03-09 at 3 34 35 PM" src="https://user-images.githubusercontent.com/29009898/110434582-f5d5d180-80ec-11eb-9585-e201b2b85320.png">|

> [!info]
> ADT: Abstract Data Structure $\leftrightarrow$ Concrete Data Structure

> [!info]
> `gethead`: 要拿到 head 這個 pointer


---

## Double linked list

![image](https://user-images.githubusercontent.com/29009898/110432749-7b0bb700-80ea-11eb-9deb-ad4f9f525704.png)

為什麼需要 double linked list.

### Reason: `removehere` for Singly Linked List

- `removeHere` 和 `insertHere` 都需要找到前一個 element
- Singly linked list 移除很麻煩, 因為不知道前一個是誰？
    <img width="661" alt="Screen Shot 2021-03-09 at 3 11 55 PM" src="https://user-images.githubusercontent.com/29009898/110432204-ca051c80-80e9-11eb-81b7-f891756feda1.png">

> [!tip] 每一個 node 兩張紙條紀錄前後位置
>
> <img width="613" alt="Screen Shot 2021-03-09 at 3 14 39 PM" src="https://user-images.githubusercontent.com/29009898/110432497-2bc58680-80ea-11eb-9f32-76ddd858c643.png">

### Application: Sparse vector in Scientific computing

- Machine learning 常有高維度的 array
- 向量內積
    <img width="692" alt="Screen Shot 2021-03-09 at 3 19 01 PM" src="https://user-images.githubusercontent.com/29009898/110432928-c756f700-80ea-11eb-86fa-248cef111c6d.png">
    - 如果有很多 $0$, 會浪費很多運算資源.

#### Sparse Vector: (Dense) Array vs. Linked list

- Dense array 如果存了一堆 $0$ 會花很多力氣.
- Linked list 可以省空間又省時間

#### LIBSVM: NTU CSIE 最廣為被使用的模型

<img width="687" alt="Screen Shot 2021-03-09 at 3 26 06 PM" src="https://user-images.githubusercontent.com/29009898/110433704-c5416800-80eb-11eb-9120-40157c5587ee.png">

- sparse vector
- `index`: 小紙條. `-1` 是底


## `malloc` 要記得 `free`
- 養成使用記憶體要還的習慣
- Garbage collection (GC)


## Linked list requires atomic operation in parallel processing

> [!tip]
> <img width="926" alt="Screen Shot 2021-03-09 at 3 50 05 PM" src="https://user-images.githubusercontent.com/29009898/110436378-1ef76180-80ef-11eb-93da-6b633d24b9db.png">
>
> linked list 在 parallel processing 時，如果 removal 時可能執行到一半，產生的 NULL pointer 造成 segmentation fault.
> 所以平行程式需要 [Atomic operation](https://riptutorial.com/c/example/17383/atomics-and-operators).


## Time Complexity


### Matrix Addition

<img width="744" alt="Screen Shot 2021-03-09 at 3 56 29 PM" src="https://user-images.githubusercontent.com/29009898/110437149-0471b800-80f0-11eb-924f-23587be887b5.png">

- $R = P \cdot cols +  Q = rough(cols)$
- $(S+R) \cdot rows + T = rough(rough(cols) \cdot rows)$
- $\rightarrow$ rough time needed: rough(rows$\cdot$cols)

> [!tip]
> $Q$ 和 $T$ 指的是 `for loop` 的條件式判斷


### Asymptotic Notation

- Goal
    rough rather than exact steps
- Why rough?
    constant not matter much
    - When input size $n$ is large

### Big - $O$ : Upper bound

Asymptotic intuition:

$$\lim_{n\rightarrow \infty}\frac{f(n)}{g(n)}\leq c$$

- $O$ 描述花的計算量, 記憶體 和 網路傳輸的使用
- $f(n) \in O(g(n))$ 在 CS, 習慣用 $f(n) = O(n)$
