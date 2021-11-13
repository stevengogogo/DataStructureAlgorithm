#ifndef eqeval_H
#define eqeval_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h> //isdigit(), ispunct()
#include "utils.h"
#include "stack.h"

#define MAX_INPUT 2000000

/** pop an operator or a number (in string) and move the pin forward.
 * @param eq_str The string of equation
 * @param rpin start site for reading
 * @param placeholder printout
 * @return number of characters has been read
*/
int pop_streq_item(char* eq_str, int*  rpin, char* placeholder);
/** Convert the first element of string to enum operator*/
Operator str2op(char*);
/** Convert string to double. Wrapper of `atof`*/
double str2double(char*);






double eval_string(char*);


#endif