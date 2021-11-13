#ifndef TREEVAL_H
#define TREEVAL_H


#include <stdio.h> //NULL
#include <stdlib.h> //malloc
#include "utils.h"

#define INT_MIN 0
#define INT_MAX 1000000001
#define MAX_N 1100000

typedef struct Node{
    int key;
    struct Node* leaf[2];
} Node;

typedef struct {
    Node* nodes;
    int n;
} problem;


problem init_problem(int N_nodes);
void kill_problem(problem);

void CreateNodes(problem, int ID, int key, int IDleft, int IDright);


int valid_tree_walk(Node* node, int min, int max);

void interface(void);

#endif