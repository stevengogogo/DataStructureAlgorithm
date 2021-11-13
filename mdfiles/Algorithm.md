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

## Master Theorem Definition 1

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


## Master Theorem Definition 2

- Let $a\geq 1$ and $b>1$ be constants
- Let $f(n)$ be a function
- $T(n)$ be a recurrence function:

$$T(n) = a T(\frac{n}{b})$$

1.  If $f(n) = O(n^{\log_b a - \epsilon})$, for some constant $\epsilon > 0 $, then $T = \Theta(n^{log_b a})$
2. If $f(n) = \Theta(n^{\log_b a})$, then $T(n) = \Theta (n^{\log_b a} \log n)$
3. If $f(n) = \Omega (n^{\log_b a + \epsilon})$, for some constant $\epsilon >0$. And if $a f(n/b) \leq cf(n)$ for some constant $c<1$. $T(n) = \Theta(f(n))$


Noted: 
- $O$ is upper bound
- $\Theta$: is equal
- $\Omega$: is lower bound


### Examples

- $T(n) = 9T(n/3) + n$
    - $a=9$, $b=3$, $f(n)=n$
    - $f(n) =  O(n^{\overbrace{\log_{3}9}^{2}} )$
    - $T(n) = \Theta(n^{\log_{a} b}) = \Theta(n^2)_{\#}$
- $T(n) = 3T(n/4) + n\log n$
    - $a=3$, $b=4$, $f(n) = n\log n$
    - $n^{\log_{b}a} \approx n^{0.793}$. Therefore, $f(n) = \Omega(n^{\log_b a + \epsilon})$.
    - $T(n) = \Theta(n\log n)$

- Special case
    - $T(n) = 2T(n/2) + n\log n$
    - $n\log n$ is not polynomially larger than $n$
    - `(AST) Exercise 4.6-2` 
        - If $f(n) = \Theta (n^{log_b a}  \log^k n)$ where $k\geq 0$
        - $T(n) = \Theta(n^{log_b a}\log^{k+1} n)$