/*
--------------------------------------------------
Project: cp264a9q2
File:    hash.c
Author:  Keven Iskander
Version: 2019-03-25
--------------------------------------------------
*/

#include "hash.h"
#include <string.h>
#include <stdlib.h>

int hash(char* word) {
  unsigned int hash = 0, i;
  for (i = 0; word[i] != '\0'; i++) {
    hash = 31 * hash + word[i];
  }
  return hash % htsize;
}

hashnode *new_hashnode(char *name, int value) {
	hashnode *np = (hashnode*) malloc(sizeof(hashnode));
	np->value = value;
	strncpy(np->name, name, 10);
	np->next = NULL;
	return np;
}

hashtable *new_hashtable(int size) {
	// allocate space for hashtable structure
	  hashtable *ht = (hashtable*) malloc(sizeof(hashtable));
	  // allocate memory to hold the array of hashnode pointers
	  ht->hnp = (hashnode**) malloc(sizeof(hashnode**)*size);

	  // initialize each pointers of array to NULL;
	  int i;
	  for (i=0; i<size; i++)
	    *(ht->hnp+i) =  NULL;   //ht->hnp[i] = NULL;

	  // set the size property
	  ht->size = size;

	  // set the count property
	  ht->count = 0;

	  return ht;
}

hashnode *search(hashtable *ht, char *name) {
	int i = hash(name);
	hashnode *p = *(ht->hnp + i); //hashnode *p = ht->hnp[i];
	if (p != NULL) {
	while ( p != NULL) {
	  if (name == p->name )  // return the first data element matching the key
		return p;
	  p = p->next;
	}
	}
	return NULL;
}

int insert(hashtable *ht, hashnode *np) {
	char *name = np->name;
	int i = hash(name);
	hashnode *p = *(ht->hnp + i), *pp = NULL;  // pp for previous pointer

	if (p == NULL) {

	// empty linked list
		*(ht->hnp + i) = np; // set new node as the leading node

	}
	else {
	while (p && name > p->name) {  // ordered by key value for search
	 pp = p;
	 p = p->next;
	}

	if (pp == NULL)
	*(ht->hnp + i) = np;
	else{
		pp->next = np;
	}

	np->next = p;
	return 1;
	}

	ht->count++;
	return 0;
}

int delete(hashtable *ht, char *name) {
	int index = hash(name);

		hashnode *ptr = ht->hnp[index], *prev;

		while (ptr) {

			if (strcmp(ptr->name, name) == 0) {

				if (ptr->next != NULL) {
				prev->next = ptr->next;
				free(ptr);
				} else {
					*(ht->hnp + index) = NULL;
				}
				ht->count--;
				return 1;

			}
			prev = ptr;
			ptr = ptr->next;
		}

		return 0;
}

void clean_hash(hashtable **htp) {
  if (*htp == NULL) return;
  hashtable *ht = *htp;
  hashnode *sp = ht->hnp[0], *p, *temp;
  int i;
  for (i = 0; i < ht->size; i++) {
    p = ht->hnp[i];
    while (p) {
      temp = p;
      p = p->next;
      free(temp);
    }
  ht->hnp[i] = NULL;
  }
  free(ht->hnp);
  ht->hnp = NULL;
  *htp = NULL;
}

void display(hashtable *ht) {
  int i = 0;
  hashnode *p;
  printf("size:  %d\n", ht->size);
  printf("count: %d\n", ht->count);
  printf("hash data:\nindex: list of the data elements");
  for (i = 0; i < ht->size; i++) {
    p = *(ht->hnp + i);
    if (p)
      printf("\n%2d: ", i);
    while (p) {
      printf("(%s,%d) ", p->name, p->value);
      p = p->next;
    }
  }
  printf("\n");
}
