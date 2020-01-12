/*
--------------------------------------------------
Project: cp264a6q2
File:    queue.c
Author:  Keven Iskander
Version: 2019-03-03
--------------------------------------------------
*/

#include "queue.h"

void enqueue(QNODE **frontp, QNODE **rearp, int val)
{
	QNODE *new = (QNODE*) malloc(sizeof(QNODE));
	new->data = val;
	new->next = NULL;
	if(*frontp == NULL && *rearp == NULL){
		*frontp = new;
		*rearp = *frontp;
	}else{
		(*rearp)->next = new;
		*rearp = new;
	}
}

int dequeue(QNODE **frontp, QNODE **rearp)
{
	QNODE *temp;
	int result = 0;
	if(*frontp != NULL){
		result = (*frontp)->data;
		if(*frontp == *rearp){
			*frontp = NULL;
			*rearp = NULL;
		}else{
			temp = *frontp;
			*frontp = (*frontp)->next;
			free(temp);
		}
	}
	return result;
}

int peek(QNODE *front)
{
	int val = 0;
	if(front != NULL){
		val = front->data;
	}else{
		printf("Nothing to peek\n");
		val = NULL;
	}
	return val;
}

void clean(QNODE **frontp, QNODE **rearp)
{
	QNODE *p = *frontp, *temp;
	while(p != NULL){
		temp = p;
		p = p->next;
		free(temp);
	}
	*frontp = NULL;
	*rearp = NULL;
}
