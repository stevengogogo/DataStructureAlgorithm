---
toc:
  depth_from: 2
  depth_to: 3
  ordered: false
---

[![hackmd-github-sync-badge](https://hackmd.io/JZUhv-byTRqV46cumxZ9Xw/badge)](https://hackmd.io/JZUhv-byTRqV46cumxZ9Xw)

<center>

# Homework 3: Nonprogramming part

**邱紹庭**

`r07945001@ntu.edu.tw`

</center>

**Table of contents**

[toc]

---

## Problem 1 - Hash (60pt)


### 1. (10pt) 

The probability of no collision ($X'$)[^UniHash]:

$$\begin{align}
P(X') &= \frac{n^2}{n^2} \frac{n^2-1}{n^2} \cdots \frac{n^2-n+1}{n^2} \\
      &= \prod_{i=1}^{n} \frac{n^2 - i + 1}{n^2}
\end{align}$$

On the other hand, the probability of any collision ($X$):

$$\begin{align}
P(X) &= 1 - P(X')\\
     &= 1 - \prod_{i=1}^{n} \frac{n^2 - i + 1}{n^2}_{\#}
\end{align}$$


[^UniHash]: [If we store n keys in a hash table of size m=n^2 , then what is the probability of any collision ?](https://gateoverflow.in/41109/store-keys-hash-table-size-then-what-probability-collision)

[^AC-P1-1]: Thanks to 張杰輝's inspiration.

### 2. (10pt) 

**💡 Idea**

Suppose we add unique keys one by one. Inserting first unique key at start require extected $1$ time of insertion. For second unique key, since there is already one position occupied, the acquisition of second key requires $\frac{|P|}{|P|-1}$ expected times of insertion[^AC-P1-1].


**🔧 Formulation**

For inserting $a+1^{th}$ unique keys when there is already $a$ slots occupied. Let $p$ be the probability of success insertion of unique key with single trial. The probability of success insertion after $n$ trials is

$$Pr_{a+1}(p_{a+1},n) = (1-p_{a+1})^{n-1}p_{a+1}$$

where $p_{a+1} = \frac{|P|-a}{|P|}$ and $n\in \{1,...,\infty\}$. The probability  $Pr_{a+1}(p_{a+1},n) \in$ **Geometric distribution**.

Since $Pr_a$ belongs to geometric distribution, the expected value is[^geom]

$$E[\text{Times to inserting $a+1^{th}$ key} | a \text{ slots occupied in } P] = \frac{1}{Pr_{a+1}} =\frac{|P|}{|P|-a}$$

For inserting $k$ keys,

$$E[\text{# of inserting $k$ keys}] = \sum_{i=0}^{\frac{\lfloor P \rfloor}{4} -1}\frac{|P|}{|P|-i}_{\#}$$


[^geom]: https://en.wikipedia.org/wiki/Geometric_distribution

### 3. (20pt) 
- $h(k,i) = (h_1(k)+i)~mod~m$
- $h_{1}(k) = k~mod~m$
- $m=11$

**Open addressing with linear probing**

|k|h1(k)|0|1|2|3|4|5|6|7|8|9|10|
|---|---|---|---|---|---|---|---|---|---|---|---|---|
|18|7||||||||18|||
|34|1||34||||||18|||
|9|9||34||||||18||9|
|37|4||34|||37|||18||9|
|40|7||34|||37|||18|40|9|
|32|9||34|||37|||18|40|9|32|
|89|1||34|89||37|||18|40|9|32|


**Open addressing with double hashing**

- $h(k,i) = (h_1(k) + ih_2(k))~mod~m$
- Primary Hash function: $h_{1}(k) = k~mod~m$
- Secondary hash function: $h_{2}(k) = 1+ (k~mod~(m-1))$
- $m=11$

|k|h1(k)|h2(k)|0|1|2|3|4|5|6|7|8|9|10|
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|18|7|9||||||||18|||
|34|1|5||34||||||18|||
|9|9|10||34||||||18||9|
|37|4|8||34|||37|||18||9|
|40|7|1||34|||37|||18|40|9|
|32|9|3||34|||37|||18|40|9|32|
|89|1|10|89|34|||37|||18|40|9|32|


- 40
    - H1:40%11 = 7 
    - H2: 1+(40%10) = 1 
- 32
    - H1: 32%11 = 10
- 89
    - H1: 89%11=1
    - H2: 1+ 89%10 = 10


### 4. (20pt) 


**Table T1**[^AC-P1-1]

- $h_1(k)=k~mod~7$

|k|h1(k)|0|1|2|3|4|5|6|
|---|---|---|---|---|---|---|---|---|
|6|6|||||||6|
|31|3||||31|||6|
|2|2|||2|31|||6|
|41|6|||2|31|||41|
|30|2|||30|31|||6|
|45|3|||30|45|||6|
|44|2|||44|31|||6|

**Table T2**

- $h_2(k) = \lfloor \frac{k}{7} \rfloor~mod~7$

|k|h2(k)|0|1|2|3|4|5|6|
|---|---|---|---|---|---|---|---|---|
|6|0|||||||||
|31|4||||||||
|2|0|||||||||
|41|5|6|||||||
|30|4|2|||||41||
|45|6|2||||31|41||
|44|6|2||||30|41|45|

---

## Problem 2 - String matching (60pt)


### 1. (10pt)

**💡 Idea**
1. Use **Robin-Karp algorithm** to hash strings.
2. **Preprocessing**: Create an array of hashes. Let the `array[i]` stores the hash of `S[i..N]`. This requires 

|Index|1|2|3|4|
|---|---|---|---|---|
|Sting|S1|S2|S3|S4|
|Hash|H1:1|H1:2|H1:3|H1:4|

where `Hi:j` represents the hash of the region `H(S[i..j])`

4. **Query**: Use **Substraction** technique to get the hash value in the region of `S[i..j]` with $O(1)$ time complexity (**Fig. 2-1**).

<center>

<img height=200 src="https://i.imgur.com/DXyMche.jpg">

**Fig 2-1.** Generate `hash(S[2..4])` from `HL` and `HR`.

</center>

**🔧 Implementation**

**Preprocessing**

```cpp=
function Preprocessing(Str, d, q)
    Initialize hash_list[1,...,length(Str)]
    
    p = 0
    for i = 1 to length(Str)
        p = (dp + Str[i]) mod q
        hash_list[i] = p
    end
    
    return hash_list
end
```
- `Str`: Text
- `d`: The radix 
- `q`: modulo

**Hash Generation**

```cpp=
function get_hash(hash_list, d, q, l, r)
    l_hash = hash_list[l]
    r_hash = hash_list[r]
    
    i_hash = (r_hash - l_hash) / d^(r-l)
    i_hash = i_hash mod q
    return i_hash
end
```

**Matching**

```cpp=
function matching(Str, hash_list, l1, l2, n)
    h1 = get_hash(hash_list, l1, l1+n-1)
    h2 = get_hash(hash_list, l2, l2+n-1)
    
   if h1==h2
       if(Str[l1...l1+n-1] == Str[l2...l2+n-1])
           return true
   return false
end
```


**🔢 Analysis**

- Preprocessing:
    - Time: $O(N)$
    - Space: $O(N)$ 
    - where $n$ is the length of the text
- Hash generation
    - Time: $O(1\cdot Q)$
        - Single query requires constant time.
    - Space: $O(1)$
- Matching
    - Similar to Rabin-Karp Matching
    - Time: $O(Q)$ (amortized). 
        - In this case, two string poccess equal lengths. The original time complexity $O((m-n+1)n)$ decays to $O(n)$ where $n$ is the length of the sub-string.
    - Space: $O(1)$. Reuse the text stored in `preprocessing`.


- **Total**: $O(N+Q)\approx O(N)$ for $Q\approx N$.

### 2. (10pt)

- `S[1..N]` = `bcdabcde`

|$i$|$x(i) = \max(p)$|array $X$|
|---|---|---|
|1|8|`bcdabcde`|
|2|0|` `|
|3|0|` `|
|4|0|` `|
|5|3|`bcd`|
|6|0|` `|
|7|0|` `|
|8|0|` `|



### 3. (20pt) 

**💡 Idea**
- Let $x(i) = y > 0$. For $\{j | j\in [i+1..i+y-1]\}$, $x(j)=x(j-i+1)$. (**Fig 2-1.**, underlined). Therefore, we can get $x(j)$ in constant time if it is covered in the identical region.
- If $k\notin [i+1..i+j-1]$, use one-by-one comparison to iterate next site with $y>0$ and calculate the $P$s on the left side of the boundary (**Fig2-1**, yellow vertical line). 
- The main reason this algorithm can keep in $O(n)$ is because the boundary **Fig 2-1.** only goes to right, and the region between `i` and `i+p-1` can be retrieved in **constant time**.

<img height=200 src="https://i.imgur.com/fKUbPrU.png">

**Fig 2-1.** Construction of Ps. The first row represents the index of site and the boundary described in *idea*. Second row is the text. The third row is the $x(i)$ with the repetitive region underlined in black[^94].


<img height=100 src="https://i.imgur.com/iKzuyPR.jpg">
<img height=100 src="https://i.imgur.com/OypDeRN.jpg">

**Fig 2-2.** **Case I**: Overlapped pattern; **Case II**: Non-overlapped pattern.

[^94]: This problem is discussed with the user `54` on DSA Discord.

**🔧 Implementation**

```cpp=
function get_xs(S)
    create list xs[1..length(S)]
    
    xs[1] = length(s)
    
    boundary = 0
    boundary_origin = 0
    
    for i = 2 to length(s)
        
        // Case 0
        if(S[1] != S[i])
            xs[i] = 0
        end
        
        // Case 1 & 2: Within Boundary
        else if(i < boundary_origin)
            // Case 1
            if(i<xs[boundary])
                p = xs[boundary] - (i-boundary_origin)
            end
            
            // Case 2
            else
                p=xs[i-boundary+1]
            end
            
            while(S[i+p] == S[1+p])                       
                p+=1
                boundary_origin = i
                boundary = i+p-1
            end
                
            xs[i] = p
        end
      
        
        // Case 3: On the right of the boundary
        else
            p = 0
            while(xs[i+p]==xs[1+p])
                p+=1
                boundary_origin = i
                boundary = i+p-1
            end     
            xs[i] = p
        end
    end
    
    return [S[1..i] for i in xs[i]] //Xs
end
```

- Time analysis
    - The boundary only goes to the end of string in one direction
    - Hence, the time complexity is $O(len(S))$
- Space: $O(len(S))$.
- This function returns a list of **X**s, which is same as 
    > Design an algorithm that calculate the content of array X

### 4. (20pt)

**💡 Idea**
- Merge pattern $p$ with the string $t$.
    - This creates a new string, $pt$, with length equal to $len(p)+len(t)$
- Use the algorithm proposed in **P3-3**, calculate the $x(i)$
- Find all of $i$ such that $\{i | i>len(p)~and~ x(i)\geq len(p)\}$


**🔧 Implementation**

```cpp=
Find-occurrence(p, t)
    m = p + t
    xs = get_xs(m)
    occurrence = 0
    for i = length(p)+1 to length(m)
        if(xs[i] >= length(p))
            occurrence += 1
        end
    end
    
    return occurrence
end
```


**🔢 Analysis**

- Time: 
    - Preprocessing: $O(len(p)+len(t))$
    - Counting: $O(len(t))$
    - Overall: $O(len(p) + 2\cdot len(t))$
- Space: $O(len(p) + len(t))$


[^RKMatch]: CLRS. PP.993

---

## Problem 3 - Having fun with Disjoint Sets (80pt)


### 1. (15pt) 

**💡 Idea**
- Initiation [^findbipart][^stackbipart]
    - Set singular sets for all verteces
- Add
    - If same set, return `false`
    - If different set, `union`
  


**Initiation**

```cpp=
INIT(N)
    Create MAP[0,..,N-1] with NIL-filled
    for i = 0 to N-1
        MAKE-SET(i)
    end
    
    isBiparatite = True
end
```
- `isBiparatite` can be seen and modified globally.
- Vector `MAP`: contains a nighbor of each verteces.
    - If `MAP[1] == 2`, it means vertex `1` is connected to vertex `2`





  

<img height=200 src="https://i.imgur.com/kxkp8uz.jpg">

**Fig 3.1** The data structure of `MAP`. In this case `Add(1)`. Th array `MAP` is a list of pointers which store address of disjoint sets. Calling `MAP[1]` returns the disjoint set of `2-1` as illustrated.

**Adding edge**

```cpp=
ADD-EDGE(x,y)
    // Check bipartite
    if FIND-SET(x) == FIND-SET(y)
        isBiparatite = False
    end
    
    if MAP[x] == NIL
        MAP[x] = y
    else
        UNION(MAP[x], y)
    end
    
    if MAP[y] == NIL
        MAP[y] = x
    else
        UNION(MAP[y], x)
    end
end
```

- `isBiparatite` is generated by `INIT`.


**Check bipartite**

```cpp=
IS-BIPARTITE()
    return isBiparatite
end
```

**🔢 Analysis**

- **Initiation**: Operates in linear time complexity for `Make-Set` is $O(1)$ and iterates $N$ times. Therefore, the total time complexity is $O(N)$.
- **Add Edge**: the union by size technique can confirm the smaller set enlarges at least twice of its size, which yields $O(\log N)$ time complexity for `Union` operation. Since the maximum calling of `ADD-EDGE` is $M$, the worst case of time complexity is: $O(M \log N)$ .
- **Check bipartite**: The time complexity of `IS-BIPARTITE` is $O(1)$.
- **Summary**: The total operation requires $O(N) + O(M\log N)$ in time complexity.


[^findbipart]: [How to Find If a Graph Is Bipartite?](https://www.baeldung.com/cs/graphs-bipartite)
[^stackbipart]: https://stackoverflow.com/questions/53246453/detect-if-a-graph-is-bipartite-using-union-find-aka-disjoint-sets


### 2. (15pt) 

**💡 Idea**
1. Create $3N$ nodes. $N$ nodes labelled with `scissor`, $N$ for `stone` and $N$ for `paper`
2. For `Win` operation, links all of 3 victory conditions. That is `scissor -> paper` / `paper->stone` / `stone->scissor`, and link these conditions into three disjoint sets.
3. For `tie` operation. For example: `Tie(i,j)`: Link $Node_{i}^{stone}$ to  $Node_{j}^{stone}$ , and the other two pairs (**Fig 3-1.**).
4. Contradiction: if more than 1 $Node_{i}^{\#}$ belongs to the same set, it means there is one person revealing two results at the same time which is a contradiction.



<img height=100 src="https://i.imgur.com/WQe2ymI.png">


**Fig 3-1. Sets of all possibility for `WIN(A,B); WIN(B,C)`.**

**🔧Implementation**

**Initiation**

```cpp=
function INIT(N)
    Create list of vertexes: 
        Scissor[1..N]
        Stone[1..N]
        Paper[1..N]
        
    for i = 1 to N
        MAKE-SET(Scissor[i])
        MAKE-SET(Stone[i])
        MAKE-SET(Paper[i])
    end
    
    contracdict = true
end
```

- The list contains **Vertex** object.
- These function creates $3N$ verteces stored in three lists.
- Noted that `Scissor[1]` means `person 1` with `scissor` output, and `Scissor[1]` and `Paper[1]` are two independent objects.

**Win**

```cpp=
function WIN(a,b)
    UNION(Scissor[a], Paper[b]) 
    UNION(Stone[a], Scissor[b])
    UNION(Paper[a], Stone[b])
    
    contradict = IS-CONTRADICT-NODE(a) 
    contradict = IS-CONTRADICT-NODE(b)
end
```

**Tie**

```cpp=
function TIE(a,b)
    UNION(Scissor[a], Scissor[b])
    UNION(Stone[a], Stone[b])
    UNION(Paper[a], Paper[b])
    
    contradict = IS-CONTRADICT-NODE(a)
    contradict = IS-CONTRADICT-NODE(b)
end
```

**Contradiction**

```cpp=
function IS-CONTRADICT-NODE(i)
    if(FIND-SET(Scissor[i]) == FIND-SET(Stone[i]))
        return true
    end
        
    else if(FIND-SET(Scissor[i]) == FIND-SET(Paper[i]))
        return true
    end
        
    else if(FIND-SET(Paper[i]) == FIND-SET(Stone[i]))
        return true
    end
    
    else
        return false
    end
end

function IS-CONTRADICT()
    return contradict
end
```

- The `IS-CONTRADICT`  uses the global variable `contradict` as return.
- The `contradict` valuable is updated within every operation `WIN` and `TIE` with $O(\log N)$ time comlexity.


**🔢 Analysis**
- Time:
    - `Init`: $O(N)$
    - `WIN`: $O(\log N)$
    - `TIE`: $O(\log N)$
    - `IS-CONTRADICT`: $O(\log N)$ in each operation: The contradict testing is run every `WIN` and `TIE` operations. Each check requires $O(\log N)$ time complexity. This is contributed by `FIND-SET` operation. 
    - Total: $O(N + M\log N)$. Time complexity results from `union by size` and `FIND-SET`, which are used for `WIN`/`TIE`/`IS-CONTRADICT` function. Noted that these three function are called $M$ times.
- Space: 
    - Individual outputs are set as independent nodes. The initiation triples the size of $N$ verteces. The total space complexity is $O(N)$.


### 3. (15pt) 

**💡 Idea**
- **Amortized analysis**: Use amotized analysis to derive the time complexity of **path compression** without **union by size**.



**🔢 Amortized analysis**

**Initiation**

This process is trivially $O(N)$ in time complexity. Because the stack operations are performed $N$ times both with `memo` and `stk` (**line `58-68`**).

**Add Edge**

- This implementation only apply **path compression**. As we can see in **line `85-92`**, the `djs_assign` reassign the subtree to the representative of the disjoint set.
- On the other hand, the `djs_union`(**line `94-99`**), the union process is deterministically performed, regardless of the sizes of two disjoint sets.

**Contradiction**
- According to [^disjoint-amortized][^disjoint-ppt], with the linked list and path compression, the `FIND-SET` requires recursive in times of tree height. Because this operation doesn't provide **union by size** technique. In the worst cast, the tree height can be flattened to a linked list with length $O(N)$ (**Fig. 3-2**).

- If the process is undid. The structure will return to **Fig 3-2 (left)** with $O(N)$ operations.

- The **contradict condition** is
    - Call `undo` instantly before call `union`.
    - Like `Union ->  Union undo Union`. This can inevitably reconstruct the tree with undoing (**Fig 3-2.** from `right->left->right`).

 
<img height=200 src="https://i.imgur.com/DsSzsEu.png">

**Fig 3-2.** Path compression[^disjoint-ppt]. The structure can be converted to the right by `FIND-SET`. Conversely, `Undo`.


**📒 Conclusion**

- I **disprove** the stated time complexity. 
- The worst case can be $O(N+MN)$ with the contradict condition described above.






[^cpuinfo]: CPU Info: `Model name: Intel(R) Xeon(R) CPU @ 2.20GHz; CPU MHz: 2199.998`

[^disjoint-amortized]: Disjoint set. PPT. Page 18. Prof. Hsin-Mu Tsai.

[^disjoint-ppt]: Page 30. https://www.cs.princeton.edu/courses/archive/spring13/cos423/lectures/UnionFind.pdf. `Starting from an empty data 
structure, path compression (with naive linking) performs any intermixed 
sequence of m ≥ n find and n – 1 union operations in O(m log n) time`

### 4. (15pt) 


As mentioned in  [^disjoint-amortized], the linked list with union-by-size can achieve $O(N+M\log N)$ time complexity.



**Initiation**

The first $O(N)$ is caused by the initiation, that uses a `for-loop` to setup all sets.

**Find set**

With the aid of **union by size**, the data structure remains a tree (**Fig 3-3**). This makes `Find-set` operation works in $O(\log N)$[^findset_union].


**Add Edge**

As mentioned in [^findset_union], the union by size technique assures the smaller set to increase at least twice of its original size, maintaining the height of the tree approximately $O(\log N)$. The union operation is accompanied with the `Find-set` which requires $O(\log N)$ time complexity. However, the link process (**Fig 3-3.**) only requires $O(1)$[^disjoint-ppt][^disjoint-amortized].


**Undo**

The `undo` process doesn't destroy the tree structure. For each undo, the unlink process is taken place, and this operation maintain the tree height. Thus, after calling `undo`, `Find-set` and `Add-edge` remains $O(\log N)$ time complexity. The `undo` operation requires the time complexity no more than $O(\log N)$


**Conclusion**

- **The statement is valid**. The time complexity of this modification is $O(N+M\log N)$.

<img height=200 src="https://i.imgur.com/onvK94p.png">

**Fig 3-3.** Union by rank [^disjoint-ppt]. The dash line represents the link created by `Add-edge`.


[^findset_union]: https://www.chegg.com/homework-help/questions-and-answers/data-structure-algorithms-need-understand-time-complexity-analysis-exam-disjoint-sets-link-q33572109. ![](https://i.imgur.com/BsghCel.png)



### 5. (20pt) 


**💡 Idea**

1. Use path compression technique and union by rank to achieve $O(\alpha(1))$ as mentioned in [^disjoint-amortized].
2. **Isolation**: 
    - With path compression technique, we can call `FIND-SET` operation ([**Fig 3-3.**](#3-15pt)) with $\log h$ time complexity to flattten the tree, where $h$ is the height of the tree.
    - Connect $k$'s descendants to its parent with $O(1)$ time complexity.
    
    
<img height=200 src="https://i.imgur.com/DsSzsEu.png">

**Fig 3-3.** Path compression[^disjoint-ppt]. 


**🔧 Implementation**

**Node structure**

```cpp=
struct node
    parent::node
    leaf::node
end
```

**Isolation**

```cpp=
function ISOLATE(k::node)
    p = FIND-SET(k)
    k.parent = NULL
    k.leaf.parent = p
end
```
- Noted that the `FIND-SET` operation is implemented with **path compression** technique, which can flatten the disjoint set, and make it easy to re-connect `k`'s offspring to its parent.


**🔢 Analysis**

- The operation is under the scale of $O(M\log N)$ in time complexity. Because the `isloate` operation is under the time complexity of $O(\log h)$ where $h$ is the height of the disjoint tree.


## References