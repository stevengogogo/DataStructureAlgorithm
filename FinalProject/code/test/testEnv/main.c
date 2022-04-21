#include "api.h"
//#include "api.h"
#ifndef EXPRESSIONMATCH_H
#define EXPRESSIONMATCH_H
/**
 * @file utils.h
 * @author Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief General Utilities for C language
 * @version 0.1
 * @date 2021-03-08
 * @note 
 * Reference
 * 1. Universal Stack is modified from: https://github.com/igniting/generic-stack
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h> // tolower
#define INIT_NUM_ARRAY_ELEMENT 10
#define EMTY_QUE_SIG -121242
#define MAX_N_MAIL 11000
typedef unsigned char byte;

/************Math************/

/**
 * @brief Get arg max
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int argmax(int a,int b);

/**
 * Check `val` is in [lower,upper]
 */
bool inDomainInt(int val, int lower, int upper);

/************Tokenize************/

/**
 * @brief Pop token from message. 
 * 
 * @param token Buffer string. Token will be saved here. `\0` if no token left
 * @param message main text
 * @param iStr reading head
 * @return int updated reading head `iStr`. -1: end of string
 */
int popToken(char message[], char token[], int iStr);

/**
 * @brief Judge a character belong to regular expression or not
 * @note Regular expression: %[a-zA-Z0-9]
 * @return true 
 * @return false 
 */
bool isRegularExpr_ASCII(int);
bool isNumber_ASCII(int);
bool isUpperCase_ASCII(int);
bool isLowerCase_ASCII(int);
/**
 * @brief [0-9] -> [0-9]; [a-z] -> [10-35]; otherwise: ASCII
 * @param c 
 * @return int 
 */
int char2num(char c);

/************Dynamic Array (Int) Stack**************/
//dynamic array
typedef struct{
    int len;
    int size;
    int* i;
} dymArr;

//init and kill
void init_dymArr(dymArr*, int size);
void kill_dymArr(dymArr*);
void resize_dymArr(dymArr*, int new_max_size);

//clear
void clear_Arr(dymArr*);

//append
/**Append at last*/
void append_dymArr(dymArr*, int val);
/** Get the item of arr[i]*/
int get_item(dymArr, int i);
/** Get the last item
 * @return last element. If no item left, return `EMTY_QUE_SIG`
*/
int pop_item(dymArr*);

/*************Queue************/
typedef struct{
    dymArr arr;
    int head;
    int tail;
} que;

que init_que(int size);
void kill_que(que*);
void enque(que*, int val);
int deque(que*);
int peek_que(que*);

/************Generic Dynamic Array************/

/** Generic copy*/
void copy_item_array(void* dstArr, int locDst,void* srcArr, int locSrc, size_t size);

/** Universal dynamic Array*/
typedef struct uArray{
    int len;
    size_t eleSize;
    byte* memory;
    int num_maxEle;
} uArray;

void init_uArray(uArray* arr, size_t eleSize);
int len_uArray(uArray* arr);
void get_uArray(uArray* arr, int i,void* item);
void set_uArray(uArray* arr, int i,void* item);
void remove_uArray(uArray* arr, int i);
void insert_uArray(uArray* arr, int i,void* item);
void append_uArray(uArray* arr, void* item);
void update_size_uArray(uArray* arr, int new_max_item);
void kill_uArray(uArray* arr);

/*Sorting*/
/** * QuickSort to increasing order. Reference: This function is modified from https://openhome.cc/Gossip/AlgorithmGossip/QuickSort3.htm#C */
void quicksort(int arr[], int left, int right);

/** * Combine fragments. This function is modifed from: https://openhome.cc/Gossip/AlgorithmGossip/QuickSort3.htm#C */
int partition(int number[], int left, int right);

/** * Switch the value store in `x` and `y`. */
void swap(int* x, int* y);

/*Matrix*/
typedef struct Matrix{
    int* m;
    int nrow;
    int ncol;
} Matrix;

void init_Matrix(Matrix* M, int nrow, int ncol);
void kill_Matrix(Matrix* M);
void set_Matrix(Matrix* M, int r, int c, int val);
int get_Matrix(Matrix*M, int r, int c);

#endif
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef GROUPANALYSIS_H
#define GROUPANALYSIS_H
//#include "api.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define SIZE 1000001

typedef struct Node{
	char* name;
	int parentIdx;
	int size;
}node;
/**/
static node* makeset(){

	node* arr = (node*)malloc(10*SIZE*sizeof(node));

	return arr;
}

static int hash(char word[]){
	int i = 0;
	int RK = 0;
	while(word[i]!='\0'){
		RK = (62*RK + (int)word[i])%SIZE;
		i++;
	}
	return abs(RK)%SIZE;
}

static int hash1(char word[]){
	return (int)word[0]*(int)word[0]+1;
}

static int findIdx(node*set, char word[]){
	int hashed = hash(word);
	int step = hash1(word);
	while(set[hashed].name){
		if(strcmp(set[hashed].name, word)!=0){
			hashed = (hashed+step)%SIZE;

		}else return hashed;
	}
	return hashed;
}

static int inputTable(node* set, char word[]){
	int hashed = findIdx(set, word);
	if(!set[hashed].name){
		set[hashed].name = word;
		set[hashed].parentIdx = hashed;
		set[hashed].size = 1;
	}

	return hashed;
}

static int findset(node *set, int hashed){
	if(set[hashed].parentIdx!=hashed){
		set[hashed].parentIdx = findset(set,set[hashed].parentIdx);
	}
	return set[hashed].parentIdx;
}

static void link_GA(node *set, int nodex, int nodey ,int *count, int *max){
	if(set[nodex].size>set[nodey].size){
		set[nodey].parentIdx = nodex;
		set[nodex].size += set[nodey].size;
		if(set[nodey].size>=2){
			*count-=1;
		}
		set[nodey].size = 0;
		if(set[nodex].size>*max){
			*max = set[nodex].size;
		}
	}else{
		set[nodex].parentIdx = nodey;
		if(set[nodex].size==set[nodey].size&&set[nodex].size==1){
			*count += 1;
		}
		set[nodey].size += set[nodex].size;
		if(set[nodex].size>=2){
			*count -= 1;
		}
		set[nodex].size = 0;
		if(set[nodey].size>*max){
			*max = set[nodey].size;
		}
	}
}

static void setunion(node* set, char word1[],char word2[], int* count, int* max){
	int nodex = inputTable(set, word1);
	int nodey = inputTable(set, word2);
	int idxx = findset(set, nodex);
	int idxy = findset(set, nodey);
	if(idxx!=idxy){
		link_GA(set, idxx, idxy, count, max);
	}
}

static void answer_GroupAnalysis(int mid[], int len, mail* mails, int* list, int* nlist){
	node* arr = makeset();
	int count = 0;
	int max = 0;

	for(int i = 0; i < len; i++){
		setunion(arr,mails[mid[i]].from, mails[mid[i]].to, &count, &max);
	}
 
  //ANS
  list[0] = count;
  list[1] = max;
  *nlist = 2;

  free(arr);

}

#endif
#define SIZE 1000001

typedef struct Stack{
	int top;
	char* array;
}stack;

static void push(stack* stack1, char input){
	stack1 -> array[++stack1->top] = input;
}

static char pop(stack* stack1){
	return stack1 -> array[stack1->top--];
}

static char peek(stack* stack1){
	return stack1 -> array[stack1->top];
}

static int stackEmpty(stack* stack1){
	if(stack1->top==-1) return 1;
	else return 0;
}

static int OpPriority(char oper){
	switch(oper){
		case('!'):
			return 3;
		case('&'):
			return 2;
		case('|'):
			return 1;
		default:
			return 0;
	};
}

static int isOp(char op){
	if(op=='!'|op=='&'|op=='|'|op=='('|op==')'){
		return 1;
	}else{
		return 0;
	}
}

static void inputHashTable(char** hashTable,char content[]){
	int istr=0;
  	char token[100];
    while(istr!=-1){
		  istr = popToken(content, token, istr);
		  int hashed = hash(token);
		  int step = hash1(token);
		  while(hashTable[hashed]){
			  if(strcmp(token, hashTable[hashed])!=0){
				  hashed+=step;
				  hashed = hashed%SIZE;
			  }else{
				  break;
			  }
		}
		char* input=(char*)malloc(100*sizeof(char));
		strcpy(input, token);
		hashTable[hashed] = input;
		// printf("%d %s\n", hashed, hashTable[hashed]);
	}
}

static char findToken(char** hashTable, char word[]){
	int hashed = hash(word);
	int step = hash1(word);
	while(hashTable[hashed]){
		if(strcmp(hashTable[hashed],word)==0){
			return '1';
		}
		hashed += step;
	}
	return '0';
}

static char* expressionPostfix(char expression[], stack* main_stack, char** hashTable){
	static char output[2*2048];
	char* token = (char*)malloc(100*sizeof(char));
	int i = 0, k = 0, j = 0;;

	while(expression[i]!='\0'){
		j=0;
		token[0]='\0';
		while(!isOp(expression[i])){
			token[j++] = expression[i++];
		}
		token[j] = '\0';
		if(token[0]!='\0') output[k++] = findToken(hashTable, token);
		if(expression[i]=='('){
			push(main_stack,'(');
		}else if(expression[i]==')'){
			while(peek(main_stack)!='('){
				output[k] = pop(main_stack);
				k++;
			}
			pop(main_stack);
		}else{
			while(stackEmpty(main_stack)==0&&OpPriority(expression[i])<=OpPriority(peek(main_stack))){
				output[k++] = pop(main_stack);
			}
			push(main_stack, expression[i]);
		}
		
		i++;
	}

	while(stackEmpty(main_stack)==0){
		output[k++]=pop(main_stack);
	}
	output[k] = '\0';
	return output;
	
}

static int postfixToValue(char postfix[], stack* stack1){
	int i = 0, value = 0, num1=0, num2=0;
	while(postfix[i]){
		if(!isOp(postfix[i])) push(stack1,postfix[i]);
		else if(postfix[i]=='!'){
			
			push(stack1,!(pop(stack1)-'0')+'0');
		}
		else if(postfix[i]=='&'){
			num1 = pop(stack1)-'0';
			num2 = pop(stack1)-'0';
			push(stack1,num1&num2+'0');
		}else if(postfix[i]=='|'){
			num1 = pop(stack1)-'0';
			num2 = pop(stack1)-'0';
			push(stack1,num1|num2+'0');
		}
		i++;
	}
	value = pop(stack1)-'0';
	return value;
}

static int answer_ExpressionMatch(char expression[], mail* mails, int* list, int *nlist){
	stack* main_stack = (stack*)malloc(sizeof(stack));
	main_stack->top = -1;
	main_stack->array = (char*)malloc(sizeof(char)*2048);
	int k = 0, i = 0;
	// while(mails[i]){
	// 	char** hashTable = (char**)malloc(10*SIZE*sizeof(char*));
	// 	char* input = (char*)malloc(sizeof(char)*101000);
	// 	strcat(input, mails[i].subject);
	// 	strcat(input, mails[i].content);
	// 	inputHashTable(hashTable, input);
	// 	char* output = expressionPostfix(expression, main_stack, hashTable);
	// 	if(postfixToValue(output, main_stack)==1) list[k++] = i;
	// 	free(hashTable);
	// 	free(input);
	// }
	*nlist = k;
	free(main_stack);
}

#endif
/**
 * @file FindSimilar.h
 * @author Steven Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief Group Analysis. Use Jaccob's similarity with hash table to identify similar strings.
 * @version 0.1
 * @date 2021-06-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FINDSIMILAR_H
#define FINDSIMILAR_H
//#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

/**********Constant Variable***********/
#define Q_RABIN 7388607
#define D_RABIN 36
#define TOKEN_STRING_LENGTH 4000
#define ULONG  long
#define UINT  int
#define USHORT unsigned short
#define ushort unsigned short

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
//#include "api.h"

typedef struct Matrix_ushort {
    ushort** m;
    ushort* len;
    int nrow;
    int ncol;
} Matrix_ushort;

void init_Matrix_ushort(Matrix_ushort* M, int nrow, int ncol);
void kill_Matrix_ushort(Matrix_ushort* M);

typedef struct infoFS{
    Matrix_ushort hstack;
    double* num_unique;
    double* SimList;
} infoFs;

void init_FS(infoFs* info);
void kill_FS(infoFs* info);

/** Return location*/
int popTokenHash(char message[], char token[], int iStr, int* Hash);
void append_mHash(infoFs* info,mail* mails, int ID);

void proc_FS(infoFs* info, mail* mails, int n_mail);

int Hash_RK(char s[]);

void answer_FS(infoFs*info, mail* mails, int ID, int n_mail, double threshold, int* list, int* nlist);
void register_hash(infoFs* info, int ID, int hash);

#endif

#include <stdio.h>
#include <time.h>

/*
static void get_mails(char* filename, mail** mails, int* num_mail){
    FILE* fp;
    size_t len;
    ssize_t read;
    //Mail info
    int id;
    int maxnum = 1000000;
    char* line = (char *) malloc(maxnum);
    char* from= (char *) malloc(maxnum);
    char* subject= (char *) malloc(maxnum);
    char* idstr= (char *) malloc(maxnum);
    char* content= (char *) malloc(maxnum);
    char* to= (char *) malloc(maxnum);
    size_t buffer=32;
    size_t chr;
    

    fp = fopen(filename, "r");
    if (fp == NULL)
        printf("File not found");

    chr = getline(&idstr,&buffer,fp);
    sscanf(idstr, "%d", num_mail);
    *mails = (mail*)malloc(*num_mail*sizeof(mail));
    
    for(int i=0;i<*num_mail;i++){
       
        chr = getline(&line,&buffer,fp);
        chr = getline(&idstr,&buffer,fp);
        chr = getline(&from,&buffer,fp);
        chr = getline(&content,&buffer,fp);
        chr = getline(&subject,&buffer,fp);
        chr = getline(&to,&buffer,fp);

        sscanf(idstr, "%d", &id);
        //Check content
        //Copy mail information
        (*mails)[i].id = id;
        strcpy((*mails)[i].subject, subject);
        strcpy((*mails)[i].content, content);
        strcpy((*mails)[i].from, from);
        strcpy((*mails)[i].to, to);
    }

    fclose(fp);
    free(line);
    free(idstr);
    free(content);
    free(subject);
    free(from);
    free(to);
}
int main(){
    
    char* hashmap[Q_RABIN];
    for(int i=0;i<Q_RABIN;i++){
        hashmap[i] = (char*)malloc(1000*sizeof(char));
    }

    char token6286[10000] = "a,and,antbird,antbirds,are,backed,bird,bolivia,brazil,colombia,ecuador,family,forests,found,french,guiana,guyana,habitats,http,hylophylax,i,in,is,it,its,lowland,moist,naevia,naevius,natural,of,on,or,org,paragraph,peru,read,species,spot,subtropical,suriname,swamps,thamnophilidae,the,tropical,venezuela,wikipedia\0";

    char token676[10000] = "a,actually,adrift,after,agree,all,also,alternate,an,and,announces,appear,are,around,arrested,as,ashore,at,battling,be,beak,beak,because,been,being,black,book,buccaneers,buried,bursts,but,by,called,can,can,captain,captures,caribbean,cartoon,celebrate,century,chest,comic,contains,counterfeit,crew,dated,dead,decoy,directly,discussion,disguises,disney,donald,down,drop,duck,eating,echo,eight,end,endings,ends,england,eyes,film,find,finds,first,fish,for,found,from,game,gap,get,getting,geysers,ghost,ghosts,gloom,gold,good,goofy,got,guys,had,has,have,haven,he,heading,headline,heard,hearted,help,henry,hidden,hiding,him,himself,his,http,hunters,i,if,in,interludes,is,island,it,just,later,lease,leg,lifted,location,long,loot,losing,lost,man,map,men,mickey,morgan,morgan,mouse,named,new,newspaper,night,no,not,nutty,obtain,of,off,offers,old,on,one,org,over,overhears,owners,paragraph,parrot,passing,peg,persuades,pete,pieces,pirate,pirates,place,placed,plants,pointer,production,quicksand,raft,read,real,rear,released,remembered,rescue,returning,reveal,ride,sea,series,sets,share,ship,skunk,slapstick,small,so,stormy,story,take,taking,tales,tattoo,tattooed,tavern,tell,that,the,their,them,there,they,this,three,tiny,to,trapped,treasure,treasure,trio,tropical,true,trying,two,unreleased,version,very,village,visited,was,wash,were,what,when,where,which,who,whom,wikipedia,with,woman,would,yellow\0";

    char tokenInter[100000] = "a,actually,adrift,after,agree,all,also,alternate,an,and,announces,antbird,antbirds,appear,are,around,arrested,as,ashore,at,backed,battling,be,beak,because,been,being,bird,black,bolivia,book,brazil,buccaneers,buried,bursts,but,by,called,can,captain,captures,caribbean,cartoon,celebrate,century,chest,colombia,comic,contains,counterfeit,crew,dated,dead,decoy,directly,discussion,disguises,disney,donald,down,drop,duck,eating,echo,ecuador,eight,end,endings,ends,england,eyes,family,film,find,finds,first,fish,for,forests,found,french,from,game,gap,get,getting,geysers,ghost,ghosts,gloom,gold,good,goofy,got,guiana,guyana,guys,habitats,had,has,have,haven,he,heading,headline,heard,hearted,help,henry,hidden,hiding,him,himself,his,http,hunters,hylophylax,i,if,in,interludes,is,island,it,its,just,later,lease,leg,lifted,location,long,loot,losing,lost,lowland,man,map,men,mickey,moist,morgan,mouse,naevia,naevius,named,natural,new,newspaper,night,no,not,nutty,obtain,of,off,offers,old,on,one,or,org,over,overhears,owners,paragraph,parrot,passing,peg,persuades,peru,pete,pieces,pirate,pirates,place,placed,plants,pointer,production,quicksand,raft,read,real,rear,released,remembered,rescue,returning,reveal,ride,sea,series,sets,share,ship,skunk,slapstick,small,so,species,spot,stormy,story,subtropical,suriname,swamps,take,taking,tales,tattoo,tattooed,tavern,tell,thamnophilidae,that,the,their,them,there,they,this,three,tiny,to,trapped,treasure,trio,tropical,true,trying,two,unreleased,venezuela,version,very,village,visited,was,wash,were,what,when,where,which,who,whom,wikipedia,with,woman,would,yellow\0";


    int iStr = 0;
    int iNxt;
    int hash;
    char tokenB[10000];
    while(1){
        iNxt = popTokenHash(tokenInter, tokenB, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        if(strncmp(hashmap[hash], tokenB, strlen(tokenB)) != 0){
            printf("Spurious Hit: %s / %s with ID=%d", hashmap[hash], tokenB, hash);
        };
        strncpy(hashmap[hash], tokenB, strlen(tokenB)+1);
    }
}
*/

int main(void) {
    // Var: Api
    int n_mails, n_queries;
    mail *mails;
    query *queries;

    //Var: Find Similar
    int* list = (int*)malloc(MAX_N_MAIL*sizeof(int));
    int nlist;
    double threshold;

    int mid;
    infoFs infs;

    //Initiation

    //FS//
	api.init(&n_mails, &n_queries, &mails, &queries);   
    init_FS(&infs);

    //Answer
	for(int i = 0; i < n_queries; i++){

		//Find Similar
        if (queries[i].type == find_similar){
            //data
            mid = queries[i].data.find_similar_data.mid;
            threshold = queries[i].data.find_similar_data.threshold;

            //process

            answer_FS(&infs, mails, mid,n_mails, threshold, list, &nlist);

            //answer
            //if(queries[i].data.find_similar_data.threshold>=-1){
            api.answer(queries[i].id, list, nlist);
            //}
        }
        
        //Expression Match
        else if(queries[i].type == expression_match){
			//answer_ExpressionMatch(queries[i].data.expression_match_data.expression,mails,list,&nlist);
		    //api.answer(queries[i].id, list, nlist);
        }

        //Group Analysis
        else {

            answer_GroupAnalysis(queries[i].data.group_analyse_data.mids, queries[i].data.group_analyse_data.len,mails, list, &nlist);
            api.answer(queries[i].id, list, nlist);
   
        }
    }

    //Garbage Collection
    //kill_FindSimilar(smrys, n_mails);
    free(mails);
    free(queries);
    free(list);

    return 0;
}

/************Math************/

//Choose the bigger one
int argmax(int a, int b)
{
   if (a>b){
       return 0;
   }
   else{
       return 1;
   }
}

bool inDomainInt(int val, int lower, int upper){
    if(val<=upper && val>=lower)
        return true;
    else
        return false;
}

/************Tokenize************/
int popToken(char message[], char token[], int iStr){
    char c;
    int asc; //ascii number
    //No string left
    if (iStr < 0){
        token[0] = '\0';
        return -1;
    }

    int i = 0; //token[i]
    while(message[iStr] != '\0' ){
        c = message[iStr];
        asc = (int)c; //ascii number

        if (isRegularExpr_ASCII(asc)){
            if (isUpperCase_ASCII(c))
                c = tolower(c);
            token[i] = c;
            ++i;
            ++iStr;
        }
        else{
            if (i==0){
                ++iStr;
                continue;
            }
            else 
                break;
        }
    }

    if (message[iStr] == '\0'){ // EOF
        iStr= -1;
    }

    token[i] = '\0'; //end of token

    return iStr;
}

bool isRegularExpr_ASCII(int asc){
    if(isNumber_ASCII(asc))
        return true;
    else if(isUpperCase_ASCII(asc))
        return true;
    else if(isLowerCase_ASCII(asc))
        return true;
    else
        return false;
}

bool isNumber_ASCII(int asc){
    return inDomainInt(asc, 48, 57);
}

bool isUpperCase_ASCII(int asc){
    return inDomainInt(asc, 65, 90);
}

bool isLowerCase_ASCII(int asc){
    return inDomainInt(asc, 97, 122);
}

int char2num(char c){
    if(isNumber_ASCII(c)){
        return (int)c - '0';
    }
    else if(isLowerCase_ASCII(c)){
        return (int)c - 'a' + 10;
    }
    else{
        return (int)c;
    }
}

/********Dynamic Array (Int) stack*********/

void init_dymArr(dymArr* arr, int size){
    assert(size>=1);
    int* is = (int*)malloc(size*sizeof(int));
    if(is==NULL){
        fprintf(stderr, "Init Error: Insufficient Memory.\n");
        exit(1);
    }

    arr->i = is;
    arr->len = 0;
    arr->size = size;
}

void kill_dymArr(dymArr* arr){
    arr->size=0;
    arr->len=0;
    free(arr->i);
};

void resize_dymArr(dymArr* arr, int new_max_size){
    arr->size = new_max_size;
    arr->i = realloc(arr->i, sizeof(int)*new_max_size);
}

void clear_Arr(dymArr* arr){
    arr->len = 0;
}

void append_dymArr(dymArr* arr, int val){
    ++(arr->len);
    //Augement size

    if((arr->len+1) > arr->size){
      int new_size = (arr->size)*2 + 1;
      arr->i = realloc(arr->i, sizeof(int)*new_size);
      arr->size = new_size;
      if(arr==NULL){
        fprintf(stderr, "Append Error: Insufficient Memory.\n");
        exit(1);
       }
    }

    arr->i[arr->len - 1] = val;
}

int get_item(dymArr arr, int i){
    return arr.i[i];
}

int pop_item(dymArr* arr){
    if(arr->len==0)
        return EMTY_QUE_SIG;
    int val = arr->i[arr->len-1];
    --arr->len;

    return val;
}

/*************Queue************/

que init_que(int size){
    que q;
    init_dymArr(&q.arr,size);
    q.head = -1;
    q.tail = -1;
    return q;
}

void kill_que(que* q){
    kill_dymArr(&q->arr);
}

void enque(que* q, int val){
    append_dymArr(&q->arr, val);
    if(q->head == -1){ //first element
        ++(q->head);
    }
    q->tail = q->arr.len - 1;
}

int deque(que* q){
    if(q->head > q->tail || q->head==-1){
        return EMTY_QUE_SIG;
    }

    int val = get_item(q->arr, q->head);
    ++(q->head);
    return val;
}

int peek_que(que* q){
    if(q->head > q->tail || q->arr.len==0)
        return EMTY_QUE_SIG;
    else 
        return q->arr.i[q->head];
}

/************Generic Array************/

void copy_item_array(void* dstArr, int locDst,void* srcArr, int locSrc, size_t size){
    //Start point
    int start_dst = locDst*size;
    int start_src = locSrc*size;

    if (size=sizeof(int)){
        *(int*)(dstArr+start_dst) = *(int*)(srcArr+start_src);
    }
    else if (size=sizeof(long)){
        //printf("f");
        *(long*)(dstArr+start_dst) = *(long*)(srcArr+start_src);
    }
    else{
        //Copy
        memcpy((byte*)(dstArr+start_dst), (byte*)(srcArr+start_src), size);
        //*(byte*)(srcArr+j+start_src) = *(byte*)(dstArr+j+start_dst);
    }
}

void init_uArray(uArray* arr, size_t eleSize){
    byte* mem = (byte*)malloc(eleSize*INIT_NUM_ARRAY_ELEMENT);
    
    //Check memory is allocated
    if(mem==NULL){
        fprintf(stderr, "Stack Init Error: Insufficient Memory.\n");
        exit(1);
    }

    //Initiation
    arr->eleSize = eleSize;
    arr->len = 0;
    arr->memory = mem;
    arr->num_maxEle=INIT_NUM_ARRAY_ELEMENT;
}

int len_uArray(uArray* arr){
    return arr->len;
}

void get_uArray(uArray* arr, int i,void* item){
    //Check i domain
    if (i>=len_uArray(arr) || i<0){
        fprintf(stderr, "Invalid index with array length %d. Got i=%d\n", arr->len, i);
        exit(1);
    }

    //Copy item
    copy_item_array(item, 0, arr->memory, i, arr->eleSize);
}

void set_uArray(uArray* arr, int i,void* item){
    //Check i domain
    if (i>=len_uArray(arr) || i<0){
        fprintf(stderr, "Invalid index with array length %d. Got i=%d\n", arr->len, i);
        exit(1);
    }

    //Copy item
    copy_item_array(arr->memory, arr->len-1, item, 0, arr->eleSize);
}

void remove_uArray(uArray* arr, int I){
    
    for(int i=arr->len-1;i>I;i--){
        copy_item_array(arr->memory, i-1, arr->memory, i, arr->eleSize);
    }

    --arr->len;

    //Shrink memory
    if(arr->len < arr->num_maxEle/2-10){
        update_size_uArray(arr, arr->num_maxEle/2);
    }
}

void insert_uArray(uArray* arr, int I,void* item){

    //For empty array 
    if(arr->len == 0 && I==0){
        append_uArray(arr, item);
        return;
    }

    ++arr->len;
    //Extend memory
    if(arr->len == arr->num_maxEle){
        update_size_uArray(arr, arr->num_maxEle*2+1);
    }

    //Shift right
    for(int i=I;i<arr->len-1;i++){
        copy_item_array(arr->memory, i+1, arr->memory, i, arr->eleSize);
    }

}

void append_uArray(uArray* arr, void* item){
    ++arr->len;
    //Augment size
    if(arr->len == arr->num_maxEle){
        update_size_uArray(arr, arr->num_maxEle*2+1);
    }   

    copy_item_array(arr->memory, arr->len-1, item, 0, arr->eleSize);
}

void update_size_uArray(uArray* arr, int new_max_item){
    arr->num_maxEle = new_max_item;
    arr->memory = realloc(arr->memory, arr->eleSize*arr->num_maxEle);
    if(arr->memory==NULL){
        fprintf(stderr, "Update size error: Invalid Memory allocation with size %d\n", arr->num_maxEle);
        exit(1);
    }
}

void kill_uArray(uArray* arr){
    free(arr->memory);
    arr->eleSize = 0;
    arr->len = 0;
    arr->num_maxEle = 0;
}

/**Sorting**/

void quicksort(int arr[], int left, int right){
    if (left < right){
        int q = partition(arr, left, right);
        quicksort(arr, left, q-1);
        quicksort(arr, q+1, right);
    }
}

int partition(int arr[], int left, int right){
    int i = left-1;
    int j;
    for(j=left; j < right; j++){
        if(arr[j] <= arr[right]){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i+1], &arr[right]);

    return i+1;
}

void swap(int* x, int* y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

/*matrix*/
void init_Matrix(Matrix* M, int nrow, int ncol){
    int* m = (int*)calloc(ncol*nrow, sizeof(int));
    M->m = m;
    M->ncol = ncol;
    M->nrow = nrow;
}

void kill_Matrix(Matrix* M){
    free(M->m);
    M->ncol = 0;
    M->nrow = 0;
}

void set_Matrix(Matrix* M, int r, int c, int val){
    int offset = r*M->ncol + c;
    M->m[offset] = val;
}

int get_Matrix(Matrix*M, int r, int c){
    int offset = r*M->ncol + c;
    return M->m[offset];
}

void init_Matrix_ushort(Matrix_ushort* M, int nrow, int ncol){
    ushort **array = malloc(nrow * sizeof *array + (nrow * (ncol * sizeof **array)));
    if(array==NULL){
        printf("Memeory Insufficient: init matrix");
    };
    size_t i;
    ushort * const data = array + nrow;
    for(i = 0; i < nrow; i++){
        array[i] = data + i * ncol;
    }

    M->m = array;
    M->ncol = ncol;
    M->nrow = nrow;
    M->len = (ushort*)calloc(nrow, sizeof(ushort));
}

void kill_Matrix_ushort(Matrix_ushort* M){
    free(M->m);
    free(M->len);
}

void init_FS(infoFs* info){
    init_Matrix_ushort(&info->hstack, Q_RABIN, MAX_N_MAIL);
    info->num_unique = (double*)calloc(MAX_N_MAIL,sizeof(double));
    info->SimList = (double*)calloc(MAX_N_MAIL, sizeof(double));
};

void kill_FS(infoFs* info){
    free(info->num_unique);
    free(info->SimList);
    kill_Matrix_ushort(&info->hstack);
};

void register_hash(infoFs* info, int ID, int hash){
    if(info->hstack.len[hash] != 0){//check duplicate
        int end = info->hstack.m[hash][info->hstack.len[hash]-1];
        if(end == ID){//already appended
            return;
        }
    }

    //Add hash
    info->hstack.m[hash][info->hstack.len[hash]] = ID;
    ++info->hstack.len[hash];

    //Register unique count
    info->num_unique[ID] += 1;
};

/** Return location*/
int popTokenHash(char message[], char token[], int iStr, int* Hash){
    char c;
    int asc; //ascii number
    *Hash = 0; //reset hash value
    //No string left
    if (iStr < 0){
        token[0] = '\0';
        return -1;
    }

    int i = 0; //token[i]
    while(message[iStr] != '\0' ){
        c = message[iStr];
        asc = (int)c; //ascii number

        if (isRegularExpr_ASCII(asc)){
            if (isUpperCase_ASCII(c))
                c = tolower(c);
            token[i] = c;
            ++i;
            ++iStr;
        }
        else{
            if (i==0){
                ++iStr;
                continue;
            }
            else 
                break;
        }

    }

    if (message[iStr] == '\0'){ // EOF
        iStr= -1;
    }

    token[i] = '\0'; //end of token
    *Hash = Hash_RK(token);

    return iStr;
}

void append_mHash(infoFs* info, mail* mails, int ID){
    char* text = mails[ID].content;
    char* subject = mails[ID].subject;
    int hash;
    int iNxt;
    int iStr = 0;
    char token[TOKEN_STRING_LENGTH];

    // Content
    while(1){
        iNxt = popTokenHash(text, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;
        register_hash(info, ID, hash);
    }

    //Subject
    iStr = 0;
    while(1){
        iNxt = popTokenHash(subject, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;
        register_hash(info,ID, hash);
    }
}

void proc_FS(infoFs* info, mail* mails, int n_mail){
    int ID;
    for(int i=0;i<n_mail;i++){
        ID = mails[i].id;
        append_mHash(info,mails, ID);
    }
}

int Hash_RK(char s[]){
	int i = 0;
	int RK = 0;
	while(s[i]!='\0'){
		RK = (D_RABIN*RK + (int)s[i])%Q_RABIN;
		i++;
	}
	return abs(RK)%Q_RABIN;
}

void answer_FS(infoFs*info, mail* mails, int ID, int n_mail, double threshold, int* list, int* nlist){
    bool isVis[Q_RABIN] = {false};
    double Overlap[MAX_N_MAIL]={0};
    char* text = mails[ID].content;//Remember to add subject
    int iNxt;
    int iStr=0;
    int hash;
    double sim;
    char token[TOKEN_STRING_LENGTH];
    ushort id = (ushort)ID;
    ushort interID;
    *nlist = 0;

    // Content
    while(1){
        iNxt = popTokenHash(text, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;

        if(isVis[hash]){
            continue;
        }
        
        //Find similar
        for(int i=0;i<info->hstack.len[hash];i++){
            interID = info->hstack.m[hash][i];
            ++Overlap[(int)interID];
        }
        isVis[hash] = true;
    }

    char* subject = mails[ID].subject; 
    iStr = 0;
    while(1){
        iNxt = popTokenHash(subject, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;

        if(isVis[hash]){
            continue;
        }
        
        //Find similar
        for(int i=0;i<info->hstack.len[hash];i++){
            interID = info->hstack.m[hash][i];
            ++Overlap[(int)interID];
        }
        isVis[hash] = true;
    }
    
    // Similarity
    for(int i=0;i<n_mail;i++){
        sim = Overlap[i] / (info->num_unique[i] + info->num_unique[ID]  - Overlap[i]);
        if(sim>threshold && i!=ID){
            list[*nlist]=i;
            ++(*nlist);
        }
    }
}
