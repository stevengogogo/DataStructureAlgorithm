# Tree and Sorting

<iframe width="560" height="315" src="https://www.youtube.com/embed/5h1CoHHCvLE" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Priority Queue with tree

- max tree
  - root key $geq$ other nodes's key
  - every sub-tree also max tree

![]()

### 複雜度

- $O$: 樹的高度
- 最糟是只有一條, 像 `linked list`


### max-heap

- max-tree + complete binary tree


### Head data structure

![](https://cdn.programiz.com/sites/tutorial2program/files/delete-1_1.png)
https://www.programiz.com/dsa/heap-data-structure#heapify

- 一個一個放上去, 交換
  - heapdify
- 每一輪都確定



#### Python 實作

```python
# Max-Heap data structure in Python

def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2 
    
    if l < n and arr[i] < arr[l]:
        largest = l
    
    if r < n and arr[largest] < arr[r]:
        largest = r
    
    if largest != i:
        arr[i],arr[largest] = arr[largest],arr[i]
        heapify(arr, n, largest)

def insert(array, newNum):
    size = len(array)
    if size == 0:
        array.append(newNum)
    else:
        array.append(newNum);
        for i in range((size//2)-1, -1, -1):
            heapify(array, size, i)

def deleteNode(array, num):
    size = len(array)
    i = 0
    for i in range(0, size):
        if num == array[i]:
            break
        
    array[i], array[size-1] = array[size-1], array[i]

    array.remove(num)
    
    for i in range((len(array)//2)-1, -1, -1):
        heapify(array, len(array), i)
    
arr = []

insert(arr, 3)
insert(arr, 4)
insert(arr, 9)
insert(arr, 5)
insert(arr, 2)

print ("Max-Heap array: " + str(arr))

deleteNode(arr, 4)
print("After deleting an element: " + str(arr))
```
- [C 實作](https://www.programiz.com/dsa/heap-data-structure#heapify)


## Priority Queue Insertion

![Screen Shot 2021-04-13 at 2 04 54 PM](https://user-images.githubusercontent.com/29009898/114504286-3a5f0a80-9c61-11eb-9711-88df322f72d6.png)


## Binary Max-Heap in Array

![Screen Shot 2021-04-13 at 2 16 05 PM](https://user-images.githubusercontent.com/29009898/114505331-caea1a80-9c62-11eb-8fe1-fe819ed73b11.png)

- Heap
  - 選最大的出來很快
  - 最多就是高度的時間
    - 高度為 $\log(n)$
- 右: 先有 Heap 
  - run `selection sort`
- 怎麼讓資料一開始是 heap？
  - unordered -> heap -> heap sort
    - 創造 heap: $n\log n$
      - 第一個 $n \log n$ 是創造
        - 可以優化成 linear time
      - 第二個是用 insertion 做 sorting
    - 兩件事情都可以在 `array` 做

- Heap 和 sorted array
  - Heap 是 partially sorted
  - 是個 Binary tree, 但可以裝在 sorted array.
  - 為什麼 insert 不在從頭放. 在尾端可以維持 binary tree 的性質. 不需要把別人擠掉


## 應用: Binary Expression Tree

![Screen Shot 2021-04-13 at 2 49 32 PM](https://user-images.githubusercontent.com/29009898/114508880-772e0000-9c67-11eb-8904-5c1eda69cd4d.png)

- Post-order traversal
  - 把 subtree 做完, 再做 root


## Binary Search Tree

![Screen Shot 2021-04-13 at 2 56 10 PM](https://user-images.githubusercontent.com/29009898/114509682-63cf6480-9c68-11eb-864d-dabf3aa2dd76.png)

問題: 如何維持 $\log n$


## Binary Search vs heap

|Binary Search|Heap|
|---|---|
|Root 是中間人|Heap 是老大在上面|

# Sorting

- Space $O(1)$: in-place
- Time:
- Stable 的定義: 保持原來順序的程度


## Heap Sort

- Space: $O(1)$
- Time: $O(n \log(n)$
- **not stable**: 需要把 element 一個一個轉換
- 不常用
  - 不好寫/ 不夠快

## Insertion Sort

- 要找到地方插入
- 無論如何都無法避免 $O(n)$
    ![Screen Shot 2021-04-13 at 3 16 10 PM](https://user-images.githubusercontent.com/29009898/114511996-2f10dc80-9c6b-11eb-9259-cf15760ed8c0.png)

- Performance
  - Space $O(1)$
  - Time $O(n^2)$
  - Stable
  - backwise implementation **adaptive**
    - 可以很快找到
- Insetion sort 比 selection sort 更歡迎

```c
var insertionSort = function(data){
    for(var i = 1; i < data.length; i ++){
        var tmp = data[i];          // tmp = 正處理的值
        var j = i - 1;
        while( j > -1 && tmp < data[j]){
            data[j+1] = data[j];    // 向右移
            j--;
        }
        data[j+1] = tmp;            // 插入新值
    }   
};
```

- [GreekforGeek](https://www.geeksforgeeks.org/insertion-sort/)
    ![](https://media.geeksforgeeks.org/wp-content/uploads/insertionsort.png)

## Shell sort

![image](https://user-images.githubusercontent.com/29009898/114514032-6c766980-9c6d-11eb-83ff-d730da5fe9e6.png)

![Screen Shot 2021-04-13 at 3 26 15 PM](https://user-images.githubusercontent.com/29009898/114513263-98451f80-9c6c-11eb-8de2-328a33a7f2f9.png)

- 終止: `gap` 變成 1
- [Tutorial Shell Short](http://stoimen.com/2012/02/27/computer-algorithms-shell-sort/)
- 要怎麼選 gap?
  - 調參數

## Merge sort


![](http://stoimen.com/wp-content/uploads/2012/03/Divideandconquer.png)

- Time: $O(n\log(n))$
- Space: linear
```
MergeSort(arr,left,right) = 
combine(MergeSort(arr,left, mid), 
        MergeSort(arr,mid+1, right))
```

- Stable: if carefully implemented / **parallelization**
- Popular in **External sort**
  - 把資料分到不同記憶體 
  - **divide-and-conquer**

- [Tutorial](http://stoimen.com/2012/03/05/computer-algorithms-merge-sort/)


## Tree Sort

不用 heap, 變成 binary search tree

## Quick sort



## Reference

1. 各種 sort 圖解. [stoimen's blog](http://stoimen.com/tag/sorting-algorithms/)
2. 動畫

    <iframe width="560" height="315" src="https://www.youtube.com/embed/kPRA0W1kECg" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


---

## 期中考

- 下週
- 會公布座位
- [筆記](../exam.md)
