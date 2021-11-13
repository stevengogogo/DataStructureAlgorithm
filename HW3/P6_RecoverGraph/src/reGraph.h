/**
 * @file reGraph.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef REGRAPH_H
#define REGRAPH_H
#define INIT_ADJ_LEN 1000
#define MAXEDGE 210000
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "utils.h"


/**
 * @brief Adjacency list
 * @param lists lists of vertexes. Neighbor are stored at list[0,..n] 
 * @param n number of vertexes
 */
typedef struct {
    que* ques;
    int n; 
} adjlist;

// Init and kill
/**
 * @brief Create adjacency list with n vertexes
 * 
 * @param n number of vertexes
 * @return adjlist 
 */
adjlist init_adjlist(int n);
void kill_adjlist(adjlist*);

//Add edge
/**
 * @brief Add edge to link v to u
 * 
 * @param u starting vertex [1, N]
 * @param v ending vertex
 */
void add_edge(adjlist*, int u, int v);


//Validation

//path
typedef struct {
    int* vs;
    dymArr visited_v;
    int len; //length of visited list
    int num_v; //length of VS
} path;

path init_path(int size);
void kill_path(path*);
void append_path(path*, int u);
int pop_path(path*);
void clear_path(path*);

/**
 * @brief Check circular reference. 
 */
bool is_circle(path*, int val);

//Edge list
typedef struct {
    dymArr u;
    dymArr v;
    bool valid;
} edgeList;

edgeList init_edgeList(int size);
void kill_edgeList(edgeList*);
void print_edgeList(edgeList);
void append_edge(edgeList*, int u, int v);

edgeList GraphReconstruct(adjlist*);
bool deque_adjList(adjlist*, edgeList*, path* pathc, path* pathl, int vtx);

int interface(void);


#endif 