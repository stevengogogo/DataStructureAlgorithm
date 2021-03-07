# Prolem 3 - *(Human Compiler)(Hand-written)


## Problem 3-(a) Swaps two arrays using pointers

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



![](img/Problem3a.png)




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