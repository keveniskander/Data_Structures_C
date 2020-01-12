/*
--------------------------------------------------
Project: cp264a6q3
File:    stack.c
Author:  Keven Iskander
Version: 2019-03-03
--------------------------------------------------
*/

#include "stack.h"

void push(SNODE **topp, int value) {
	SNODE *temp = (SNODE*) malloc(sizeof(SNODE));
	temp->data = value;
	temp->next = NULL;
	if (*topp == NULL) {
		*topp = temp;
	} else {
		temp->next = (*topp);
		(*topp) = temp;
	}
}

void pop(SNODE **topp) {

	SNODE *temp;
	if(topp == NULL){
		printf("Error: Nothing to pop.");
	}else{
		temp = *topp;
		*topp = (*topp)->next;
		temp->next = NULL;
		free(temp);
	}
}

int peek(SNODE *top) {

	int val = 0;
	if(top != NULL){
		val = top->data;
	}else{
		printf("Error: Nothing to peek");
		val = NULL;
	}
	return val;
}

void clean(SNODE **topp) {

	SNODE *ptr = *topp, *temp;
	while(ptr != NULL){
		temp = ptr;
		ptr = ptr->next;
		free(temp);
	}
	*topp = NULL;
}
