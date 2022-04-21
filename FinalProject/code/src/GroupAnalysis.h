#ifndef GROUPANALYSIS_H
#define GROUPANALYSIS_H
#include "api.h"
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