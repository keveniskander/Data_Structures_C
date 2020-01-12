/*
--------------------------------------------------
Project: cp264a5q1
File:    llist.c
Author:  Keven Iskander
Version: 2019-02-15
--------------------------------------------------
*/

#include "llist.h"

#include <stdio.h>
#include <stdlib.h>


void display(NODE *start) {
	printf("Value Address\n");
	  while(start != NULL) {
	    printf("%5d %d\n", start->data.name, start);
	    start = start->next;
	  }
}

NODE* search(NODE *startp, char *name) {
	while((startp != NULL) && (startp->data.name != name)) {
	    startp = startp->next;
	  }
	  return startp;
}

void insert(NODE **startp, char *name, float score) {
	struct node* np = (struct node *)malloc(sizeof(struct node));
	  if (np == NULL) {printf("malloc fails"); return;}
	  np->data.score = score;
	  np->next = NULL;

	  np->next = *startp;
	  *startp = np;
}

int delete(NODE **startp, char *name) {
	struct node *np = *startp;
	  struct node *prev = NULL;

	  while ( (np != NULL) && (np->data.name != name )) {
	    prev = np;
	    np = np->next;
	  }

	  if (np == NULL)
	    return 0;
	  else {
	    if (prev == NULL)
	      *startp = np->next;
	    else
	      prev->next = np->next;

	#ifdef usefree
	    free(np);
	#endif

	    return 1;
	  }
}

void clean(NODE **startp) {
	struct node *temp, *np = *startp;
	  while (np != NULL) {
	    temp = np;
	    np = np -> next;
	    free(temp);
	  }
	  *startp = NULL;
}

// the following functions are adapted and modified from previous assignments. You make use of them.

void report_data(NODE *start, char *filename) {
    NODE *np = start;
    int count = 0;
    float mean = 0;
    float stddev = 0;
    int histogram[6] = {0};
    FILE *fp = fopen(filename, "w");

    fprintf(fp, "grade report\n");
    while (np != NULL) {
        count++;
        mean += np->data.score;
        stddev += np->data.score * np->data.score ;
        //histogram data
        if (np->data.score >=100)  histogram[0]++;
        else if (np->data.score < 50)  histogram[5]++;
        else histogram[(unsigned int) (99.99-np->data.score)/10]++;

        fprintf(fp, "%-15s%3.1f%4c\n", np->data.name, np->data.score, letter_grade(np->data.score));
        np = np->next;
    }
    mean /= count;
    stddev = sqrt(stddev/count - mean*mean);

    fprintf(fp, "\nstatistics summary\n");
    fprintf(fp, "%-15s%d\n", "count", count);
    fprintf(fp, "%-15s%3.1f\n", "mean", mean);
    fprintf(fp, "%-15s%3.1f\n", "stddev", stddev);
    fprintf(fp, "%-15s%3.1f\n", "median", median(start));

    fprintf(fp, "histogram\n");
    int i;
    fprintf(fp, "%-15s%d\n", "[90,100]", histogram[0]);
    for (i=1; i<5; i++) {
       fprintf(fp, "[%d,%d)        %d\n", 90-i*10, 100-i*10, histogram[i]);
    }
    fprintf(fp, "%-15s%d\n", "[0,50)", histogram[5]);

    fclose(fp);
}

void import_data(NODE **startp, char *filename) {
    char line[40], name[20];
    FILE *fp = fopen(filename, "r");
    char *result = NULL;
    char delimiters[] = ",";
    float score = 0;

    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        result = strtok(line, delimiters);
        strcpy(name, result);
        result = strtok(NULL, delimiters);
        score = atof(result);
        insert(startp, name, score);
    }
    fclose(fp);
}


char letter_grade(float s){
  char r = 'F';
  if (s >= 85) r = 'A';
  else if (s >= 70) r = 'B';
  else if (s >= 60) r = 'C';
  else if (s >= 50) r = 'D';
  else r = 'F';
  return r;
}

void swap(float *first, float *second )
{
  float temp;
  temp = *first;
  *first = *second;
  *second = temp;
}

void quick_sort(float *a, int m, int n)
{
  float key;
  int i,j,k;

  if( m < n ) {
    k = (m+n)/2;
    swap(a+m, a+k);
    key = *(a+m);
    i = m+1;
    j = n;
    while(i <= j) {
      while( i <= n && *(a+i) <= key)
      i++;
      while( j >= m && *(a+j) > key )
      j--;
      if( i < j)
      swap(a+i, a+j);
    }
    swap(a+m, a+j);
    quick_sort(a, m, j-1);
    quick_sort(a, j+1, n);
  }
}

float median(NODE *start)
{
  if (start == NULL) return 0;
  int len = 0, i=0;
  NODE *np = start;
  while (np) { len++; np = np->next; }

  float a[len];
  for (i=0, np=start; i<len; i++, np=np->next) {
    a[i] = np->data.score;
  }

  quick_sort(a, 0, len-1);

  if (len % 2 == 1)
   return a[len/2];
  else
   return (a[len/2-1] + a[len/2])/2 ;
 }
