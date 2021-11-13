/**
 * @file list.h
 * @author Shao-Ting Chiu
 * @brief Double linked list. This implementation provides O(1) complexity for reversing. See main page for details. This implementataion sacrifices the speed of reading. It requires the check of the flag to the next node  when moving from one node to another. However, HW1 P5 only needs to read the lines once. Noted that the direction of the next node is updated by XOR operation, so this double linked list is also known as XOR double linked list (https://en.wikipedia.org/wiki/XOR_linked_list).
 * @version 0.1
 * @date 2021-04-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1010
#define MAX_LEN_OPER_STR 100


typedef struct _node{
    int data;
    struct _node* ngb[2]; // neighbor
} node;

typedef struct {
    node* str;
    node* end;
} list;


// Constructor and Descructor
node* init_node(int data);
list init_list(void);
void detach_list(list* line);
void kill_node(node*);
void kill_list(list*);

int PrintList(list*);
int printNode(node* nStr);
int iter_read(node*);

/**
 * @brief Read the linked list from the first node to the last. Which is linked to the NULL
 * 
 * @return int -1 for error report
 */
int iter_read(node*);

/** get the flag point to the node. This function assumes a node is linked to at least one node */
int get_flag2node(node* terminal_node);

/**
 * @brief Get the flag to reach NULL. The index is returned to get the node->ngb[index] = NULL.
 * 
 * @param terminal_node 
 * @return int `2` for two NULL neigbhors, `0` and `1` for flags. 
 */
int get_flag2null(node* terminal_node);

/* Return the direction to the dst. -1 for missing */
int get_flag2dst(node* src, node* dst);


//Operations

/** Return 1 if one element is pop; -1 for none */
int leave(list*);

/**
 * @brief Insert new element
 * 
 * @param log new data
 * @return int `1` for success adding; `-1` as error code
 */
int enter(list*, int log);

/**
 * @brief 
 * 
 * @param src source line
 * @param dst destination line
 */
void migrate(list* src, list* dst);


/** interface. Use `stdin` for manipulating the linked lists */
void interact_scanf(void);

#endif