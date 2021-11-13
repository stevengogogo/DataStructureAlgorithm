/**
 * @file main.c
 * @brief Interface of the nonogram solver
 */
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "NonogramSolver.h"


/* * @brief Interface */
int main()
{


    nogram nog;
    
    //nog = create_nogram_fscantf("test/data/input_col.txt");
    nog = create_nogram_scantf();
    solve_nonogram(&nog);
    printf_map(nog);
    return 0;
}