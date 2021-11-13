#include "linkedarray.h"



LnkArr* init_list_empty(void){
    LnkArr* list = (LnkArr*)malloc( sizeof(LnkArr) );
    list->flag = 0;
    list->isSorted = 0;
    list->len = 0;
    list->nextNode = NULL;
    return list;
}

void kill_list(LnkArr* list){
    LnkArr* nxt;
    LnkArr* cur=list;
    
    while (cur != NULL){
        nxt = cur->nextNode;
        free(cur);
        cur = nxt;
    }
}



int insert(LnkArr* list, int i, int x){
    int isSplit = 0;
    Loc iloc = find_LnkArr_ith(list, i);

    assert(iloc.node->len <= subN);
    if(iloc.node->len == subN/2){ // insufficient space 
        splitNode(iloc);
        ++isSplit;
        iloc = find_LnkArr_ith(list, i);
    }

    insertLArray(iloc, x);
    return isSplit;
}

void insertLArray(Loc nodeLoc, int x){
    int flag = nodeLoc.node->flag;
    int len = nodeLoc.node->len;
    int* arr = nodeLoc.node->arrInx;
    int* arrS = nodeLoc.node->arrSort;
    int i = nodeLoc.i + nodeLoc.isEnd; //ith position
    int i_ = (flag==1) ? (len - 1) - i + 1 : i; // convert to array position. +1 for flag = 1

    ++(nodeLoc.node->len); //expand array length
    insert_arr(arr, i_, x, nodeLoc.node->len);

    if (nodeLoc.node->isSorted){
        int i_sorted = BinarySearch_MaxSmaller(arrS, len, x);
        ++i_sorted;
        insert_arr(arrS, i_sorted, x, nodeLoc.node->len);
    }
    else{
        insert_arr(arrS, i_, x, nodeLoc.node->len); // same operation with indexed array [indexed]
    }
}

void splitNode(Loc nodeLoc){
    //Create new node
    LnkArr* nodeNew = init_list_empty();
    LnkArr* nodeFirst = nodeLoc.node;
    int i_read;
    int flag = nodeFirst->flag;
    int len = nodeFirst->len;

    // Rewiring the pointers
    nodeNew->nextNode = nodeLoc.nodeNext;
    nodeLoc.node->nextNode = nodeNew;

    // Properting of new node
    nodeNew->flag = 0;
    nodeNew->isSorted = nodeLoc.node->isSorted;
    nodeNew->len = 0;


    // move data
    for(int i= (len/2); i < len ;i++){
        i_read = get_i2read(i, nodeFirst->flag, nodeFirst->len);

        ++(nodeNew->len); //Expand array
        append_arr(nodeNew->arrInx, 
                   nodeFirst->arrInx[i_read], 
                   nodeNew->len);
    }

    //Shift data to left
    if (flag==1){
        int d = get_i2read(len/2, nodeFirst->flag, nodeFirst->len) + 1;

        for(int i=d; i < (len); i++)
            nodeFirst->arrInx[i - d] = nodeFirst->arrInx[i];

        nodeFirst->len = nodeFirst->len - (len-len/2);
    }
    else{
        nodeFirst->len = len/2  ;//34
    }

    // Reorder
    update_orderArr(nodeFirst);
    update_orderArr(nodeNew);


    // Sum of separated lengths should equal to the original.
   // assert(len == (nodeFirst->len + nodeNew->len) );


}


int query(LnkArr* list, int l, int r, int k){
   //Find max min between l , r
    StrEndLoc StrEnd = find_start_end_LA(list, l, r);
    MinMax mx = sortBetween(StrEnd.str, StrEnd.end);

    //Binary search k-least member
    int high = mx.max ;
    int low = mx.min;
    int mid;
    int Kleast;
    int found = 0;

    int ans = low;
    while( high >= low){
        mid = (high+low)/2;
        Kleast = NumItemSmaller(StrEnd, mid);

        if (Kleast >= (k)){
            high = mid - 1;
        }
        else{
            ans = mid;
            low = mid + 1;
        }
    }

    printf("%d", ans);
    return ans;
}

int delete(LnkArr* list, int i){
    Loc iloc = find_LnkArr_ith(list, i);
    int isRemoved = 0;
    assert(iloc.isEnd == 0);
    
    if(iloc.node->len > 1){ // more than 1 element
        remove_LArray(iloc);
    }
    else{
        if (iloc.nodePrev != NULL){
            kill_LArray(iloc);
            ++isRemoved;
        }
        else{
            remove_LArray(iloc);
        }
    }
    return isRemoved;
}

void remove_LArray(Loc nodeLoc){
    LnkArr* node =  nodeLoc.node;
    int flag = node->flag;
    int i_ = getINode(nodeLoc);
    int i_sorted;
    int varMov = node->arrInx[i_]; 
    int* arrSort = node->arrSort;

    //Remove indexed array
    remove_arr(node->arrInx, i_, node->len);

    //Remove sorted array
    if (node->isSorted){
        i_sorted = BinarySearch_MaxSmaller(arrSort, node->len, varMov) + 1;

        //if (arrSort[i_sorted] != varMov)
            //--i_sorted;

       assert(arrSort[i_sorted] == varMov);

        remove_arr(arrSort, i_sorted, node->len);
    }
    else{
        remove_arr(arrSort, i_, node->len); //same operation with indexed array
    }

    --(node->len); // update length by -1
}


void kill_LArray(Loc nodeLoc){
    LnkArr* nodePrev = nodeLoc.nodePrev;
    LnkArr* nodeNext = nodeLoc.nodeNext;
    LnkArr* nodeCurrent = nodeLoc.node;
    //Rewiring
    nodePrev->nextNode = nodeNext;
    //Release memory
    free(nodeCurrent);
}


int reverse(LnkArr** list, int str, int end){
    StrEndLoc StrEnd = find_start_end_LA(*list, str, end);
    Loc nodeStr = StrEnd.str;
    Loc nodeEnd = StrEnd.end;

    int isCrossArr=0;

    
    if (nodeStr.node == nodeEnd.node){ // Same array
        reverseInNodes(nodeStr, nodeEnd);
    }
    else if (nodeStr.i == 0 && nodeEnd.i == (nodeEnd.node->len-1)){ // perfec contain full length
        flipFullNodes(list, nodeStr, nodeEnd);
    }
    else{ // Cross arrays
        reverseSplit(list, &nodeStr, &nodeEnd, str, end);
        isCrossArr=1;
    }
    return isCrossArr;
}

int reverseSplit(LnkArr** list, Loc* nodeStr, Loc* nodeEnd, int Istr, int Iend){

    int TmpArr[subN];
    int LenTmp=0;
    int Split = 0;
    int isHeadMoved=0;

    //Split if data is more than subN/2
    if (nodeStr->node->len > (subN/2)){
        splitNode(*nodeStr);
        Split=1;
    }
    if(nodeEnd->node->len > (subN/2)){
        splitNode(*nodeEnd);
        Split=1;
    }

    //Update 
    if (Split!=0){
        StrEndLoc StrEnd = find_start_end_LA(*list, Istr, Iend);
        *nodeStr = StrEnd.str;
        *nodeEnd = StrEnd.end;
    }

    //Flip intermediate nodes
    if ( ((*nodeStr).nodeNext != (*nodeEnd).node) ){ //confirm there is node between the str end
        isHeadMoved = flipFullNodes_nodes(
                    list, 
                    (*nodeStr).nodeNext,(*nodeStr).node, (*nodeEnd).nodePrev,NULL);
     }
    assert(isHeadMoved == 0);

    //split reverse at Start array and End array
    reversePartLA(*nodeStr, *nodeEnd);

    return isHeadMoved;
}

int reversePartLA(Loc nodeStr, Loc nodeEnd){
    int TmpArr[subN];
    int LenA=0;

    // Change to same direction with flag = 0
    if(nodeStr.node->flag == 1)
        convert_flag(nodeStr.node);

    if(nodeEnd.node->flag ==1 )
        convert_flag(nodeEnd.node);

    //move data from nodeStr to temp (reverse part)
    int* strArr = nodeStr.node->arrInx;
    int* endArr = nodeEnd.node->arrInx;

    int i_str = getINode(nodeStr);
    int i_end = getINode(nodeEnd);

    //move str data to tmp 
    for(int i=i_str; i<nodeStr.node->len; i++){
        TmpArr[LenA] = strArr[i];
        ++LenA;
    }

    //copy end data to str [reverse]
    int i_str2 = i_str;
    for(int i=i_end; i>=0;i--){
        strArr[i_str2] = endArr[i];
        ++i_str2;
    }
    //update Str length
    nodeStr.node->len = i_str2;
    assert(i_str2 < subN);

    //copy str data to end [reverse]
    convert_flag(nodeEnd.node);
    assert(nodeEnd.node->flag == 1);
    i_end = getINode(nodeEnd); //update i_end

    for (int i=0; i<LenA;i++){
        endArr[i_end] = TmpArr[i];
        ++i_end;
     }
     //update End length
     nodeEnd.node->len = i_end;

     //reorder
     update_orderArr(nodeStr.node);
     update_orderArr(nodeEnd.node);
    return i_end;
}

int flipFullNodes(LnkArr** list, Loc nodeStr, Loc nodeEnd ){
    LnkArr* nodeBefore = nodeStr.nodePrev;
    LnkArr* nodeAfter = nodeEnd.nodeNext;
    int moveHead = 0;
    //Reverse intervals: Flip flag and reverse pointers
    LnkArr* nTmp;
    LnkArr* nPrev = nodeEnd.nodeNext; //END
    LnkArr* node = nodeStr.node;

    while(node != nodeEnd.nodeNext){
        //Flip
        node->flag ^= 1; //XOR

        //Rewiring
        nTmp = node->nextNode;
        node->nextNode = nPrev;

        //Move to next node
        nPrev = node;
        node = nTmp;
    }

    if (nodeStr.nodePrev != NULL)
        nodeStr.nodePrev->nextNode = nodeEnd.node; //START
    else { // nodeStr is the head
        //TODO
        *list = nodeEnd.node;//change head 
        moveHead = 1;
    }
    return moveHead;
}

int flipFullNodes_nodes(LnkArr** list, LnkArr* StrNode, LnkArr* StrPrevNode,LnkArr* EndNode, LnkArr* EndNodePrev){
    Loc nodeStr, nodeEnd;

    nodeStr.node = StrNode;
    nodeStr.nodePrev = StrPrevNode;
    nodeStr.nodeNext = StrNode->nextNode;

    nodeEnd.node = EndNode;
    nodeEnd.nodePrev = EndNodePrev;
    nodeEnd.nodeNext = EndNode->nextNode;

    return flipFullNodes(list, nodeStr, nodeEnd);
}

int reverseInNodes(Loc nodeStr, Loc nodeEnd){
    //Same array
    assert(nodeStr.node == nodeEnd.node);
    int iStr = getINode(nodeStr);
    int iEnd = getINode(nodeEnd);
    int flip;

    flip = reverse_arr(nodeStr.node->arrInx, iStr, iEnd);

    assert(iEnd < nodeStr.node->len);
    return flip;
}

void update_orderArr(LnkArr* node){
    memcpy(node->arrSort, 
           node->arrInx, 
           sizeof(int)*node->len);
    //if (node->isSorted == 1){
    quicksort(node->arrSort, 0, node->len-1);
    node->isSorted = 1;
    //}
}

Loc find_LnkArr_ith(LnkArr* headList, int i){
    return find_LnkArr_ith_bounded(headList, NULL, 0, i);
}

Loc find_LnkArr_ith_bounded(LnkArr* startNode, LnkArr* prevNode, int sumLenPrev, int i){
    
    int num_st = sumLenPrev; 
    Loc posI;
    // Location Info
    int i_arr; 
    int isEnd;
    LnkArr* node = startNode;

    posI.nodePrev = prevNode; // No previous array at start

    if (i==1){ // First array  
        assert(prevNode == NULL);
        posI.node = node;
        posI.nodeNext = node->nextNode;
        posI.numCum = num_st;
        posI.i = 0;
        posI.isEnd = 0; // there is no i-1 for i=1
        return posI;
    }

    while (1){
        if ((num_st + node->len) >= i){ // find ith location
            i_arr = i - num_st - 1;
            isEnd = 0;
            break;
        }
        else{
            if (node->nextNode == NULL){ // end of list
                i_arr = node->len - 1; // last element. 
                assert( (node->len + num_st) == (i - 1)); // i is at end
                isEnd = 1; // (i-1) th element
                break;
            }
            num_st += node->len;

            // Move to next node
            posI.nodePrev = node;
            node = node->nextNode;
        }
    }

    posI.node=node;
    posI.nodeNext = node->nextNode;
    posI.i = i_arr;
    posI.isEnd = isEnd;
    posI.numCum = num_st;

    return posI;
}

StrEndLoc find_start_end_LA(LnkArr* headlist, int str, int end){
    assert(str<=end);
    assert(headlist!=NULL);
    Loc nodeStr = find_LnkArr_ith(headlist, str);
    Loc nodeEnd = find_LnkArr_ith_bounded(nodeStr.node, nodeStr.nodePrev, nodeStr.numCum, end);
    StrEndLoc StrEnd;
    StrEnd.str = nodeStr;
    StrEnd.end = nodeEnd;
    return StrEnd;
}

int get_ith_var(LnkArr* headList, int i){
    Loc nodeLoc = find_LnkArr_ith(headList, i);
    int i_ = getINode(nodeLoc);
    return nodeLoc.node->arrInx[i_];
}

int get_i2read(int i, int flag, int length){
    int i_ = (flag==0) ? i : length - 1 - i ;
    return i_;
}

int getINode(Loc iloc){
    return get_i2read(
        iloc.i,
        iloc.node->flag,
        iloc.node->len
    );
}

int getINodeEnd(Loc iloc){
    return get_i2read(
        iloc.node->len-1,
        iloc.node->flag,
        iloc.node->len
    );
}

int getINodeStr(Loc iloc){
    return get_i2read(
        0,
        iloc.node->flag,
        iloc.node->len
    );
}

int convert_flag(LnkArr* node){
    reverse_arr(node->arrInx, 0,node->len-1);
    node->flag ^= 1;
    return node->flag;
}

int sortNode(LnkArr* node){
    int doSort = 0;
    if (node->isSorted == 0){
        quicksort(node->arrSort, 0, node->len-1);
        node->isSorted = 1;
        ++doSort;
    }
    return doSort;   
}

MinMax sortBetween(Loc nodeStr, Loc nodeEnd){
    MinMax mx, mxEnd;

    //Same node
    if(nodeStr.node == nodeEnd.node){
        mx = findMinMaxLA(nodeStr, nodeEnd);
        return mx;
    }

    //Different nodes
    mx = findMinMax(nodeStr.node->arrInx,
                    getINode(nodeStr), 
                    getINodeEnd(nodeStr));
    
    mxEnd = findMinMax(nodeEnd.node->arrInx,
                       getINodeStr(nodeEnd),
                       getINode(nodeEnd));
    
    update_MinMax(&mx, mxEnd.min, mxEnd.max);
    
    //Find Min Max within array
    LnkArr* node = nodeStr.nodeNext;
    int min = node->arrSort[0];
    int max = node->arrSort[node->len - 1];
    while( node != nodeEnd.node){
        //Sort
        sortNode(node);

        //get extremes
        min = node->arrSort[0];
        max = node->arrSort[node->len - 1];

        //Updates
        update_MinMax(&mx, min, max);

        //Move to next node
        node = node->nextNode;
    }
    

    return mx;
}

MinMax findMinMaxLA(Loc nodeStr, Loc nodeEnd){
    assert(nodeStr.node == nodeEnd.node);
    LnkArr* node = nodeStr.node;
    int Istr = getINode(nodeStr);
    int Iend = getINode(nodeEnd);
    MinMax mx = findMinMax(node->arrInx, Istr, Iend);
    return mx;
}

int NumItemSmaller(StrEndLoc StrEnd, int key){
    int numSmaller=0;
    Loc nodeStr = StrEnd.str;
    Loc nodeEnd = StrEnd.end;
    int Istr, Iend;


    if (nodeStr.node == nodeEnd.node){ // Same array; same node
        Istr = getINode(nodeStr);
        Iend = getINode(nodeEnd);
        if( Istr>Iend){
            swap(&Istr, &Iend);
        }
        numSmaller = NumItemSmaller_Screen(nodeStr.node->arrInx,
                              Istr, Iend, key);
        return numSmaller;
    }
    
    /*Linear search for terminals*/
    //Start terminal [i, end]
    Istr = getINode(nodeStr);
    Iend = getINodeEnd(nodeStr);
    numSmaller += NumItemSmaller_Screen(nodeStr.node->arrInx,Istr, Iend, key);

    //End terminal [0, i]
    Istr = getINodeStr(nodeEnd);
    Iend = getINode(nodeEnd);

    numSmaller += NumItemSmaller_Screen(nodeEnd.node->arrInx, Istr, Iend, key);

    /*Binary search*/
    LnkArr* node = nodeStr.nodeNext;

    while(node != nodeEnd.node){
        assert(node->isSorted == 1);
        numSmaller+= NumItemSmaller_Sorted(node->arrSort, 
                                           node->len, 
                                           key) ;
        node = node->nextNode;
    }

    return numSmaller;
}

/*Interface*/
void interface(void){
    LnkArr* list = init_list_empty();

    int n, q; //n: #n initial seq; q: #n of commands
    char cmd[30];
    int val;
    int v0,v1,v2;
    scanf("%d", &n);
    scanf("%d", &q);

    //Initial seq
    for(int i=1; i<=n;i++){
        scanf("%d", &val);
        insert(list, i, val);
    }
    

    // Commands
    for(int i=0;i<q;i++){
        scanf("%s", cmd);
        if (strcmp(cmd, "Delete") == 0){
            scanf("%d", &v0);
            delete(list, v0);
        }
        else if(strcmp(cmd, "Insert") == 0){
            scanf("%d", &v0);// loc
            scanf("%d", &v1);// val
            insert(list, v0, v1);
        }
        else if(strcmp(cmd, "Query") == 0){
            scanf("%d", &v0);// loc
            scanf("%d", &v1);// val
            scanf("%d", &v2);
            query(list, v0, v1, v2);  
            printf("\n");  
        }
        else if(strcmp(cmd, "Reverse") == 0){
            scanf("%d", &v0);// loc
            scanf("%d", &v1);// val
            reverse(&list, v0, v1);
        }
    }

    kill_list(list);
}

void interfaceDebuggingFile(char* filename){
    FILE *fp;
    fp = fopen(filename, "r");  

    LnkArr* list = init_list_empty();
    array listArr = init_array();

    int n, q; //n: #n initial seq; q: #n of commands
    char cmd[30];
    int val;
    int v0,v1,v2;
    int qu=0;
    int quList;
    int quArr;
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &q);

    //Initial seq
    for(int i=1; i<=n;i++){
        fscanf(fp,"%d", &val);
        insert_array(&listArr, i, val);
        insert(list, i, val);
    }
    compare_LA_array(&listArr, list);
    

    // Commands
    for(int i=1;i<=q;i++){
        fscanf(fp,"%s", cmd);
        if (strcmp(cmd, "Delete") == 0){
            fscanf(fp,"%d", &v0);
            delete_array(&listArr, v0);
            delete(list, v0);
        }
        else if(strcmp(cmd, "Insert") == 0){
            fscanf(fp, "%d", &v0);// loc
            fscanf(fp, "%d", &v1);// val
            insert_array(&listArr, v0, v1);
            insert(list, v0, v1);
        }
        else if(strcmp(cmd, "Query") == 0){
            fscanf(fp, "%d", &v0);// loc
            fscanf(fp, "%d", &v1);// val
            fscanf(fp, "%d", &v2);
            ++qu;
            

            compare_LA_array(&listArr, list);
            //compare_InxOrder(list);

            StrEndLoc StrEnd = find_start_end_LA(list, v0, v1);

            assert(StrEnd.str.node->arrInx[getINode(StrEnd.str)] == listArr.arr[v0 - 1]);
            assert(StrEnd.end.node->arrInx[getINode(StrEnd.end)] == listArr.arr[v1 - 1]);

            quList =  query(list, v0, v1, v2);  


            compare_LA_array(&listArr, list);

            quArr = query_array(&listArr, v0,v1,v2);
            //compare_LA_array(&listArr, list);
            //assert(quList == quArr);
            printf("\n");  
        }
        else if(strcmp(cmd, "Reverse") == 0){
            fscanf(fp, "%d", &v0);// loc
            fscanf(fp, "%d", &v1);// val
            reverse_array(&listArr, v0, v1);
            reverse(&list, v0, v1);
        }
        else {
            //assert(1==0);
        }

        compare_LA_array(&listArr, list);
    }

    kill_list(list);
}

int compare_LA_array(array* arr, LnkArr* list){
    int diff = 0;
    array diffIs = init_array();
    for (int i=0;i<(arr->len);i++){
        if (arr->arr[i] != get_ith_var(list, i+1)){
            //printf("Real: %d, List: %d at %d", arr->arr[i], get_ith_var(list, i+1), i+1);
            ++diff;
            
            diffIs.arr[diffIs.len] = i;
            ++diffIs.len;
            
        }
    }
    if (diff>0){
        printf("Difference: %d", diff);
    }
   // assert(diff==0);
   return 0;
}

int compare_InxOrder(LnkArr*list){

    LnkArr* node = init_list_empty();

    while (list!=NULL){

        if (list->isSorted == 1){
            memcpy(node->arrInx, list->arrInx, sizeof(int)*list->len);
            quicksort(node->arrInx, 0, list->len-1);

            for(int i=0; i<list->len;i++){
                //assert(node->arrInx[i] == list->arrSort[i]);
                }
        }
        else{
            for(int i=0; i<list->len;i++){
                //assert(list->arrInx[i] == list->arrSort[i]);
                }
        }

        list = list->nextNode;
    }
    
    free(node);

    return 0;
}