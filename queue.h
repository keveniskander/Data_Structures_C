/*
--------------------------------------------------
Project: cp264a6q2
File:    queue.h
Author:  Keven Iskander
Version: 2019-03-03
--------------------------------------------------
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <malloc.h>

typedef struct node {
  int data;
  struct node *next;
} QNODE;

void enqueue(QNODE **frontp, QNODE **rearp, int);
int dequeue(QNODE **frontp, QNODE **rearp);
int peek(QNODE *front);
void clean(QNODE **frontp, QNODE **rearp);

#endif
