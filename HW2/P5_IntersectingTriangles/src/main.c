/**
 * @file main.c
 * @author Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief Get Triangle Intersections with Merge sort
 * @version 0.1
 * @date 2021-05-04
 * @note Acknowledgement: TAs on Monday afternoon, Thursday afternoon have helped me on This  project. Besides, I have shared my idea about how to count identical P with CSIE studet HSU, CHIH-CHUAN via NTU COOL. I kept sharing the abstract idea while the variable `Iden` is mentioned to him that is related to the source code @ref MERGE_COUNT_INVERSION. Also, Lin (0110420@stu.nknush.kh.edu.tw) provided a critical hint to my debug process. That is the overflow problem when saving `int` with the number of pair (max: 3e12). See Documentation: https://stevengogogo.github.io/DSA_IntersectingTriangles/globals.html for details [Public]. The repository will be public one week after the deadline: https://github.com/stevengogogo/DSA_IntersectingTriangles.
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "intersect.h"
#include "generator.h"

int main()
{
    
   // Interface
    generator.init();
    int t = generator.getT();

    for(int i=0;i<t;i++){
        int n, *p, *q, *r;
        generator.getData(&n, &p, &q, &r);

        ulong ans = get_intersects(n, p, q, r);
        printf("%ld\n", ans);
    }


    return 0;
}