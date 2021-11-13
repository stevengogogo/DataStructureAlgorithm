---
puppeteer:
  landscape: false
  format: "A4"
  timeout: 500 # <= Special config, which means waitFor 3000 ms
  export_on_save:
    puppeteer: true # export PDF on save
    puppeteer: ["pdf"] # export PDF and PNG files on save
---
<center>

# Report

Your name
`Email`

</center>


## Code

### H3
#### H4
##### H5
###### H6


```c  {.line-numbers}
int a;
```

## Citation


Something important [^1][^3].

## Equations

$$
\begin{align}
 \lim_{n\rightarrow\infty} \frac{f}{g} &= 0 \\
 &= 3
\end{align}
$$


[^1]: Citation 1
[^3]: Auto indexing
