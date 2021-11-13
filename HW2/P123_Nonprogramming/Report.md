---
toc:
  depth_from: 1
  depth_to: 3
  ordered: false
---

<a href="https://hackmd.io/lQc0xN-7RsOa9Ux7Z9VVjQ"><img width=150 src=https://i.imgur.com/f4QaiGE.png></a>


<center>

# Homework 2: Non-Programming Part

邱紹庭
`r07945001@ntu.edu.tw`

</center>

**Table of Contents**

[toc]

---


## Problem 1 - Sort (80pt + 20pt)



### 1. (10pts)

Because median is surely not one of the extemes, we can try $n-2$ times eliminiate the impossible i-of-median one by one. The remaining two $P$ will be the extremes. 

```cpp {.line-numbers}
Find-Extremes(P)
    Is = [1,2,3]
   
    for j = 4 to P.len+1
        i = PANCAKE-GOD-ORACLE(P,Is...)
        remove(Is[i])
        if j == P.len+1
            break
        append(Is, j)
    
    return Is
```

Therefore, totoal iteration is $n-1$ times $\in O(n)$

### 2. (20pts)


The main idea is how to convert `PANCAKE-GOD-ORACLE` into a **comparison function**, and use this comparison function to achieve the optimal of comparison sort.


**Making a comparison function**

Since we got the extremes, to say $P_{ext_1}$ and $P_{ext_2}$, we can use one of the $P_{ext}$ as a baseline. We need to prove the following equality

``` wrap=
compare(i,j) = i == PANCAKE-GOD-ORACLE(P[i], P[j], P_ext)
```

where $i,j\notin \{ P_{ext1}, P_{ext2} \}$

- when `P[i] < P[j]` and `P_ext` is maximum
    - `compare(i,j) == 1`
- Otherwise
    - `compare(i,j) == 2`
- because  $P_{ext}$ is always bigger or smaller than both of `P[i]` and `P[j]`
- For `P_ext` is a minimum, vice versa.
- We can not know `compare` is `argmin` or `argmax` function of `P[i]` and `P[j]`. But we can guarantee the monotonicity by using `compare` in *quick sort*.


**Apply to comparison sort**


Since we got the comparison function, we need to first allocate extremes to `P[1]` and `P[end]`. we can apply sorting algorithm, which is optimal in time complexity, to the sequence `P[2]...P[end-1]` (Noted that at this moment, $P[1]=P_{ext1}$, $P[end] = P_{ext2}$, $P[i] = P_k~if~k\in \{1,\cdots,end-1\}$). To acheive $O(n\lg n)$, I chose **quick sort** to the region with index `[2,...,end-1]` and use `compare` function proved above. For clarity, I listed the pseudo code below which is modified from *ITA P.171*:

```cpp {.line-numbers}
Quicksort(A,p,r)
    if compare(p,r)
        q =Partition(A,p,r)
        Quicksort(A,p, q-1)
        Quicksort(A, q+1,r)
end 

Partition(A,p,r)
    x = A[r]
    i = p-1
    for j = p to r-1
        if compare(A[j],x) == 1
            i = i+1
            exchange A[j] with A[i]
    
    exchange A[r] with A[i+1]
    
    return i+1  
end

Sort(P)
    Is = Find-Extremes(P)
    allocate Is to P[1] and P[end]
    Quicksort(P,2,P.end-1)
end
```


**Query Complexity**

- For finding extrema: $O(n)$
- For sorting: It is implemented in quick sort that has the time complexity of $O(n\lg n)$. This complexity can be regarded the calling times of `compare` which uses the `PANCAKE-GOD-ORACLE`. Therefore, the overall query complexity is $n\lg n$.




**Reference**:
1. Algorithm: Sort using Median and Just 1 comparison in $O(n \log n)$. [Stackoverflow][^p-2]
2. Introduction to Algorithm. Page 171.

[^p-2]: [Algorithm Sort with median. StackOverflow](https://stackoverflow.com/questions/19080059/algorithmsort-using-median-and-just-1-comparison-in-on-log-n)






### 3. (10pts)

The insertion takes in two parts: 

1. Comparison to extrema
2. Binary search with extrema as a base number

Let another pancake be `P_new` with testiness `t_new`. And assume list `L` is sorted with extremes locate at `L[1]` and `L[end]`. We want to find a site `i` to insert  `P_new` such that `L` remains sorted (**Fig. 2-1**).

**Comparison to extrema**

``` {.line-numbers}
Pancake-God-Oracle(L[1], L[end], P_new)
```

1. if `output=1`: Insert `P_new` at front
2. else if `output=end`: Insert `P_new` at end
3. Else:
    - Use **binary search** to find location


**Binary Search**

As described in [P1-2](#1-10pts), we can use extrema to build a **comparison function** from `Pancake-God-Oracle`. After checking `P_new` is between `L[1]` and `L[end]`, we can apply the comparison function to **binary search** , which acheive $O(\log n)$ complexity, to find the place to insert `P_new`.


```python {.line-numbers}
Insert(L, P_new)
    i = Pancake-God-Oracle(L[1],L[end],P_new)
    if i==1
        insert P_new at 1 #case 1
    elseif i==end
        insert P_new at end #case 2
    else #case 3
        I = Binary-Search(L[2:end],P_new, func=compare)
        insert P_new at I+1
end

compare(i,j)
    I = Pancake-God-Oracle(i,j, L[1])
    if I==i
        return 1 # i>j
    else 
        return 2 
end
```


The reason to use bianry search:

1. $L$ is **sorted**.
2. When `P_new` is in the **middle** of the extremas, **binary search** is the fastest way to find an item in an **sorted** array.


<center>

<img width=500 src="https://i.imgur.com/hx4MUIS.png">

**Fig. 1-1.** Conditions of inserting a new value. 
</center>


### 4. (5pt)

In **problem 1-3**, the **insertion** keeps the list **sorted** in $O(\log n)$ query complexity. Without locating the boundary pancakes, we can randomly choose two pancakes for starting. In **Fig. 2-2**, any list of two items is sorted. Therefore, we can apply the insertion algorithm proposed in **problem 1-3** (**Fig. 2-1**) to add the rest of pancakes one by one. The following is the proof of the sorting algorithm based on insertion.

**Initiation**

Any list of two items is **sorted**.

**Loop invariance**

Insertion algoritm in **Problem 1-3** keeps the inserted list sorted.


**Termination**

The last element is inserted with the same algorithm, so the list remains sorted.


On the other hand, the query complexity of one insertion is $O(\log n)$, and there are $n-2$ times of calling the insertion algorithm. Therefore, the resulting query complexity is $O(n\log n)$ for $n>2$



<center>
<img width=400 src="https://i.imgur.com/xXAwwL5.png">
</center>


**Fig. 1-2.**   Any list of two items is sorted, and can be applied to the insertion algorithm described in **Fig. 1-1**.




### 5. (20 pt)



In sorting with `PANCAKE-GOD-ORACLE`, we use the medians between three arguments to gain order information about an input sequence $\langle t_1,t_2,\cdots,t_n\rangle$. we perform the tests, $t_i \in (t_j, t_k)$, $t_j\notin (t_i, t_k)$ and $t_k \notin (t_k, t_j)$ when `PANCAKE-GOD-ORACLE(P,i,j,k)=Pi`. we can not inspect the values of the elements or gain order information about the tastes in any other way.


To sort the list of $t_{i}$, the permutation can be represented by the **decision-tree model** (**Fig. 2-3**). We can annotate each leaf by a permutation $\langle \pi(1),\cdots,\pi(n)\rangle$. The execution of the sorting algorithm is equal to tracing a path from root of the decision tree down to a leaf. Each node represents a query, and there are $3$ possible outcomes that results in three sub-trees (**Fig. 2-3**). When coming to a leaf, the input sequence is already *sorted* in an order of $t_{\pi(1)} < \cdots <t_{\pi(n)}$ and $t_{\pi(1)} > \cdots  > t_{\pi(n)}$. Because a correct sorting algorithm must be able to produce each permutation from its input, each of the $\frac{n!}{2}$ permutatoins muse appear as one of the leaves of the decision tree. 

Consider a decision tree of height $h$ with $l$ reachable leaves to sort $n$ elements. Because each of the $\frac{n!}{2}$ permutations of the input appears as some leaf, that is, $\frac{n!}{2}<l$. Since a **tertiary tree** of height $h$ has no more than $3^h$ leaves. Therefore,

$$\frac{n!}{2} \leq l \leq 3^h$$

which, by using logarithms, shows

$$\begin{align} h &\geq \log_{3}(n!) - \log_{3}(2) \\
                 &= \Omega(n\log n)
\end{align}$$

where $\log(n!) = \Omega(n\log n)$ is derived from **Stirling's approximation**[^stir].

By the definition of $\Omega$[^diffO],

$$\lim_{n\to \infty} \frac{n\log n}{f(n)} > 0$$



where $f(n)$ is the query complexity in respect of $n$. Therefore, the equation $\lim_{x\to \infty} \frac{n\log n}{f(n)}=0$ is inachievable, to say, $f(n) \notin o(n\log)$.


<center>
<img  src="https://i.imgur.com/ieFNpO1.jpg">
</center>

**Fig. 1-3.** A **decision tree model** of sorting $t_{i}$ where $i\in \{1,...,4\}$ with calling the function `PANCAKE-GOD-ORACLE(P,i,j,k)`. The syntax $\fbox{t1:t2:t3}$ represents a function call `PANCAKE-GOD-ORACXLE(P,1,2,3)`, and the output is labelled on the links. The sorted list is described in the bracket $\langle t_i ,\cdots,t_j\rangle$.



[^stir]: $n!=\sqrt{2\pi n}(\frac{n}{e})^{n} e^{\alpha_n}$. from CLRS P.58
[^diffO]: [Difference between Big-O and Little-O Notation. StackOverflow](https://stackoverflow.com/questions/1364444/difference-between-big-o-and-little-o-notation)


### 6. (15pt)

**When $n=2$**

When $n=2$, the list is sorted by `swap` operation.

**Suppose first `ELF-SORT` call sorts the sub-list, the following operation remain the list sorted**

We assume the first $\frac{2}{3}n$ can be sorted by the first `ELF-SORT` call (`Sorted-1` in **Fig.1-5**). The second `ELF-SORT` sorted the last $\frac{2}{3}$ portion of $n$, which is notated as `Sorted-2`. Now, both of first $\frac{1}{3}n$ and last $\frac{2}{3}n$ are sorted locally. As a sorted sub-list, $i>j$ for $i\in [l, l+\Delta)\}$ and $j\in [l+\Delta, l+2\Delta)\}$. The third `ELF-SORT` call is to merge the first $\frac{1}{2}$ of `Sorted-2` with `Sorted-1`. Because $\{i|i\in [l+\Delta, r)\}$ is sorted in descendind order, $i>j$ for $i\in [l+\Delta, r-\Delta)\}$ and $j\in [l+2\Delta, r)\}$. Therefore, it is guaranteed that all the elements in `Sorted-3` is larger than those in `Sorted-2`, and both `Sorted-3` and `Sorted-2` are sorted locally, and all of the regions have been sorted twice with different scenerios. Finally, The list is sorted by `ELF-SORT`.



<center>
<img width=400 src="https://i.imgur.com/emhCDjz.jpg">

**Fig. 1-5.** Sorting procedures via `ELF-SORT`. Three lists represent sorted lists after first, second and last `ELF-SORT` call respectively. The unsorted region is labelled with `random`; sorted region `Sorted-i` where `i` represents sorting by $i^{th}$ `ELF-SORT` call, $i\in\{1,2,3\}$.
</center>

### 7. (5pt)

💡**Idea**

>Suppose we have a worst-case running time $T(n)$, estimate the process region of the next reucrsive level.

💬**Description**
When length of list is $n$, $l=1$ and $r=n$. The `ELF-SORT` function will proceed the list with length $n - \frac{1}{3} n$ for $3$ times, which is derived from $[l,r-\Delta]$ where $\Delta$ represent $\frac{1}{3}$ of current $n$. The `swap` operation is independent from $n$, so it can be done in constant time.



$$\begin{aligned} 
T(n) &= 3\underbrace{T(n - \frac{1}{3}n)}_{Next~function~call} + \underbrace{\Theta(1)}_{swap}\\
     &= 3T(\frac{n}{3/2}) + \Theta(1)
\end{aligned}$$





### 8. (15pt)

Let $a$ be the times of recursive calls and $b$ the ratio of current $n$ to the next. we have 

$$T(n) = \underbrace{3}_{a}T(\frac{n}{\underbrace{\frac{3}{2}}_{b}}) + \Theta(1)$$

let $f(n)$ be a function call of `SWAP`.

**Number of `Swap` operation**

The recursive function can be described in a tree structure (**Fig. 1-4**). The `swap` operation occurs on the leaf when $n=2$. The height of the tree is around $\log_b n$. Because all of the nodes have $a$ sub-nodes, that results in $a^{\log_b n}$ leaves, to say, $n^{\log_b a}$. The sum of time complexity of swap operation is $\Theta(n^{\log_b a})$.


**Number of `ELF-SORT` calling**

In **Fig.1-4**, each node represents a function call. The total function call is $g(n) = \sum_{j=0}^{\log_{b}(n) -1} a^j f(\frac{n}{b^j})$


**Time complexity of $T(n)$**

Because $f(n) \in \Theta(1)$, $f(n) \in O(n^{\log_b a-c})$ for some constant $c>0$. This implies that $f(n/b^i) = O(n/b^j)^{\log_b a - c}$ where $\log_b a$ is the height of the recursive tree (**Fig. 1-4**). We get 

$$\begin{aligned}
    g(n) &= \sum_{j=0}^{\log_{b}(n) -1} a^j f(\frac{n}{b^j}) \\
         &= \sum_{j=0}^{\log_{b}(n) -1} a^j (\frac{n}{b^j})^{\log_b a - c} \\
         &= n^{\log_b a-c} \sum_{j=0}^{\log_{b}(n) -1} (\frac{ab^c}{\underbrace{b^{\log_b a}}_{=a}})^j \\
         &= n^{\log_b a-c} \underbrace{\sum_{j=0}^{\log_{b}(n) -1} (b^c)^j}_{\text{Geometric series}} \\
         &= n^{\log_b a-c} (\frac{\overbrace{b^{c \log_b n}}^{n^c} - 1}{b^c - 1}) \\
         &= n^{\log_b a - c} (\frac{n^c - 1}{b^c - 1}) \\
         &\in \Theta(n^{log_{b} a})
\end{aligned}$$

Therefore, the total time complexity is 
$$\begin{aligned}
    T(n) &= \underbrace{\Theta(n^{\log_b a})}_{g} + \underbrace{\Theta(n^{\log_b a})}_{f} \\
         &= \Theta(n^{\log_b a}) = \Theta(n^{\log_{3/2}3}) \\
         &\approx \Theta(n^{2.7}) \in \Theta(n^3) 
\end{aligned}$$




<center>
<img width=400 src="https://i.imgur.com/VlJuon8.png">

**Fig. 1-4.** Time complexity of a recursive function. Time complexity is labelled on nodes and leaves. The figure is modified from [^CLRS:Master].
</center>


[^CLRS:Master]: CLRS, Introduction to Algorithm. 3rd edition. P. 99.


---

## Problem 2 - Tree (65pt)


### 1. (10pt)

**💡Idea**

- Because $k-1 < k$, $t_{k-1}$ is on the left side of $t_k$ 
- On the other hand, $t_{k-1}$ possesses largest index on the left side of $t_{k}$
- Therefore, one can use the policy to find $t_{k-1}$ from $t_k$
    > Turn left, and keep going right until reaching a NIL

**🔧Implementataion**

```cpp {.line-numbers}
function findPrev(t_k)
    
    if(t_k.left == NIL)
        return NIL
    end
    
    t_prev = t_k.left
    
    while(t_prev.right != NIL)
        t_prev = t_prev.right
    end
    
    return  t_prev
end
```


### 2. (15pt)



Because avery sub-tree of $T$ is a binary search tree, and left sub-sub-tree contains data earlier than the sub-tree's root in time. That is, for the set $\{t_i | i\in left~side~of~t_k\}$ fullfills the inequality $t_{i} < t_{k}$.

$$\textbf{t_1 < t_2 < ...} < t_k < \cdots < t_{n-1} < t_n$$

where the set of left nodes is in **bold** font. We can first proof that we can find the previous node of $t_{1}$ that is an empty set (`NIL`). 

For finding $t_{k-1}$, there is no other value between $t_{k-1}$ and $t_{k}$ that is smaller than $t_k$. Therefore, we need to find the biggies value in the set $\{t_i | i\in left~side~of~t_k\}$. By keep reaching the **right leaf**, we can get the biggest value of $\{t_i | i\in left~side~of~t_k\}$. That is $t_{k-1}$.


### 3. (10pt)

<center>
<img width=300 src="https://i.imgur.com/k3pNorJ.jpg">

**Fig. 2-1.** Reconstructed binary tree[^lc:BT].
</center>


[^lc:BT]:[LeetCode: Binary Tree Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/solution/)


### 4. (15pt)


**Definition of root element**

The definition of a root is always the **first** element of the **preorder traversal**. Thus, the determination of a root is unique, which is `inorder[1]`.

**Definition of leaves**

With a given root/subroot, the definition of left and right sets of leaves is unique (**Fig. 2-2**). Recursively, all the set of leaves will be uniquely distributed with complete inorder and preorder traversal.

**Conclusion**

Ther is no two binary trees share with the same `(inorder, preorder)` pair.

<center>
<img width=300 src="https://i.imgur.com/J4m4hog.jpg">

**Fig. 2-2.** Reucrsive algoritm of reconstructing a binary tree with preorder and inorder traversal 
[^Tutorial:BST-Construct].
</center>


### 5. (15pt)

**💡Idea**
- Use recursive method described in **Fig. 2-2**.
- Use a look-table (**Fig. 2-3**) to record the **preorder index** and **inorder index** in respect of a **key** which is the alphabet in **Fig. 2-2**. $O(n)$ time complexity is required for this process including screening these two arrays.
- **A recursive method** to build a binary tree. By intuition, the **worst case** of constructing a binary tree with a **left-connected linked list** that requires $O(n)$ time complexity



<center>
<img width=300 src="https://i.imgur.com/GGDW9tN.jpg">

**Fig. 2-3.** Data structure for storing the indexes of **inorder** and **postorder** array.
</center>

**🔧Implementation**


- Constructing a look-up array
    ```cpp {.line-numbers}
    struct node
        iIN  //index in inorder array
        iPRE //index in preorder array
        left //leaves
        right
    end

    function getPairedArr(inorder, preorder)

        node arr[length(inorder)];

        for i = 1 to length(inorder)
            arr[inorder[i]].iIN = i
        end

        for i = 1 to length(preorder)
            arr[preorder[i]].iPRE = i
        end

        return arr
    end
    ```
    
- Reconstructing a binary tree
    ```cpp {.line-numbers} 
    buildBST(inorder, preorder, iIN)
        map = getPairedArr(inorder, preorder)
        iNA = 1
        root= _buildBst(map, inorder, preorder, &iNA)
        return root
    end


    _buildBST(map, inArr, preArr, *iNA)
        
        //Reach end
        if (length(inArr)==0 || *iNA > length(preArr))
            return NULL
        end
        
        //Asign new root
        root = map[preArr[*iNA]]
        
        Iin = map[preArr[*iNA]].iIN
        
        *iNA++
        
        root.left = _buildBst(map, inArr[1:Iin-1], preArr, iNA)
        root.right = _buildBst(map, inArr[Iin+1:end], preArr, iNA)
        
        
        return root
    end
    ```
Note: 
1. This framework is majorly inspired by [^Tutorial:BST-Construct] and [^leet:BSTrecursive]
2. In Julia: `a[3:end] == []` when `length(a) == 2`[^juliaArr]


 [^leet:BSTrecursive]: [BST recursive](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/discuss/1204516/recursive)


---


## Problem 3 - Heap (55pt)

### 1. (15pts)

**💡Idea**

- **Direction of change**: First of all, if `x.key == v`, there is no need to move the element `x` We need to know the new assigned value `v` is greater or smaller. 
- **Case 1: `x.key` is increased**:   
    - There is only one possibility: going downward to leaf.
- **Case 2: `x.key` is decreased**:
    - Going upward to root.

Both *Case 1* and *Case 2* can be recursively (or loop) implemented. The only difference is the direction of movement.

<center>
<img width=300 src="https://i.imgur.com/gc9HtiV.jpg">

**Fig 3-1.** Moving direction of node `x`.
</center>


**🔧Implementation**

```cpp {.line-numbers}
h.modify(x, v){
    if (x.key==v)
      //Do nothing
    else if(x.key>v)
        h.increaseKey(x,v)
    else
        h.decreaseKey(x,v)
}


h.decreaseKey(x,v){
    assert(x.key > v)
    x.key = v
    while(parent(x) != NULL and parent(x).key > v){
        swap( parent(x), x) 
    }
}


h.increaseKey(x,y){
    assert(x.key < v)
    x.key = v
    
    while( not all of x.leaves[:] is NULL ){
        //Get the node with minimum key
        min_node = argmin(x.leaves[:]) 
        if(min_node.key < x.key){
            swap(min_node, x)
        }
    }
    
}
```

**Description**

- `h.decreaseKey`: For going upward, there is only one neighbor. That is `parent`
- `h.increaseKey`: Going downward is more complicated. We need to choose the direction in the following conditions:
    - **NUll end**: Terminate here
    - **One NULL end**: Choose the node with key
    - **Both leaves have key**: Choose the `minimum` to swap

**Time Complexity**

There are no more than $\log |h|$ (height of tree) needed for a swap operation because the **target node moves to a new level of tree and never turns back each time**. The times of `while-loop` depends on **the height of tree**.

**Notes**

1. I use `x.leaves[:]` is for generosity, that means there can be leaves more than two like **d-ary heap**
2. The `swap` function switches two variables. 


### 2. (10pt)

**Definition**

`u`: undefine variable

#### (a)


|N\M|0|1|2|3|
|---|---|---|---|---|
|0|u|u|u|u|
|1|u|u|u|u|
|2|u|u|u|1|
|3|4|u|u|2|

```!
D.add(2, 3, 1); D.add(3, 3, 2); D.add(3, 0, 4); ShowState();
```


##### (b)

|N\M|0|1|2|3|
|---|---|---|---|---|
|0|u|u|u|u|
|1|u|u|u|u|
|2|u|u|u|1|
|3|4|u|u|u|

```!
 D.extractMinRow(3) ; ShowState();
```


##### `(c)`

|N\M|0|1|2|3|
|---|---|---|---|---|
|0|u|u|u|u|
|1|u|u|u|3|
|2|u|u|u|1|
|3|4|u|u|u|

```c!
D.add(1, 3, 3); ShowState();
```


##### (d)

|N\M|0|1|2|3|
|---|---|---|---|---|
|0|u|u|u|u|
|1|u|u|u|3|
|2|u|u|u|u|
|3|4|u|u|u|

```c!
D.delete(2, 3); ShowState();
```

##### (e)

|N\M|0|1|2|3|
|---|---|---|---|---|
|0|u|u|u|u|
|1|u|u|u|u|
|2|u|u|u|u|
|3|4|u|u|u|

```c!
D.extractMinCol(3 ); ShowState();
```

### 3.(10pt)

**💡Idea**

- **$\log(NM)$ is the sum of two heaps' operation**
    - Since all of operations mentioned `O(log(nm))` time compleixty, it is likey the result of **two-heap-operation**, which causes `O(log(m) + log(n))` operation of a paired heap
- How to know the **availability** of an item?
    - For each element $A_{i,j}$, we need to labelled the availability by using `struct` or build another one-to-one map to store the data of availability. The status of an item can be:
        1. Undefined
        2. Available
        3. Extracted


- Each column/row requires a heap to keep the track on the minimum. There will be $M+N$ heaps. 
- Each node should keep track on its location `i` and `j`. To 


<center>
<img width=300 src="https://i.imgur.com/kgjrWPg.jpg">

**Fig 3-2.** 2D array with two array of heaps.
</center>


**🔧Implementation: Data Structure**

1. Node $A_{i,j}$ 
    ```cpp {.line-numbers}
    struct node{
        key
        i
        j
        iHr // location at row heap
        iHc //location at col heap
        avail//availability
    }
    ```
2. Heap
    ```cpp {.line-numbers}
    struct heap{
        node* array[N] //M
        len //[0,N]/[0.M]
    }
    ```
3. Data Structure `D`
    ```cpp {.line-numbers}
    struct D{
        heap Hc[M]
        heap Hr[N]
        node A[N,M]
    }
    ```


**🔧Implementation: Operations**



1. `D.add(i, j, v)`
    ```cpp {.line-numbers}
    function add(d::D, i,j,v)
        //Register A[i,j]
        d.A[i,j].avail = true
        d.A[i,j].i = i
        d.A[i,j].j = j
        d.A[i,j].key = v

        insertHeap(d.Hr[i], &d.A[i,j])
        insertHeap(d.Hc[j], &d.A[i,j]) 
    end
    ```
    
    We have to extract all unavailable values until find the reachable minimum.

2. `D.extractMinRow(i)`

    ```cpp {.line-numbers}
    function extractMinRow(d::D, r)

        d.Hr[0].avail = false
        extractMinHeap(d.Hr[r])
        deleteHeap(d.Hc, d.Hr[0].iHc) //heap deletion

    end
    ```
    Similar to `D.extractMinCol`


3. `D.extractMinCol(i)`

    ```cpp {.line-numbers}
    function extractMinRow(d::D, c)

        d.Hc[0].avail = false
        extractMinHeap(d.Hc[c])
        deleteHeap(d.Hr, d.Hc[0].iHr) //heap deletion

    end
    ```

4. `D.delete(i, j)`

    ```cpp {.line-numbers}
    function delete(d::D, i, j)
       d.A[i,j].avail = false
       deleteHeap(d.Hr, d.A[i,j].iHr)
       deleteHeap(d.Hc, d.A[i,j].iHc)
    end
    ```



### 4. (20pt)

In **Fig. 3-2**, $M+N$ heaps have been estbalished for tracking the minimum value of columns and rows. 

#### Add
We need two heap insertions to track the minimum values of column `j` and row `i`. Therefore, the time complexity is `O(log M + log N) = O(log MN)`


#### Extract

The extraction on either `col` or `row` requires a following heap deletion. Both of them requires `O(log(h))`. Therefore, the sum of complexity is `O(log N + log M)`


#### Deletion

We need to delete the same item in two heaps. Use the `iHc` and `iHr` to keep track on the location. The deletion can be done by simply set `d.Hrp[iHc] = -Inf` with heapify and extraction. All of them requires logarithmic time complexity on each side. In summary, the total time complexity is `O(log N + log M)`








[^Tutorial:BST-Construct]: [ Construction of unique Binary tree. Book chapter](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwiIzf_Av8bwAhUvy4sBHem3BCgQFjABegQIBBAD&url=https%3A%2F%2Fs3-eu-west-1.amazonaws.com%2Fpfigshare-u-files%2F1800958%2FConstructionofuniqueBinarytree.pdf&usg=AOvVaw23KzE0wgqxMB83ms4ZTp6Y)


 [^juliaArr]: ```julia
    julia> a = [1,2,3,4]
    4-element Array{Int64,1}:
    1
    2
    3
    4

    julia> a[5:end]
    Int64[]
    ```