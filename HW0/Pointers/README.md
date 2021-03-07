# Prolem 3 - *(Human Compiler)(Hand-written)

## Problem 3a: Swaps two arrays using pointers

![Screen Shot 2021-03-07 at 8 34 25 AM](https://user-images.githubusercontent.com/29009898/110225352-efdec580-7f1f-11eb-9675-516acb605e42.png)


```c
int fake_a[] = {1,3};
int fake_b[] = {2,4};
int *real_a = fake_a;
int *real_b = fake_b;

for(int i=0;i<2;i++)
    printf("%d", *(real_a + i));
for(int i=0;i<2;i++)
    printf("%d", *(real_b + i));

int *tmp = real_a; //tmp is a pointer to pointer
real_b = fake_a;  // fill the blanks
real_a = fake_b;  // fil the blanks

for(int i=0;i<2;i++)
    printf("%d", *(real_a + i));
for(int i=0;i<2;i++)
    printf("%d", *(real_b + i));
```

Test at: https://onlinegdb.com/SJ4JFi-7_

![](img/Problem3a.png)

---

## Problem 3b: An array supporting negative indices

![Screen Shot 2021-03-07 at 9 17 08 AM](https://user-images.githubusercontent.com/29009898/110226009-f7a16880-7f25-11eb-81db-7c27eb264c33.png)

```c
#include <stdio.h>
#define MINN -50
#define MAXN 50

int main(){
    int storage[MAXN - MINN + 1] = {0}; // 101
    int *ary = storage - MINN ; //fill the blank

    for(int i=MINN;i<=MAXN;i++)
        ary[i] = i;
    for(int i=MINN;i<=MAXN;i++)
        printf("%d", ary[i]);
    return 0;
}
```
Verified at: https://onlinegdb.com/rydhl3W7u

![](img/Problem3b.png)

---

## Problem 3C: Tranverses data nodes in a linked list.

![Screen Shot 2021-03-07 at 12 03 34 PM](https://user-images.githubusercontent.com/29009898/110228580-38f14280-7f3d-11eb-9891-65aeaeb849e0.png)

```c
#include <stdio.h>
#include <stdlib.h> //malloc / free
#include <memory.h> //memset

//use typedef to define "struct node" as "node"
typedef struct node{
    int data;
    struct node *nxt;
} node;

node* alloc(int data, node* nxt){
    node *tmp = (node*)malloc(sizeof(node));
    tmp->data=data;
    tmp->nxt = nxt;
    return tmp;
}

void destroy(node *head){
    if(head != NULL){ //FIll the blank 
        destroy(head->nxt);
        //clean sensitive data;
        memset(head,0,sizeof(head));
        free(head);
    }
}

int main(){
    // create nodes [0,1,2,4]
    node* head = alloc(0, alloc(1,alloc(2,alloc(4,NULL))));
    node* tmp = head;
    //print the nodes subsequently
    while(tmp!=NULL){
        printf("%d -> ", *tmp-> data ); //FIll the blank 
        tmp = (*tmp)->nxt; //FIll the blank 
    }
    printf("NULL");

    //free the nodes subsequently to avoid memory leak
    destroy(head);
    return 0;
}
```

### Curate

Use `temp->data` not `(*tmp)->data`

#### Copy a pointer to another pointer

![Screen Shot 2021-03-07 at 12 31 17 PM](https://user-images.githubusercontent.com/29009898/110229016-09dcd000-7f41-11eb-9414-77bad043e4c8.png)
> From [Basics of C Programmin](https://computer.howstuffworks.com/c24.htm)

### Question 

Wrong version: https://www.onlinegdb.com/
Corrected version: https://onlinegdb.com/BkReV0bXd

---

## Problem 3D: Binary Tree
![Screen Shot 2021-03-07 at 11 52 38 AM](https://user-images.githubusercontent.com/29009898/110228385-9f756100-7f3b-11eb-92e7-76ee4bf3413f.png)
![Screen Shot 2021-03-07 at 11 52 48 AM](https://user-images.githubusercontent.com/29009898/110228386-a603d880-7f3b-11eb-9108-fb2e0b11d480.png)

**問題**: `printf` 應該在 `if` 前面

```c
#include <stdio.h>
#include <stdlib.h> //malloc /free
#include <memory.h> //memset

//use typedef to substitute "struct node with "node""
typedef struct node {
    int data;
    struct node *left, *right;
} node;

//creates a node filledwith predefined values
node* alloc(int data, node *left, node *right){
    node *tmp = (node*)malloc(sizeof(node));
    tmp->data = data,
    tmp->left = left;
    tmp->right = right;
    return tmp;
}

//traverses (遍歷) the nodes recursively
void traverse(node* root){
    printf("%d", root->data);
    if ((root->left != NULL) & (root->right != NULL)){
        traverse(root->left);
        traverse(root->right);
    }
}

//frees the nodes recursively
void destroy(node *root){
    if ((root->left != NULL) & (root->right!=NULL)){
        destroy(root->left);
        destroy(root->right);
        //clean sensitive data
        memset(root, 0, sizeof(root));
        free(root);
    }
}

int main(){
    // creates a hierarchical data structure
    node *root = \
        alloc(0,
            alloc(3,
                alloc(7, NULL, NULL),
                alloc(4, NULL, NULL)
            ),
            alloc(2,
                alloc(1, NULL, NULL),
                alloc(9, NULL, NULL)
            )
        );

    traverse(root);
    destroy(root);
}
```
Verify at: https://onlinegdb.com/r1VxlA-7d
![](img/Problem3c.png)

---

## Notes

### Null Pointer and `Segmentation fault`

- Segmentation fault: 
    > Segmentation fault is a specific kind of error caused by accessing memory that “does not belong to you
- NULL Pointer
    > People assign NULL to pointer to indicate that it points to nothing.

### Read Only String and its Dynamical type

- `char* str` Read only: able to share among functions
    ```c
    char *str = "gfg"; 
    ```
    Read only. `str[0]=a` leads to segmentation fault. Noted that read-only string can be passed among functions:
    ```c
    char *getString(){
    char *str = "GfG"; /* Stored in read only part of shared segment */

    /* No problem: remains at address str after getString() returns*/
    return str; 
    }	 

    int main(){
    printf("%s", getString()); 
    getchar();
    return 0;
    }

    ```
- `char str[]` Mutable string: unable to share among functions.
    ```c
    int main(){
        char str[];
        str = "gfg";
    }
    ```
- Store in heap: allow to share and modify
    ```c
    char *getString()
    {
    int size = 4;
    char *str = (char *)malloc(sizeof(char)*size); /*Stored in heap segment*/
    *(str+0) = 'G'; 
    *(str+1) = 'f';  
    *(str+2) = 'G';
    *(str+3) = '\0';  
    
    /* No problem: string remains at str after getString() returns */   
    return str;  
    }     
    int main()
    {
    printf("%s", getString());  
    getchar();
    return 0;
    }
    ```

---
## Reference
1. Segmentation fault and pointer. [[stackoverflow](https://stackoverflow.com/questions/17873561/pointer-initialisation-gives-segmentation-fault)]
2. String and storage. [[GreekforGeek](https://www.geeksforgeeks.org/storage-for-strings-in-c/)]
3. Pointing to the same address. [[eBook-Basics of C Programming](https://computer.howstuffworks.com/c24.htm)]