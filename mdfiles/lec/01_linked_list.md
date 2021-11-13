# Arrays and Linked Lists

<iframe width="560" height="315" src="https://www.youtube.com/embed/by2jcmzeebs" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

---

# 如何證明演算法正確?

## Loop invariance

After `i-th` iteration of the `for` loop, `arr[m]` is always the smallest among `arr[0]`,...., `arr[i]`
- true when `i=0`
- true when `i=k` → true when `i=k+1`

### 證明

- 先寫要證明什麼
- 看看離散數學的內容

## Efficiency of Algorithm

- Sequential search
- Binary search

## Pseudo code for `getMinIndex`

### Linear serach

```c
int getMinIndex(int arr[], int len){
	int i;
	int m=0;
	for(i=0;i<len;i++){
		if (arr[m] > arr[i]){
			m=i;
		}
	}
}

```

```c
GET-MIN-INDEX(A)

m = 1
for i = 2 to A.length
	if A[m] > A[i]
		m = i

return m

```

### Selection sort

![image](https://user-images.githubusercontent.com/29009898/110298600-b9906b80-802f-11eb-9d9e-55b1f2f927eb.png)


## What is data structure?

- Scheme of organizing data within computer
- 快: 常常用的東西取的快
- Good data structure needs proper maintenance algorithms:
    - `Construct` / `Update` / `remove`

## Why data structures and algorithms?

- Data structures
    - Storage
    - Network, bandwidth
- Algorithms
    - Computation

## Proper use: Tradeoff of different factors

# C Programming  versus DSA

- Test
    - 怎麼測試程式碼
    - 設計關鍵情形
- Modualize
    - 模組化
- Tradeoff
    - Theory
    - Practice

# What is Array?

- Index
- Memory is array
- Address
    - `arr[index]` , `memory[address]`
- C programming
    - Pointer

## Array as memory block in C

- Access: `arr[index]` → `memory[arr + index * sizeof(data)]`
    - Array 可以快速 update 和拿出來
- Maintenance: `malloc(sizeof(data)*length)`
    - construct (length)

![image](https://user-images.githubusercontent.com/29009898/110298769-ee9cbe00-802f-11eb-9461-cf2c5cac1088.png)
       

- Garbage collection

# Orderred array

![image](https://user-images.githubusercontent.com/29009898/110298847-0116f780-8030-11eb-8efe-de5e00896c29.png)

## 可以試試 實做 orderred array

- Insertion
- remove

# Sorting

## Insertion Sort

$O(n^2)$ 

![](https://user-images.githubusercontent.com/29009898/110297582-a335e000-802e-11eb-94dd-322eb7caccb2.png)

## Selection Sort

$O(n^2)$ 

![Untitled 1](https://user-images.githubusercontent.com/29009898/110297584-a3ce7680-802e-11eb-8400-65c32a2ae1ca.png)

# Sequential search algorithm

---

# 作業0

![Untitled](https://user-images.githubusercontent.com/29009898/110297587-a4670d00-802e-11eb-9c69-6fe3de90e824.png)

- 會走到沒有 define 的地區
- 執行錯誤
- `ary[-4]`
- `segmentation fault` 每次呼叫都是系統給空間，如果取用非法空間就是 `segmentation fault`