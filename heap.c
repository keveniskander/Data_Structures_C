/*
--------------------------------------------------
Project: cp264a9q1
File:    heap.c
Author:  Keven Iskander
Version: 2019-03-25
--------------------------------------------------
*/



#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size = 0;

HEAP *new_heap(int capacity)
{
	HEAP *hp = malloc(sizeof(HEAP)*capacity);
	hp->capacity = capacity;
	hp->size = 0;
	hp->hnap = (HNODE*)malloc(sizeof(HNODE)*capacity);
	return hp;
}

void insert(HEAP *heap, HNODE new_node)
{
	if (heap->size >= heap->capacity) {
			heap->capacity <<= 1;
			heap->hnap = realloc(heap->hnap, sizeof(HNODE) * heap->capacity);
		}

		heap->hnap[heap->size] = new_node;

		int parent, index = heap->size;
		while (index) {
			parent = (index - 1) >> 1;  //equivalent to parent = (index11)/ 2;
			if (cmp(heap->hnap[parent].key, heap->hnap[heap->size].key) == 0)
				break;
			else {
				heap->hnap[index] = heap->hnap[parent];
				index = parent;
			}
			}
		heap->hnap[index] = new_node;

		heap->size++;
}

HNODE extract_min(HEAP *heap)
{
	// your implementation
		HNODE temp = heap->hnap[0];
		heap->hnap[0] = heap->hnap[heap->size - 1];
		int index = 0, n = heap->size - 1;

		HNODE val = heap->hnap[0];
		int ci = (index << 1) + 1;  //left child, equivalent to ci = index * 2 + 1;
		while (ci <= n) { // if has the left child
			if ((ci < n) && (heap->hnap[ci].key > heap->hnap[ci + 1].key))
				ci++;  // ci is now the child of bigger key

			if (heap->hnap[ci].key > val.key)
				break; // the both children has key values less the val, done stop.
			else {
				heap->hnap[index] = heap->hnap[ci]; //change key value by the bigger child's value
				index = ci;
				ci = (index << 1) + 1;
			}
		}
		heap->hnap[index] = val;
		//sfree(heap->hnap[0]);
		heap->size--;
		if (heap->size == heap->capacity / 4) {
			heap->capacity /= 2;
			heap->hnap = realloc(heap->hnap, sizeof(HNODE) * heap->capacity);

		}
		return temp;

}

void decrease_key(HEAP *heap, int node_index, KEYTYPE key_value)
{
	heap->hnap[node_index].key = key_value;
	HNODE temp = heap->hnap[node_index];
	int parent, index = node_index;
	while(index){
		parent = (index-1)>>1;
		if (cmp(heap->hnap[parent].key, heap->hnap[heap->size].key) == 0)
				break;
			else {
				heap->hnap[index] = heap->hnap[parent];
				index = parent;
			}
		}
	heap->hnap[index] = temp;
}

int find_index(HEAP *heap, DATA value) {
	int i = 0;
	while(i<heap->size){
		if(heap->hnap[i].data == value){
			return i;
		}
		i++;
	}

	return -1;
}

void display_heap(HEAP *hp) {
    printf("\nsize:%d\ncapacity:%d\n", hp->size, hp->capacity);
    printf("(index, key, data):\n");
    int i;
    for (i=0; i < hp->size; i++) {
      printf("(%d %d %d) ", i, hp->hnap[i].key, hp->hnap[i].data);
      if (i % 10 == 9) printf("\n");
    }
    printf("\n");
}

int cmp(KEYTYPE a, KEYTYPE b) {
    if (a < b)
       return -1;
    else if (a==b)
       return 0;
    else
       return 1;
}
