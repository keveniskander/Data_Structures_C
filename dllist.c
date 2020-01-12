/*
--------------------------------------------------
Project: cp264a5q1
File:    dllist.c
Author:  Keven Iskander
Version: 2019-02-15
--------------------------------------------------
*/

#include "dllist.h"

NODE *new_node(char data) {
	node *np = (node *) malloc(sizeof(node));
	np->data = data;
	np->prev = NULL;
	np->next = NULL;
	return np;
}

void display_forward(NODE *np) {
	while(np != NULL) {
	printf("%d\n", np->data);
	np = np->next;
	}
}

void display_backward(NODE *np) {
	while(np!=NULL){
		printf("%d\n", np->data);
		np = np->prev;
	}
}

void insert_start(NODE **startp, NODE **endp, NODE *new_np) {

	if(startp==NULL){
		new_np->prev = NULL;
		new_np->next = NULL;
		*startp = new_np;
		*endp = new_np;
	}else{
		new_np->prev = NULL;
		new_np->next = *startp;
		(*startp)->prev = new_np;
		*startp = new_np;
	}
}

void insert_end(NODE **startp, NODE **endp, NODE *new_np) {

	if(endp==NULL){
		new_np->prev = NULL;
		new_np->next = NULL;
		*endp = new_np;
		*startp = new_np;
	}else{
		new_np->prev = NULL;
		new_np->next = *endp;
		(*endp)->prev = new_np;
		*endp = new_np;
	}
}

void delete_start(NODE **startp, NODE **endp) {

	NODE *ptr = *startp;
	if(ptr!=NULL){
		if(ptr==*endp){
			*startp = NULL;
			*endp = NULL;
		}else{
			*startp = ptr->next;
			(*startp)->prev = NULL;
		}
		free(ptr);
	}
}

void delete_end(NODE **startp, NODE **endp) {

	NODE *ptr = *endp;
	if(ptr!=NULL){
		if(ptr==*startp){
			*endp = NULL;
			*startp = NULL;
		}else{
			*endp = ptr->next;
			(*endp)->prev = NULL;
		}
		free(ptr);
	}
}

void clean(NODE **startp, NODE **endp) {

	node* temp;
	NODE *np = *startp;
	    while (np != NULL)
	    {
	        temp = np;
	        np = np -> next;
			free(temp);
	    }

}
