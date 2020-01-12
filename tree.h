/*
--------------------------------------------------
Project: cp264a7q1
File:    tree.h
Author:  Keven Iskander
Version: 2019-03-08
--------------------------------------------------
*/

#ifndef TREE_H
#define TREE_H

#include<stdio.h>
#include<stdlib.h>

typedef struct tree_node {
  int data;
  struct tree_node *left;
  struct tree_node *right;
} TNODE;

/*  creates a TNODE node and sets the data to value and returns the pointer */
TNODE *new_node(int value);

/* this computes and returns the number of node count of the tree passed by root.*/
int get_count(TNODE *root);

/* this computes and returns the number of the tree passed by root. */
int get_height(TNODE *root);

/* this cleans the tree passed by rootp. */
void clean_tree(TNODE **rootp);

/* this displays the node data of the tree by pre-order. */
void display_preorder(TNODE *root);

/* this displays the node data of the tree by in-order. */
void display_inorder(TNODE *root);

/* this displays the node data of the tree by post-order. */
void display_postorder(TNODE *root);

/* this displays the tree in 2D text format */
void display_tree(TNODE *root, int prelen);

/* this displays the tree in breadth-first order using additional queue data structure */
void iterative_bf_display(TNODE *root);

/* this does the breadth-first search */
TNODE *iterative_bf_search(TNODE *root, int val);

/* this does the depth-first search */
TNODE *iterative_df_search(TNODE *root, int val);

//queue data structure for breadth-first traversal and search
typedef struct queue_node {
  void *pdata;
  struct queue_node *next;
} QNODE;
typedef struct queue {
	QNODE *front;
	QNODE *rear;
} queue;
void enqueue(QNODE **frontp, QNODE **rearp, void *pdata);
void *dequeue(QNODE **frontp, QNODE **rearp);
void clean_queue(QNODE **frontp, QNODE **rearp);

// stack data structure for depth-first traversal and search
typedef struct stack_node {
  void *pdata; // pointer data
  struct stack_node *next;
} SNODE;
void push(SNODE **topp, void *pdata);
void pop(SNODE **topp);
void *peek(SNODE *top);
void clean_stack(SNODE **topp);

#endif
