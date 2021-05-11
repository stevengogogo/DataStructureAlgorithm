# Disjoint Set

<iframe width="560" height="315" src="https://www.youtube.com/embed/eYUSRIPm3Ms" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

---

## 為什麼 `FIND-SET` 會是 constant time? 如果是 linked-list 需要先找到 data, 那不是 `O(n)` 的時間嗎?

<img width="200" alt="Screen Shot 2021-05-11 at 1 44 40 PM" src="https://user-images.githubusercontent.com/29009898/117764426-0a565780-b25f-11eb-9a6a-fa8245fe02a2.png">

- 要記起來 data 儲存的位置
- `FindSet` 直接使用

## 如果直接把 set 的 head 直接等於第一個 set 的 head 的 pointer 不是只要 `O(1)` 時間嗎?

<img width="989" src="https://user-images.githubusercontent.com/29009898/117765475-9157ff80-b260-11eb-8462-49e7ce982130.png">


## Amortized analysis

- [Tutorial](https://mropengate.blogspot.com/2015/06/algorithm-amortized-analysis.html)
- CLRS CH17.

## Set Theory


<img width="838" alt="Screen Shot 2021-05-11 at 3 35 36 PM" src="https://user-images.githubusercontent.com/29009898/117776821-8906c100-b26e-11eb-91f2-7c3e504a7694.png">

- [Formal explain](https://math.libretexts.org/Bookshelves/Mathematical_Logic_and_Proof/Book%3A_Mathematical_Reasoning__Writing_and_Proof_(Sundstrom)/7%3A_Equivalence_Relations/7.2%3A_Equivalence_Relations)

- [Slides](https://web.stanford.edu/class/archive/cs/cs103/cs103.1132/lectures/05/Small05.pdf)

## Discussion

### Painless Bug Tracking

> At any given time, I can only remember two bugs.
> 
> Keeping a database of bugs is one of the hallmarks of a good software team.
> 
> Without an organized database listing all known bugs in the code.

### Every good bug report

1. Steps to reproduce
2. What you expected to see
3. What you saw instead

### Tips for debuggin

1. Reduce the repro steps to the minimal steps
2. 

### Dijksra Algorithm
 
Measuring the shortest path in graph

- [javapoint](https://www.javatpoint.com/dijkstras-algorithm)