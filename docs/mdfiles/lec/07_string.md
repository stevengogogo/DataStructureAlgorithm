# String Matching


<iframe width="560" height="315" src="https://www.youtube.com/embed/8hyChVu-hvc" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

---

## Agenda

|<img  alt="Screen Shot 2021-04-27 at 1 27 08 PM" src="https://user-images.githubusercontent.com/29009898/116189915-461bf800-a75c-11eb-8105-496fd36c0ac7.png">|<img  alt="Screen Shot 2021-04-27 at 1 29 44 PM" src="https://user-images.githubusercontent.com/29009898/116190126-a448db00-a75c-11eb-869f-e4061732972d.png">|
|---|---|

- 一週搭配 2 題
- 題目要在上課之前完成
- In-class quizzes 要在課堂或午夜前完成
- 課堂活動分組

## String matching algorithms

<img width="630" alt="Screen Shot 2021-04-27 at 1 19 33 PM" src="https://user-images.githubusercontent.com/29009898/116189236-36e87a80-a75b-11eb-8d21-02f964e47778.png">

## Time complexity

- `strncmp`:
  - `str1`
  - `str2`
  - `n`

## String Matching problem

<img width="535" alt="Screen Shot 2021-04-27 at 1 58 07 PM" src="https://user-images.githubusercontent.com/29009898/116192556-9b5a0880-a760-11eb-8096-b8d4e584e7d9.png">

## 笨蛋暴力法

```pseudo
for s=0 to n-m
  if P[1...m] == T[s+1...s+m]
    return s
```

- Value of stupid methods
  - 不容易寫錯
  - 可讀性高

- Source of inefficiency
  - The information is lost when next comparison starts.

- `P[1...m]`: 是全部都比的意思
- Complexity
  $$O(nm-m^2) = O(nm)$$


## Rabin-karp Algorithm

<img src="https://user-images.githubusercontent.com/29009898/116196512-30abcb80-a766-11eb-86a5-d4028a38de7c.png">

- 每一個 shift 都確定 `sum`
- `checksum` 如果 sum 相等, 則必定 string 相等

- 製造檢查碼: 把字串看成 $|\sum|$ 進位數
  - $\sum = \{ 0,1, \cdots, 9 \}$
  - 則 $|\sum| = 10$


### 計算檢查碼

<center>
<img width="342" alt="Screen Shot 2021-04-27 at 2 45 34 PM" src="https://user-images.githubusercontent.com/29009898/116197339-3bb32b80-a767-11eb-92e4-a52c08efb936.png">
</center>

$$P[m] + 10\cdot(P[m-1] + 10(P[m-2] + \cdots + 10(P[2] + 10[1])))$$


- 移動: constant time
  - 往右一格
    - $t_s = 10^{m-1} \cdot T[s+1] + A$
    - $t_{s+1} = A\cdot 10 + T[s+m+1]$
- 總共: linear time


```pseudo
preprocess: Calculate to P

if t0 == P return 0
for S=1 to n-m # n-m 次
  calculate ts # O(1)
  if ts==p # 數字比較 O(1)
    return s 
```

- Complexity:
  - linear time

- Problem:
  - Checksum is too **large***. 字串加起來可能會是很大的數字

### 修正: 同餘定理

<img src="https://user-images.githubusercontent.com/29009898/116198753-f09a1800-a768-11eb-8d2a-6af580b557eb.png">

- 用 mod 的性質
- 一般選質數

<img src="https://user-images.githubusercontent.com/29009898/116198969-3060ff80-a769-11eb-94f4-a0fa8583d163.png">


<img src="https://user-images.githubusercontent.com/29009898/116199206-71591400-a769-11eb-95cd-cb6721e6d4e1.png">

- 如果檢查碼一樣, 第一個字元比到最後一個字元
  - 回復到 $O(nm)$
  - 但是很少發生


### Code

```pseudo
n = T.length
m = P.length

h = d^{m-1} mod q

P=0, t=0

for i = 1 to m
  p = (dp + p[i]) mod q
  t = (dt + T[i]) mod q
for s = 0 to n-m
  if p==t
    if p== T[s+1...s+m]
```


## Knuth-Morris-Pratt Algorithm

> [!info] 期末考會考 

<img  src="https://user-images.githubusercontent.com/29009898/116204158-0b6f8b00-a76f-11eb-8e48-eee3f7cf5a84.png">






--

## In-Class Quiz

### Week 10 In-Class: Problem 1 
> Take a look at #5 in the slide. If each character in the pattern P is unique, then how can you improve the naive algorithm in O(n)? Please explain why using an example.

If all the character in P is unique and mismatches the subarray in the beginning, the shift `s` within `[1:length(P)-1]` will surely mismatch due to the uniquiness. Therefore, we can speed up the algorithm by skipping `length(p)-1` steps when a mismatch occurs.

In the following example, the pattern jumps two steps forward.

```
String
Pattern
```

```
AABAABC
ABC
```

```
AABAABC
  ABC
```

```
AABAABC
    ABC
```

> [!tip] 更正: 從不相等的地方從新比對一次. Linear time algorithm
> <img  src="https://user-images.githubusercontent.com/29009898/116196365-fb9f7900-a765-11eb-9dd8-7ff17725eed8.png">