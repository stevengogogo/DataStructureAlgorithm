# Master Theorem: Time complexity of recursive functions

## Recurrence Relation

Consider a program:

```pseudo
func Sum(n int) int {
    if n == 1{
        return 1
    }
    return n + Sum(n-1)
}
```

Derive: $T(n) = 1 + T(n-1)$

## Master Theorem 

> The master theorem is a recipe that gives asymptotic estimates for a recurrence relations

- Let $a\geq 1$ and $b \geq 1$ be constants
- let $f(n)$ be a function. 
- let $T(n)$ be a recurrence function

$$T(n) = a T(\frac{n}{b}) + f(n)$$

- if $f(n) = \Theta(n^d)$, where $d\geq 0$ then 

- If $a < b^d$
    - $T(n) = \Theta(n^d)$
- If $a = b^d$
    - $T(n) = \Theta(n^d \log n)$
- If $a > b^d $
    - $T(n) = \Theta(n^{\log_b a})$