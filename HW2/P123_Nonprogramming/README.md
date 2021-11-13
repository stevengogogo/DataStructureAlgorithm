 # Nonprogramming part of Homework 2

See 

[![hackmd-github-sync-badge](https://hackmd.io/nLmc8gAiQNCgLfrH7RHBbw/badge)](https://hackmd.io/lQc0xN-7RsOa9Ux7Z9VVjQ)


---


# Reading Notes

# Heap: CH6


### How to acheive linear time complexity?

- 不用比的可以得到: $O(n)$
- 比較: $O(n\log n)$


## Sorting Comlexity 

![](https://i.imgur.com/d2LWkzP.png)


## Heaps

![](https://i.imgur.com/egnpKXr.png)

```
Parent(i)
    return [i/2]
Left(i)
    return 2i
Right(i)
    return 2i+1
```


### Heap operations

- 等比公式: $\frac{a(1-r^n)}{1-r}$



### Level / Height


![](https://i.imgur.com/ivFQRIr.png)


# Quick Sort: Ch7

```python 
PARTITION(A,p,r)
    x = A[r]
    i = p - 1
    for j = p to r-1
        if A[j] < x
            i = i+1
            exchange A[i] with A[j]
    exchange A[i+1] with A[r]
    return i+1
```





# Binary Search Trees: CH12


## Deletion


```python
TREE-MINIMUM(u)
    while u != NIL
        u = u.left
    return u
```

```python
 TRANSPLANT(T, u, v)
     if u.p == NIL 
         T.root = v
     elseif u==u.p.left
         u.p.left = v
     else 
         u.p.right = v
     if v!=NIL
         v.p = u.p
    
```

```python
TREE-DELETE(T,z)
    if z.left == NIL
        TRANSPLANT(T,z,z.right)
    else z.right == NIL
        TRANSPLANT(T,z,z.left)
    else 
        y = TREE-MINIMUM(z.right)
        if y.p != z
            TRANSPLANT(T, y, y.right)
            y.right = z.right
            y.right.p = y
        TRANSPLANT(T, z, y)
        y.left = z.left
        y.left.p = y
```
