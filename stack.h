/*
--------------------------------------------------
Project: cp264a6q3
File:    stack.h
Author:  Keven Iskander
Version: 2019-03-03
--------------------------------------------------
*/

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

typedef struct node {
  int data;
  struct node *next;
} SNODE;

void push(SNODE **topp, int value);
void pop(SNODE **topp);
int peek(SNODE *);
void clean(SNODE **topp);

#endif
