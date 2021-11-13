# Priority Tree

> From DSA 2021: Problem 5 - Alice's Bookshelf

## Problem Statement

- **A Bookshelf**

    |Position|1|2|3|4|5|...|n|
    |---|---|---|---|---|---|---|---|
    |Priority|-1|0|0|3|4|...|1|


- **A book**
    ```julia
    struct Book{
        position
        priority
    }
    ```

- **Priority** 
  - **not unique**
  - When queuing books with **same priority**
    **extract the one with least position**.
- **Position**
  - Start from `1`
  - Insert `0` means insertion at start.

## Operation

- `1 p k`: **insert** a `book(priority=p,position=k)`. 
  - When `k=0`, insert at start
- `2 k`: **Delete** the `k-th` book.
- `3 l r p`: **Increase priorities** by `p` between `[l,r]`
- `4 l r`: Query the **largest priority**  between `[l,r]`
- `5 l r`: Reverse the positions between `[l,r]`
- `6`: Remove the largest priority


## Strategy


### Insert

**Description**


For insert node at `book(pos=18, prio=20)`
<center>
<img height=250 src="https://img-blog.csdn.net/20151103185313376?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast">
</center>



**Algorithm**

1. Search and Create `pos=18` (BST serach). [`n_new`]
2. Correct Heap
   - **Case 1**: `n_new.key` < `n_new.parent.key`
     - Do nothing
   - **Case 2**: `n_new.key` > `n_new.parent.key` and `n_new` is on the right
     - `LeftRotate(n_new.parent)` to pick `n_new` up
     - Repeat 2.
   - **Case 3**: invert left right in **Case 3**  



**Complexity**



### Delete

**Description**
**Algorithm**
**Complexity**



### Increase Priority

**Description**


**Algorithm**


**Complexity**



### Query largest

**Description**
- Query the largest priority between the positions `l` and `r`.
    ```c
    Query(l, r)
    ```

**Algorithm**

1. Search first element in [l,r]
   ```c
   node search_node_in_region(root, l, r)
   ```



**Complexity**

### Reverse order
**Description**
**Algorithm**
**Complexity**



## Helper functions

#### Get first position
- Leftist position under root `x`
    ```cpp
    node FirstPosition(x)
        while x.left != NULL
            x = x.left
        return x
    end
    ```

#### Search Position

- Record **Number of nodes under node x**

#### Search Highest Priority

- Search node with key=`x` within `[lp, hp]` with **highest level**. Return `NULL` if not item found.
    ```cpp
    node TreeSearchDomain(x, lp, hp)
        if x == NULL
            return x
        else if isBelong(x,lp,hp)
            return x
        else if x > max(lp,hp)
            return TreeSearchDomain(x.right, lp,hp)
        else 
            return TreeSearchDomain(x.left, lp,hp)
    end
    ```
- Usage
  - Query the largest books between position `l` and `r`
- Time
  - `O(log n)`
- Ref: Binary search in BST




---

## Note

### Invet Binary Tree

```python
class Solution:
    def invertTree(self, root):
        if root is None:
            return None
        root.left, root.right = \
            self.invertTree(root.right), self.invertTree(root.left)
        return root
```

1. [LeetCode](https://leetcode.com/problems/invert-binary-tree/solution/)

### Treap Data Structure

> A treap is a binary tree that maintains simultaneously the property of binary search tree (BST) and heap.


#### Split
![Screen Shot 2021-05-30 at 2.56.52 PM](https://i.imgur.com/FH6UJw2.png)
*Source: [A&DS S02E06. Treaps, implicit keys](https://youtu.be/svAHk-FAQgM?t=2068)*

```cpp
split(node, x)
    if node == NULL
        return {null, null}
    if node.x < x
        p = split(node.right, x)
        node.right = p.left
        return {node, p.second}
    else
        p = split(node.left, x)
        node.left = p.second
        return {p.left, node}
```

#### Merge
![Screen Shot 2021-05-30 at 2.57.09 PM](https://i.imgur.com/JPYJraG.png)
*Source: [A&DS S02E06. Treaps, implicit keys](https://youtu.be/svAHk-FAQgM?t=2068)*

**Ref:** 
1. [medium](https://medium.com/carpanese/a-visual-introduction-to-treap-data-structure-part-1-6196d6cc12ee)
2. [Treap. Wiki](https://en.wikipedia.org/wiki/Treap)
3. [Treap. CP-Aglorithms](https://cp-algorithms.com/data_structures/treap.html)
4. [Treap. ITREAD](https://www.itread01.com/content/1545721233.html)


## Sample Code 

```cpp {.line-numbers} 
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

random_device random_seed;
mt19937 mt(random_seed());

class implicit_treap
{	
	public:
		struct node
		{
			int sz, priority, lazy, rev, sum;
			int val, key;
			node *l, *r, *par;

			node() { lazy = 0; rev = 0; val = 0; sz = 0; key = 0; priority = 0; l = NULL; r = NULL; par = NULL;}
			node(int _val)
			{
				val = _val;
				sum = _val;
				rev = 0;
				lazy = 0;
				key = 0;
				sz = 1;
				priority = mt();

				l = nullptr;
				r = nullptr;
				par = nullptr;
			}
		};

		typedef node* pnode;

	private:
		pnode root;
		map<int, pnode> position;

		int size(pnode p) { return p ? p->sz : 0; }
		void update_size(pnode &p) { if(p) p->sz = size(p->l) + size(p->r) + 1; }

		void update_parent(pnode &p)
		{
			if(!p) return;
			if(p->l) p->l->par = p;
			if(p->r) p->r->par = p;
		}

		void push(pnode &p)
		{
			if(!p) return;		
			p->sum += size(p) * p->lazy;
			p->val += p->lazy;

			if(p->rev) swap(p->l, p->r);

			if(p->l) { p->l->lazy += p->lazy; p->l->rev ^= p->rev; }
			if(p->r) { p->r->lazy += p->lazy; p->r->rev ^= p->rev; }

			p->lazy = 0;
			p->rev = 0;
		}

		void reset(pnode &t) { if(t) t->sum = t->val; }

		void combine(pnode &t, pnode l, pnode r)
		{
			if(!l) { t = r; return; }
			if(!r) { t = l; return; }
			t->sum = l->sum + r->sum;
		}

		void operation(pnode &t)
		{
			if(!t) return;

			reset(t);
			push(t->l);
			push(t->r);

			combine(t, t->l, t);
			combine(t, t, t->r);
		}

		void split(pnode t, pnode &l, pnode &r, int k, int add = 0)
		{
			if(t == NULL) { l = NULL; r = NULL; return; }
			push(t);

			int idx	= add + size(t->l);
			if(idx <= k) 
				split(t->r, t->r, r, k, idx + 1), l = t;
			else
				split(t->l, l, t->l, k, add), r = t;

			update_parent(t);
			update_size(t);
			operation(t);
		}

		void merge(pnode &t, pnode l, pnode r)
		{
			push(l);
			push(r);

			if(!l) { t = r; return; }
			if(!r) { t = l; return; }

			if(l->priority > r->priority)
				merge(l->r, l->r, r), t = l;
			else 
				merge(r->l, l, r->l), t = r;

			update_parent(t);
			update_size(t);
			operation(t);
		}

		int get_pos(pnode curr, pnode son = nullptr)
		{
			if(!son)
			{
				if(!curr->par) return size(curr->l);
				else return size(curr->l) + get_pos(curr->par, curr);
			}

			if(!curr->par)
			{
				if(son == curr->l) return 0;
				else return size(curr->l) + 1;
			}

			if(curr->l == son) return get_pos(curr->par, curr);
			else return get_pos(curr->par, curr) + size(curr->l) + 1;
		}

	public:	
		void clear()    /// function for clearing the implicit treap.
		{
			root = NULL;
			position.clear();
		}

		inline int size() { return size(root); }    /// function which return the size of the implicit treap (the number of elements).

		implicit_treap() { clear(); }

		void insert(int pos, int key, int val)      /// function for inserting an element with value "val" at position "pos" with key "key". 
		{
			if(!root)
			{
				pnode to_add = new node(val);
				to_add->key = key;
				root = to_add;
				position[key] = root;
				return;
			}

			pnode l, r, mid;
			mid = new node(val);
			position[key] = mid;
			mid->key = key;

			split(root, l, r, pos - 1);
			merge(l, l, mid);
			merge(root, l, r);
		}

		void erase(int qL, int qR)  /// function for erasing all elements in the subarray [qL; qR].
		{
			pnode l, r, mid;

			split(root, l, r, qL - 1);
			split(r, mid, r, qR - qL);
			merge(root, l, r);
		}

		int query_sum(int qL, int qR) /// function for finding the sum of values of all element in the range [qL; qR].
		{
			pnode l, r, mid;

			split(root, l, r, qL - 1);
			split(r, mid, r, qR - qL);

			int answer = mid->sum;

			merge(r, mid, r);
			merge(root, l, r);

			return answer;
		}

		void add_value(int qL, int qR, int val)     /// function for adding "val" to the values of all elements in the interval [qL; qR]. 
		{
			pnode l, r, mid;

			split(root, l, r, qL - 1);
			split(r, mid, r, qR - qL);

			mid->lazy += val;

			merge(r, mid, r);
			merge(root, l, r);
		}


		void reverse(int qL, int qR)                /// funtion for reversing the subarray [qL; qR].
		{
			pnode l, r, mid;

			split(root, l, r, qL - 1);
			split(r, mid, r, qR - qL);

			mid->rev ^= 1;
			merge(r, mid, r);
			merge(root, l, r);
		}

		void cyclic_shift(int qL, int qR, int k)    /// function for cyclic shifting of the subbaray [qL; qR] with "k" positions.
		{
			if(qL == qR) return;
			k %= (qR - qL + 1);

			pnode l, r, mid, fh, sh;
			split(root, l, r, qL - 1);
			split(r, mid, r, qR - qL);

			split(mid, fh, sh, (qR - qL + 1) - k - 1);
			merge(mid, sh, fh);

			merge(r, mid, r);
			merge(root, l, r);
		}

		int get_position_of_key(int key) { return get_pos(position[key]); }     /// function for finding the position of the element with key "key". 

		int get_value_at_positon(int pos)    /// function for finding the value of the element at position "pos". 
		{  
			pnode l, r, mid;
			split(root, l, r, pos - 1);
			split(r, mid, r, 0);

			int ret = mid ? mid->val : -1; 
			merge(r, mid, r);
			merge(root, l, r);
			return ret;
		}

		int get_key_at_positon(int pos)      /// function for finding the key of the element at position "pos". 
		{  
			pnode l, r, mid;
			split(root, l, r, pos - 1);
			split(r, mid, r, 0);

			int ret = mid ? mid->key : -1; 
			merge(r, mid, r);
			merge(root, l, r);
			return ret;
		}

		void erase_key(int key)             /// erases the element with key "key".
		{
			pnode l, r, mid;

			int pos = get_position_of_key(key);
			
			split(root, l, r, pos - 1);
			split(r, mid, r, 0);
			merge(root, l, r);
		}
};
```

## Reference

- Invert BST: https://afteracademy.com/blog/invert-a-binary-tree
- Cartesian heaps:https://cp-algorithms.com/data_structures/treap.html

### Treap and Implicity Treap
1. [Treap (Cartesian tree). CP-Algorithm](https://cp-algorithms.com/data_structures/treap.html#toc-tgt-1)
2. [Treaps : One Tree to Rule ’em all ..!! Part-1](https://tanujkhattar.wordpress.com/2016/01/10/treaps-one-tree-to-rule-em-all-part-1/)
3. [Treaps : One Tree to Rule ’em all ..!! Part-2](https://tanujkhattar.wordpress.com/2016/01/10/treaps-one-tree-to-rule-em-all-part-2/)
4. [Episode 30 - Treaps. YouTube](https://youtu.be/erKlLEXLKyY?t=1785)
5. [A Visual Introduction to Treap Data Structure (Part I: The Basics). Medium](https://medium.com/carpanese/a-visual-introduction-to-treap-data-structure-part-1-6196d6cc12ee)
6. [Implicity Heap. Java](https://github.com/radoslav11/Implicit-treap/blob/master/implicit_treap.cpp)