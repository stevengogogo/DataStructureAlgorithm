#ifndef EXPRESSIONMATCH_H
#define EXPRESSIONMATCH_H
#include "utils.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "GroupAnalysis.h"
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