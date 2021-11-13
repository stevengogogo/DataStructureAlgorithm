#include "list.h"


node* init_node(int data){
    node* init = (node*)malloc(sizeof(node));
    assert(init != NULL);
    init->data = data;
    init->ngb[0] = NULL;
    init->ngb[1] = NULL;

    return init;
}

list init_list(){
    list line = {
        .str = NULL,
        .end = NULL
    };
    return line;
}

void detach_list(list* line){
    line->str = NULL;
    line->end = NULL;
}

void kill_node(node* n){
    n->data = -1;
    free(n);
}

void kill_list(list* line){
    while(line->end != NULL){
        leave(line);
    }
}

int PrintList(list* line){
    if (line->str == NULL)
        return 0;
    else if (line->str != NULL && line->end != NULL){
        return iter_read(line->str);
    }
    else {
        return -1; // Error code
    }
}

int printNode(node* nStr){
    if (nStr->data < 0)
        return -1;
    printf("%d", nStr->data);
    return 0;
}

int iter_read(node* nStr){
    int flag = get_flag2node(nStr);

    assert(printNode(nStr) != -1 );
    printf(" "); //spacing

    if (flag==-1) // With only one node
        return 1;
    
    node* ptr_pre = nStr;
    node* current_node = nStr->ngb[flag];
    int len=1;

    while(current_node != NULL){
        //Print
        assert(printNode(current_node) != -1);
        //Spacing
        printf(" ");
        // Update flat
        if (current_node->ngb[flag] == ptr_pre)
            flag = flag ^ 1; //xor
        
        //move
        ptr_pre = current_node;
        current_node = current_node->ngb[flag];

        len++;
    }

    return len;

}



int get_flag2node(node* terminal_node){

     node* left =  terminal_node->ngb[0]; 
     node* right = terminal_node->ngb[1];

    assert( ((left == NULL) || (right == NULL) ) ); // one of ends is null

    if (left==NULL && right == NULL)
        return -1;

    if (left != NULL && right == NULL)
        return 0;
    
    if (left == NULL && right != NULL)
        return 1;
}

int get_flag2null(node* terminal_node){
    int flag2node = get_flag2node(terminal_node);

    if (flag2node == -1)
        return 2;
    else 
        return flag2node^1;
    
}

int get_flag2dst(node* src, node* dst){
    if( src->ngb[0] == dst ){
        return 0;
    }
    else if(src->ngb[1] == dst){
        return 1;
    }
    else {
        return -1;
    }
}

//Operations
int leave(list* line){
    int flag;
    int flag_back;

    node* last_n = line->end;
    if(line->end != NULL){
        flag = get_flag2node(line->end);
        
        if (flag==-1){ // Only one element
            assert(line->str == line->end); // Assign to same node
            line->str = NULL;
            line->end = NULL;
            kill_node(last_n);
            return 1;
        }


        line->end = line->end->ngb[flag];
        // Get to pointer to last node
        flag_back = get_flag2dst(line->end, last_n);
        assert(flag_back != -1); // success link back

        line->end->ngb[flag_back] = NULL;
        
        kill_node(last_n);

        return 1;
    }
    else {
        return -1;
    }
}

int enter(list* line, int log){
    node* new = init_node(log);

    if(line->str == NULL){ //start a new line
        assert(line->end == NULL); //null line
        line->str = new;
        line->end = new;

        return 1;
    }

    else if (line->str != NULL && line->end != NULL){ 
        int flag = get_flag2null(line->end);

        if (flag == 2){
            flag = 1;
        }

        // Bridge last to new block
        line->end->ngb[flag] = new;

        // Bridge New block
        new->ngb[flag] = NULL;
        new->ngb[flag^1] = line->end;

        // move terminal to new
        line->end = new;

        return 1;
    }

    else {
        return -1;
    }
}

void migrate(list* src, list* dst){
    if (src->str == NULL){
        // src is null
    }
    
    else {
        if (dst->str == NULL){ // dst is null
            assert(src->end != NULL);
            //swap terminals
            dst->str = src->end;
            dst->end = src->str;
            detach_list(src); //clear list
        }
        else { // neither src nor dst are null

            // Get direction to null
            int flag_src_null = get_flag2null(src->end);
            int flag_dst_null = get_flag2null(dst->end);
            
            // For 1 element
            if (flag_src_null == 2)
                flag_src_null = 1;
            if (flag_dst_null == 2)
                flag_dst_null = 1;

            // Bridging
            src->end->ngb[flag_src_null] = dst->end;
            dst->end->ngb[flag_dst_null] = src->end;

            // Reset terminals
            dst->end = src->str;
            detach_list(src); //clear list
        }
    }
}


// Interface

void interact_scanf(void){
    int k,n;
    int a,b;
    int ch=-1;
    char oper[MAX_LEN_OPER_STR];

    list lines[MAX_LINES];


    scanf("%d", &k);
    scanf("%d", &n);

    //Initiate lines
    for (int i=0;i<k; i++){
        lines[i] = init_list();
    }

    for (int i=0;i<n; i++){
        scanf("%s", oper);

        if (strcmp(oper, "leave") == 0){
            scanf("%d", &a);
            leave(&lines[a]);
        }

        else if (strcmp(oper, "migrate") == 0){
            scanf("%d%d", &a, &b);
            migrate(&lines[a], &lines[b]);
        }

        else if (strcmp(oper, "enter") == 0){
            scanf("%d%d", &a, &b);
            enter(&lines[a], b);
        }

        else {
            printf("Error");
        }
    }

    for (int i=0;i<k;i++){
        ch = PrintList(&lines[i]);
        if (i!=k-1)
            printf("\n");
        assert(ch!=-1); 
    }

    //kill
    for (int i=0;i<k;i++)
        kill_list(&lines[i]);
}