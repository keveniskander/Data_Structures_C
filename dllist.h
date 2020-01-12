/*
--------------------------------------------------
Project: cp264a5q1
File:    dllist.h
Author:  Keven Iskander
Version: 2019-02-15
--------------------------------------------------
*/

#ifndef DLLIST
#define DLLIST

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *prev;
    struct node *next;
} NODE;

typedef struct node node;  // define node as stuct node

/*
typedef struct node {
  int data;
  struct node *next;
  struct node *prev;
} node;
*/

NODE *new_node(char data);
void display_forward(NODE *start);
void display_backward(NODE *end);
void insert_start(NODE **startp, NODE **endp, NODE *new_np);
void insert_end(NODE **startp, NODE **endp, NODE *new_np);
void delete_start(NODE **startp, NODE **endp);
void delete_end(NODE **startp, NODE **endp);
void clean(NODE **startp, NODE **endp);

#endif
