#include "list.h"


//Array of operations
int (*POPFUNC[3])(packData, int) = {PopFirstPack, PopLastPack, PopMaxPack};
static const int (*PEEKFUNC[3])(packData, int) = {PeekFirstPack, PeekLastPack, PeekMaxPack};


int solve(packData pd, query* qs, int n_query, int* pkOrders){
    int nPk = pd.N_Package;
    int targetPK = 0;
    int IDpop;
    pack* PKs = pd.packs;
    pack* curPK = &PKs[pkOrders[targetPK]];

    for(int i=0;i<n_query;i++){
        /**Do Operation**/
        if(qs[i].opID == PUSH){
            PushPack(pd, qs[i].arg[1], qs[i].arg[0]);//[lineID, packID]
        }
        else{//qs[i].opID == MERGE){
            MergeLines(pd, qs[i].arg[1], qs[i].arg[0]);//[Dst, Src]
        }

        /**Try Pop**/
        while(curPK->popfunc != NULL && targetPK < nPk){
            //Pop
            IDpop = (*(curPK->popfunc))(pd, curPK->line);
            assert(pkOrders[targetPK]==IDpop);
            //Move next
            ++targetPK;
            curPK = &PKs[pkOrders[targetPK]];
        }

    }

    if (targetPK == nPk)
        return 1;
    else
        return 0;
}

packData init_packData(int n, int l){
    packData pd;

    pd.N_Lines = l;
    pd.N_Package = n;

    //Create NULL pack
    pack pk = getNullPack();
    //Create Null prodLine;
    prodLine pl = getNullProdLine();

    //Memory
    size_t sizePacks = (pd.N_Package + 1)*sizeof(pack); //[0,1,n]
    size_t sizeLines = pd.N_Lines*sizeof(prodLine);  //[0,l-1]
    size_t sizeNodes = (pd.N_Package+1)*sizeof(hnode);

    // Allocate 
    pd.packs = (pack*)malloc(sizePacks);
    pd.lines = (prodLine*)malloc(sizeLines);
    pd.nodes = (hnode*)malloc(sizeNodes);

    // initialize
    for(int i=0;i<=pd.N_Package;i++){
        pd.packs[i] = pk;
        pd.packs[i].ID = i;
    }

    for(int i=0;i<pd.N_Lines;i++)
        pd.lines[i] = pl;


    return pd;
}

void kill_packData(packData pd){
    //kill heaps
    free(pd.nodes);
    
    free(pd.lines);
    free(pd.packs);
}

// Data management
void PushPack(packData pd, int iLine, int iPack){
    pack* pk = &pd.packs[iPack];
    assert(pk->avail == 0);

    //Register new data
    pk->avail = 1;

    //Clear first, last, max
    _clearGetMethod(pd, iLine);

    //Insertion
    _insertHeap(pd, iLine, iPack);
    _insertlist(pd, iLine, iPack);


    //Reset first, last, max
    _setGetMethod(pd, iLine);
}

void MergeLines(packData pd, int iDst, int iSrc){
    assert(pd.lines[iSrc].avail==1);
    assert(pd.lines[iDst].avail==1);

    //Clear first, last, max
    _clearGetMethod(pd, iSrc);
    _clearGetMethod(pd, iDst);


    _mergeHeap(pd, iDst, iSrc);
    _mergelist(pd, iDst, iSrc);
    pd.lines[iSrc].avail = 0;

    //Reset first, last, max
    _setGetMethod(pd, iSrc);
    _setGetMethod(pd, iDst);
}


// Pop
int PopFirstPack(packData pd, int iLine){
    return _PopOperation(pd, iLine, PeekFirstPack, _popFirst);
}

int PopLastPack(packData pd, int iLine){
    return _PopOperation(pd, iLine, PeekLastPack, _popLast);
}

int PopMaxPack(packData pd, int iLine){
    return _PopOperation(pd, iLine, PeekMaxPack, _popMaxHeap);
}

int _PopOperation(packData pd, int iLine, int (*PeekFunc)(packData,int), int (*PopFunc)(packData,int)){
    int ID = (*PeekFunc)(pd, iLine);
    int ID_POP = (*PopFunc)(pd, iLine);
    assert(ID == ID_POP);
    //Mark popped
    _removePack(&pd.packs[ID]);
    //Clear old first/last/max
    _clearGetMethod(pd,iLine);
    //set new first/last/max
    _setGetMethod(pd, iLine);
    return ID_POP;
}

// Peek Data

int PeekFirstPack(packData pd, int i){
    if(pd.lines[i].list.first != NULL){
        while(pd.lines[i].list.first->avail == 0 ){
            //Remove unavailable item
            _popFirst(pd, i);
            if(pd.lines[i].list.first == NULL)
                break;
        }
    }


    //Return
    if(pd.lines[i].list.first == NULL)
        return EMPTY;
    else{ 
        //Update Get method
        pd.lines[i].list.first->popfunc = PopFirstPack;
        return pd.lines[i].list.first->ID;
    }
}

int PeekLastPack(packData pd, int i){
    if(pd.lines[i].list.first != NULL){
        while(pd.lines[i].list.last->avail == 0 ){
            _popLast(pd, i);
            if(pd.lines[i].list.first == NULL)
                break;
        }
    }


    //Return
    if(pd.lines[i].list.last == NULL)
        return EMPTY;
    else{
        //Update Get method
        pd.lines[i].list.last->popfunc = PopLastPack;
        return pd.lines[i].list.last->ID;
    }
}

int PeekMaxPack(packData pd, int i){
    if(pd.lines[i].heap != NULL){
        while(pd.lines[i].heap->key->avail == 0 ){
            _popMaxHeap(pd, i);
            if (pd.lines[i].heap == NULL)
                break;
        }
    }

    //Return
    if (pd.lines[i].heap == NULL){
        return EMPTY;
    }
    else{
        pd.lines[i].heap->key->popfunc = PopMaxPack;
        return pd.lines[i].heap->key->ID;
    }
}


void _clearGetMethod(packData pd, int iLine){
    int ID=0;
    for(int i=0;i<3;i++){
        ID = (*PEEKFUNC[i])(pd, iLine);
        if (ID != EMPTY)
            _removePackGetMethod(&pd.packs[ID]);
    }    
}

void _setGetMethod(packData pd, int iLine){
    int ID=0;
    for(int i=0;i<3;i++){
        ID = (*PEEKFUNC[i])(pd, iLine);
        if (ID != EMPTY){
            pd.packs[ID].popfunc = POPFUNC[i];
            pd.packs[ID].line = iLine;
        }
    }    
}



//Heap

void _insertHeap(packData pd, int iLine, int iPack){
    pack* pk = &pd.packs[iPack];
    hnode* root = pd.lines[iLine].heap;
    hnode* newnode = createNode(pk, &pd.nodes[pk->ID]);

    if (root!=NULL)
        pd.lines[iLine].heap = _insertHeapLeftist(root, pk, newnode);
    else{
        pd.lines[iLine].heap = newnode;
    }

}


int _popMaxHeap(packData pd, int i){
    hnode* root = pd.lines[i].heap;
    int val=0;
    assert(root != NULL);
    
    pd.lines[i].heap = _popMaxHeapLeftist(root, &val);
    return val;
}

void _mergeHeap(packData pd, int iDst, int iSrc){
    hnode* A = pd.lines[iDst].heap;
    hnode* B = pd.lines[iSrc].heap;

    if (B == NULL){ //Null Source
        return;
    }
    else if (A == NULL){ // Null Destination
        pd.lines[iDst].heap = B;
        pd.lines[iSrc].heap = NULL;
        return;
    }
    else{
        pd.lines[iDst].heap = _mergeHeapLeftist(A, B);
    }

 
    // Empty source
    pd.lines[iSrc].heap = NULL;
}



hnode* _mergeHeapLeftist(hnode* A,hnode* B){
    if (A==NULL){
        return B;
    }
    else if(B==NULL){
        return A;
    }

    if (A->key->ID < B->key->ID ){ //Max Heap
        swaphNode(&A, &B);
    }

    A->leaves[1] = _mergeHeapLeftist(A->leaves[1], B);
    if (_getDistLeftist(A->leaves[1]) > _getDistLeftist(A->leaves[0])){
        swaphNode(&(A->leaves[0]), &(A->leaves[1]));
    }
    if (A->leaves[1] == NULL){
        A->dist = 0;
    }
    else{
        A->dist = 1 + _getDistLeftist(A->leaves[1]);
    }
    return A;
}

hnode* _popMaxHeapLeftist(hnode* root, int* val){
    hnode* delNode = root;
    *val = root->key->ID;

    root = _mergeHeapLeftist(root->leaves[0], root->leaves[1]);

    delNode->leaves[0] = NULL;
    delNode->leaves[1] = NULL;
    return root;
}

hnode* _insertHeapLeftist(hnode* root, pack* pk, hnode* newNode){

    //Make heap with one element
    root = _mergeHeapLeftist(root, newNode);

    return root;
}

int _getDistLeftist(hnode* node){
    if (node==NULL){
        return -1;
    }
    else{
        return node->dist;
    }
}

void swaphNode(hnode** A, hnode** B){
    hnode* tmp = *A;
    *A = *B;
    *B = tmp;
}

hnode* createNode(pack* pk, hnode* node){
    hnode* newNode = node;
    newNode->key = pk;
    newNode->leaves[0]=NULL;
    newNode->leaves[1]=NULL;
    newNode->dist = 0;
    return newNode;
}



void _killHeap(hnode* root){
    if (root == NULL)
        return ;
        
    _killHeap(root->leaves[0]);
    _killHeap(root->leaves[1]);

    free(root);
}



//Linked list 

void _insertlist(packData pd, int iLine, int iPack){
    List* list = &pd.lines[iLine].list;
    pack* pk = &pd.packs[iPack];

    //Check pk is new
    assert(pk->next==NULL);
    assert(pk->prev==NULL);

    if (list->first == NULL){ // Init
        assert(list->last == NULL);
        list->first = pk;
        list->last = pk;
    }
    else{ // Continue
        assert(list->last->next == NULL);
        list->last->next = pk;
        pk->prev = list->last;
        list->last = pk;
    }
}

void _mergelist(packData pd, int iDst, int iSrc){

    List* listDst = &pd.lines[iDst].list;
    List* listSrc = &pd.lines[iSrc].list;

    if (listSrc->first==NULL){ //src is null
        //Do nothing
    }
    else if (listDst->first == NULL){ //dst is null
        listDst->first = listSrc->first;
        listDst->last = listSrc->last;
    }
    else{
    assert(listSrc->last != NULL);
    assert(listDst->last != NULL);

    //wiring dst end
    listDst->last->next = listSrc->first;
    listSrc->first->prev = listDst->last;

    //update dst end
    listDst->last = listSrc->last;
    
    //Clear source
    listSrc->first = NULL;
    listSrc->last = NULL;
    
    }
}


int _popFirst(packData pd, int iLine){
    List* list = &pd.lines[iLine].list;
    assert(list->first!=NULL);
    int val = list->first->ID;
    list->first->avail = 0; // update availability

    if(list->first == list->last){ //turn to null
        list->first = NULL;
        list->last = NULL;
        
    }
    else{
    //Rewiring
    list->first = list->first->next; // move start
    list->first->prev = NULL; // link start.prev to NULL

    if(list->first == NULL) //turn to null
        list->last = list->first;

    }

    return val;
}

int _popLast(packData pd, int iLine){
    List* list = &pd.lines[iLine].list;
    assert(list->first!=NULL);
    int val = list->last->ID;
    list->last->avail = 0; // update availability

    if(list->first == list->last){ //turn to null
        list->first = NULL;
        list->last = NULL; 
    }

    else{
        //Rewiring
        list->last = list->last->prev; // move end
        list->last->next = NULL; // link end.next to NULL

        if(list->last == NULL) //turn to null
            list->first = list->last;
    }

    return val;
}

//Remove Item
void _removePack(pack* pk){
    pk->avail = 0;
    pk->line = EMPTY;
    _removePackGetMethod(pk);
}

void _removePackGetMethod(pack* pk){
    pk->popfunc = NULL;
}

//Struct

pack getNullPack(void){
    pack pk;
    pk.avail = 0;
    pk.prev = NULL;
    pk.next = NULL;
    pk.ID = INT_MIN;
    pk.popfunc = NULL;
    pk.line = EMPTY;
    return pk;
}

prodLine getNullProdLine(void){
    prodLine pl;
    pl.heap = NULL;
    pl.avail = 1;
    pl.list.first = NULL;
    pl.list.last = NULL;
    return pl;
}


//Interface
int _getopID(char* op){
    if(strcmp(op, "push")==0)
        return PUSH;
    else if(strcmp(op, "merge")==0)
        return MERGE;
    else 
        return -1;
}

void _getOperation(query* Op){
    char opStr[MAX_OP_CHAR];
    scanf("%s",opStr);
    scanf("%d", &Op->arg[0]);
    scanf("%d", &Op->arg[1]);
    Op->opID = _getopID(opStr);
}

void _printRes(int sol){
    if (sol == 1)
        printf("possible");
    else
        printf("impossible");
}

void interface(void){
    int T; // # of test cases
    int nP; // # of packages
    int nQ; // # of queries
    int nL; // # of Lines
    int sol=0;
    query* Ops = (query*)malloc(MAX_Q * sizeof(query));
    int* pkOrders = (int*)malloc(MAX_N*sizeof(int));

    scanf("%d", &T);

    for(int t=0;t<T;t++){

        // Problem Info
        scanf("%d", &nP);
        scanf("%d", &nQ);
        scanf("%d", &nL);

        //Initiation
        packData pd = init_packData(nP, nL);

        //Operations
        for(int i=0;i<nQ;i++)
            _getOperation(&Ops[i]);

        //Save package order
        for(int i=0;i<nP;i++)
            scanf("%d", &pkOrders[i]);

        //Solve
        sol = solve(pd, Ops, nQ, pkOrders);
        _printRes(sol);

        if(t!=T-1){
            printf("\n");
        }

        kill_packData(pd);
    }

    //Free
    free(Ops);
    free(pkOrders);
}