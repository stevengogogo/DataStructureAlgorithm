/**
 * @file utils.h
 * @author Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief General Utilities for C language
 * @version 0.1
 * @date 2021-03-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <float.h>

#define error_tol 

typedef enum OPERATOR Operator;
enum OPERATOR {
    PLUS, // +
    MINUS, // -
    MULT, // *
    DIV, // /
    LP, // (
    RP  // )
};

/** Compare two double
 * @ref Reddit: https://www.reddit.com/r/C_Programming/comments/4thsn7/comparing_doubles_in_c/d5iduhx?utm_source=share&utm_medium=web2x&context=3
*/
int is_double_equal(double a, double b);
double max_double(double a, double b);

#endif