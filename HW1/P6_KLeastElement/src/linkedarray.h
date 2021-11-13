/**
 * @file linkedarray.h
 * @author Steven Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief Unrolled linked list for finding K-least element
 * @version 0.1
 * @date 2021-04-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LINKEDARRAY_H
#define LINKEDARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "utils.h"

#define subN 3000

/** * Node with arrays.
 * @param len length of stored data
 * @param isSorted `0` for unsorted array, `1` sorted
 * @param flag direction of reading. `0` means starts from head; `1` end.
 * @param arrInx Data in index order
 * @param arrSort Array for ordered data
 * Ref: 
 * - Design: https://github.com/stevengogogo/DSA-KLeastElement
 */
typedef struct node{
    int len;
    int isSorted;
    int flag;
    int arrInx[subN+100];
    int arrSort[subN+100];
    struct node* nextNode;
} LnkArr;


/**
 * @brief Position in linked array
 * @param node the array contains the ith member
 * @param i index in node.array[i]
 * @param isEnd is i-1 the end of the sequence? 
 *              - 0 means node.array[i] is the ith position
 *              - 1 means node.array[i] is the (i-1)th position
 */
typedef struct {
    LnkArr* node;
    LnkArr* nodePrev;
    LnkArr* nodeNext;
    int i;
    int isEnd;
    int numCum;
} Loc;

typedef struct {
    Loc str;
    Loc end;
} StrEndLoc;



/** * Initiate empty linked array */
LnkArr* init_list_empty(void);
void kill_list(LnkArr*);


/** * Insert x at ith position. i starts at 1
 * @return 1 create new node, 0
*/
int insert(LnkArr*, int i, int x);

void insertLArray(Loc nodeLoc, int x);

/**
 * @brief Split the node to extend. The splited node is wired to the next node
 * 
 * @param nodeLoc 
 * @return Loc Location of first node.
 */
void splitNode(Loc nodeLoc);

/** * Query
 * @param l lower bound lth element
 * @param r upper bound r-th element
 * @param k k least 
 * @return k-least element
 */
int query(LnkArr* list, int l, int r, int k);

/** * Delete */
int delete(LnkArr* list, int i);
/** * Remove an element*/
void remove_LArray(Loc nodeLoc);
/** * Free the node*/
void kill_LArray(Loc nodeLoc);

/** * Reverse */
int reverse(LnkArr** list, int str, int end);


/***/
int reverseSplit(LnkArr** list, Loc* nodeStr, Loc* nodeEnd, int Istr, int Iend);

int reversePartLA(Loc nodeStr, Loc nodeEnd);

/** @brief Flip nodes between start to end nodes, including themselves. The effect region is (start.Prevnode, End.Nextnode)
 * @warning The flip action reverse all the members from nodeStr.node[1,end] to nodeEnd.node[1,end].  
 * @return 1 if head list is changed.
 */
int flipFullNodes(LnkArr** list,Loc nodeStr, Loc nodeEnd);

int flipFullNodes_nodes(LnkArr** list, LnkArr* StrNode, LnkArr* StrPrevNode,LnkArr* EndNode, LnkArr* EndNodePrev);

/** * Reverse inside the node*/
int reverseInNodes(Loc nodeStr, Loc nodeEnd);


/** * Find the position in linked array */
Loc find_LnkArr_ith(LnkArr* headList, int i);

/** * Find ith begin with a start node and sum of previous length */
Loc find_LnkArr_ith_bounded(LnkArr* startNode, LnkArr* prevNode, int sumLenPrev, int i);

/** * @return [nodeStr, nodeEnd] */
StrEndLoc find_start_end_LA(LnkArr* headlist, int str, int end);

/** * Get ith variable */
int get_ith_var(LnkArr* headList, int i);

int get_i2read(int i, int flag, int length);

/** * get node.arr[i] from loc */
int getINode(Loc);

/** * get end i*/
int getINodeEnd(Loc);

/** * Get start */
int getINodeStr(Loc);



void update_orderArr(LnkArr* node);

int convert_flag(LnkArr* node);


/** * Make the node sorted. Do nothing if the array is already sorted
 * @return 1 if sorting happened; 0 otherwise
 */
int sortNode(LnkArr*);

/** @brief sort array between start and end node (including terminals)*/
MinMax sortBetween(Loc nodeStr, Loc nodeEnd);

/** Find min max in same array
 * @warning `nodeStr` and `nodeEnd` is asserted on the same array 
*/
MinMax findMinMaxLA(Loc nodeStr, Loc nodeEnd);

/**
 * @brief Measure how many items is smaller than `key`.
 * @details Linear search for terminal arrays is made by \ref NumItemSmaller_Screen ; binary search for full array is done by \ref NumItemSmaller_Sorted
 * @param StrEnd 
 * @param key 
 * @return int number of items smaller than key.
 */
int NumItemSmaller(StrEndLoc StrEnd, int key);


void interface(void);
void interfaceDebuggingFile(char* filename);
int compare_LA_array(array* arr, LnkArr* list);
int compare_InxOrder(LnkArr*list);
#endif
