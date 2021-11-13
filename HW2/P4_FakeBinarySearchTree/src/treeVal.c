#include "treeVal.h"


problem init_problem(int N_nodes){
    problem prob;
    prob.n = N_nodes;
    int N = N_nodes+30;
    prob.nodes = (Node*)malloc(N*sizeof(Node));

    //Initialize node
    for(int i=0;i<N;i++){
        prob.nodes[i].parent = NULL;
        prob.nodes[i].leaf[0] = NULL;
        prob.nodes[i].leaf[1] = NULL;
        prob.nodes[i].visited = 0;
    }

    return prob;
}

void kill_problem(problem prob){
    free(prob.nodes);
}

void CreateNodes(problem prob, int ID, int key, int IDleft, int IDright){
    Node* node = &prob.nodes[ID];
    node->key = key;
    node->visited=0;

    if (IDleft!=-1){
        node->leaf[0] = &prob.nodes[IDleft];
        prob.nodes[IDleft].parent = node;
    }
    else
        node->leaf[0] = NULL;

    if(IDright!=-1){
        node->leaf[1] = &prob.nodes[IDright];
        prob.nodes[IDright].parent = node;
    }
    else 
        node->leaf[1] = NULL;
}


int findOrigin(Node* node){
    if(node->parent == NULL){
        return -1;
    }
    else if(node->parent->leaf[0] == node && node->leaf[0] != node){
        return 0;
    }
    else if(node->parent->leaf[1] == node && node->leaf[1] != node){
        return 1;
    }
    else{
        return -1;
    }
}


int valid_tree_walk(Node* node, int min, int max){

    assert(node!=NULL);

    Node* l = node->leaf[0];
    Node* r = node->leaf[1];
    Node* p = node->parent;
    int key = node->key;
    int n = 0;
    int valid=0;


    
    //check validity
    if( inBound(key, min, max) == 1){
        ++n;
    }


    //Traversal
    if (r!=NULL){
        n+=valid_tree_walk(r, chooseMax(min, key), max);
    }

    if (l!=NULL){
        n+=valid_tree_walk(l, min, chooseMin(max,key));

    }

    return n;
}


void interface(void){
    int N_nodes;
    int key, IDleft, IDright;
    int N_reach;

    scanf("%d", &N_nodes);

    problem prob = init_problem(N_nodes);

    for(int i=1; i<=N_nodes;i++){
        scanf("%d", &key);
        scanf("%d", &IDleft);
        scanf("%d", &IDright);

        CreateNodes(prob, i, key, IDleft, IDright);
    }

    if(&prob.nodes[1]==NULL){
        N_reach = 0;
    }
    else{
        N_reach = valid_tree_walk(&prob.nodes[1], INT_MIN, INT_MAX);
    }

    printf("%d", N_reach);

    kill_problem(prob);
}
