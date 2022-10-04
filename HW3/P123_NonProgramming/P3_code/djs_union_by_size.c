#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int _ = *a;
    *a = *b;
    *b = _;
}

struct Stack_element {
    int x;
    int *x_ptr;
    struct Stack_element *pre, *nxt;
};

struct Stack {
    struct Stack_element *head, *tail;
    int sz;
};

void stack_init(struct Stack *stack) {
    stack->head = (struct Stack_element*)malloc(sizeof(struct Stack_element));
    stack->tail = (struct Stack_element*)malloc(sizeof(struct Stack_element));
    stack->head->nxt = stack->tail; stack->head->pre = NULL;
    stack->tail->pre = stack->head; stack->tail->nxt = NULL;
    stack->sz = 0;
}

void stack_push(struct Stack *stack, int x, int *y) {
    struct Stack_element* e = (struct Stack_element*)malloc(sizeof(struct Stack_element));
    e->x = x;
    e->x_ptr = y;
    stack->tail->pre->nxt = e;
    e->pre = stack->tail->pre;
    e->nxt = stack->tail;
    stack->tail->pre = e;
    ++stack->sz;
}

struct Stack_element* stack_top(struct Stack *stack) {
    if (stack->tail->pre == stack->head) for(;;);
    return stack->tail->pre;
}

void stack_pop(struct Stack *stack) {
    if (stack->tail->pre == stack->head) for(;;);
    stack->tail->pre = stack->tail->pre->pre;
    stack->tail->pre->nxt = stack->tail;
    --stack->sz;
}

struct DisjointSet {
    int *p, *sz;
    int cc; // number of connected component
    struct Stack stk, memo;
};

void djs_init(struct DisjointSet* djs, int n) {
    djs->p = (int*)malloc(n * sizeof(int));
    djs->sz = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        djs->p[i] = i;
        djs->sz[i] = 1;
    }
    djs->cc = n;
    stack_init(&djs->stk);
    stack_init(&djs->memo);
}

void djs_save(struct DisjointSet *djs) {
    stack_push(&djs->stk, djs->memo.sz, &djs->memo.sz);
}

void djs_undo(struct DisjointSet* djs) {
    while (djs->memo.sz > stack_top(&djs->stk)->x) {
        *stack_top(&djs->memo)->x_ptr = stack_top(&djs->memo)->x;
        stack_pop(&djs->memo);
    }
    stack_pop(&djs->stk);
}

void djs_assign(struct DisjointSet* djs, int *x, int v) {
    stack_push(&djs->memo, *x, x);
    *x = v;
}

int djs_find(struct DisjointSet* djs, int x) {
    return djs->p[x] == x ? x : djs_find(djs, djs->p[x]);
}

void djs_union(struct DisjointSet* djs, int x, int y) {
    x = djs_find(djs, x), y = djs_find(djs, y);
    if (x == y) return;
    if (djs->sz[x] < djs->sz[y]) {
        swap(&x, &y);
    }
    djs_assign(djs, &djs->p[y], x);
    djs_assign(djs, &djs->sz[x], djs->sz[x] + djs->sz[y]);
    djs_assign(djs, &djs->cc, djs->cc - 1);
}

void init(struct DisjointSet *djs, int n) {
    djs_init(djs, n);
}

void add_edge(struct DisjointSet* djs, int x, int y) {
    djs_save(djs);
    djs_union(djs, x, y);
}

void undo(struct DisjointSet* djs) {
    djs_undo(djs);
}

void show_cc(struct DisjointSet *djs) {
    printf("%d\n", djs->cc);
}

int main () {
    // below is an example code
    struct DisjointSet djs;
    init(&djs, 5);
    show_cc(&djs);
    add_edge(&djs, 1, 2);
    add_edge(&djs, 1, 3);
    show_cc(&djs);
    undo(&djs);
    show_cc(&djs);
    undo(&djs);
    show_cc(&djs);
}