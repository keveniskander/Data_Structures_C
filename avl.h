/*
--------------------------------------------------
Project: cp264a8q1
File:    avl.h
Author:  Keven Iskander
Version: 2019-03-15
--------------------------------------------------
*/


#ifndef AVL_H
#define AVL_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct rec {
  char name[40];
  float score;
} RECORD;

typedef struct node {
    RECORD data;
    int height;
    struct node *left;
    struct node *right;
} TNODE;

/* check if the tree is AVL tree, return 1 if true, 0 otherwise */
int is_avl(TNODE *root);

/* do left rotation  */
TNODE *rotate_left(TNODE *root);

/* do right rotation  */
TNODE *rotate_right(TNODE *root);

/* insert record (name, score) into the AVL using name as key */
void insert(TNODE **rootp, char *name, float score);

/* delete node of data.name from the AVL */
void delete(TNODE **rootp, char *name);  //

// following functions are from a7q1 and a7q2

/* get and return and delete the node of the smallest data.name node from the bst */
TNODE *extract_smallest_node(TNODE **rootp);

/* display tree data by in-order */
void display_inorder(TNODE *root);

/* display tree in 2D text format */
void display_tree(TNODE *root, int prelen);

/* search BST by data.name */
TNODE *search(TNODE *root, char *name);

/* clean the tree */
void clean_tree(TNODE **rootp);

#endif
