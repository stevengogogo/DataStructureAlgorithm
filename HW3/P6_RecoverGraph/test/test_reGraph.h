#ifndef TEST_REGRAPH_H
#define TEST_REGRAPH_H

#include "reGraph.h"
#include "acutest.h"


void test_build(void){
    adjlist adl = init_adjlist(100);

    for(int i=1;i<=100;i++){
        for(int j=1;j<=100;j++)
            add_edge(&adl,i,j);
    }

    for(int i=1;i<=100;i++){
        for(int j=1;j<=100;j++){
            TEST_CHECK(get_item(adl.lists[i], j) == j);
        }
    }    
    


    kill_adjlist(&adl);
}


#endif