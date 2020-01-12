/*
--------------------------------------------------
Project: cp264a9q2
File:    hash.h
Author:  Keven Iskander
Version: 2019-03-25
--------------------------------------------------
*/

#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int htsize;

typedef struct hashnode {
  char name[10];  // used as key variable
  int value;
  struct hashnode *next;
} hashnode;

typedef struct hashtable {
  hashnode **hnp;    // pointer pointing to the array of hashnode pointers
  int size;          // hash table size, maximum number of different indices
  int count;         // number of data elements in the hash table
} hashtable;

/* hash function that hash name string to an integer of modular htsize */
int hash(char *name);

/* create dynamically a hash node and set name and value and return the point */
hashnode *new_hashnode(char *name, int vale);

/* create dynamically a chained hash table of the size */
hashtable *new_hashtable(int size);

/* search the hash table and return the pointer of found hashnode */
hashnode *search(hashtable *ht, char *name);

/* insert hashnode np to hash table
 * when the named hashnode exists, update the hashnode's value by np->value, return 0;
 * otherwise insert into the hash table, return 1
*/
int insert(hashtable *ht, hashnode *np);

/* delete hashnode by name. If the named hash node exists, delete it and return 1;
 * otherwise return 0
*/
int delete(hashtable *ht, char *name);

void clean_hash(hashtable **htp);

void display(hashtable *ht);

#endif
