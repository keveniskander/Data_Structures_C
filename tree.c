/*
--------------------------------------------------
Project: cp264a7q1
File:    tree.c
Author:  Keven Iskander
Version: 2019-03-08
--------------------------------------------------
*/

#include "tree.h"

TNODE *new_node(int value) {
  TNODE *np = (TNODE *) malloc(sizeof(TNODE));
  if (np == NULL) return NULL;
  np->data = value;
  np->left = NULL;
  np->right = NULL;
  return np;
}

int get_count(TNODE *root) {
	int count = 0;
		if(root)
		{
			count += 1;
			count += get_count(root->left);
			count += get_count(root->right);

		}
	return count;
}
int get_height(TNODE *root) {

	int lheight;
	int rheight;
	if(root == NULL){
		return 0;
	}else{
		lheight = get_height(root->left);
		rheight = get_height(root->right);

		if(lheight>rheight){
			return(lheight + 1);
		}else{
			return(rheight + 1);
		}
	}
}

void clean_tree(TNODE **rootp) {

	TNODE *root = *rootp;
	  if (root) {
	    if (root->left)
	      clean_tree(&root->left);
	    if (root->right)
	      clean_tree(&root->right);
	    free(root);
	  }
	  *rootp = NULL;
	}


void display_preorder(TNODE *root) {
	if (root) {
		printf("%c ", root->data);
	    display_preorder(root->left);
	    display_preorder(root->right);
	  }

}

void display_inorder(TNODE *root) {
	if (root) {

		display_preorder(root->left);
		printf("%c ", root->data);
		display_preorder(root->right);
	  }
}

void display_postorder(TNODE *root) {

	if(root){
		display_preorder(root->left);
		display_preorder(root->right);
		printf("%c ", root->data);
	}
}

void iterative_bf_display(TNODE *root) { // iterative level order display

	queue q = {0};
	enqueue(&(q.front),&(q.rear),&(root->data));
	while (q.front != NULL){
		TNODE *current = dequeue(&(q.front),&(q.rear));
		printf(" %c",current->data);
		if(current->left != NULL)
		{
			enqueue(&(q.front),&(q.rear),&(current->left->data));

		}
		if(current->right != NULL)
		{
			enqueue(&(q.front),&(q.rear),&(current->right->data));

		}
	}
}

TNODE * iterative_bf_search(TNODE *root, int val) {
	queue q = {0};
	enqueue(&(q.front),&(q.rear),&(root->data));

	TNODE *current;
	while (q.front != NULL)
	{
		current = dequeue(&(q.front),&(q.rear));
		if (current->data  ==  val ){

			return current;
			break;

		}
		if(current->left != NULL)
		{
			enqueue(&(q.front),&(q.rear),&(current->left->data));

		}
		if(current->right != NULL)
		{
			enqueue(&(q.front),&(q.rear),&(current->right->data));

		}

	}
	if (q.front == NULL){
		TNODE *current = NULL;
	}
return current;
}

TNODE *iterative_df_search(TNODE *root, int val) {
	if (root == NULL) return NULL;
		SNODE *top = NULL;
		push(&top, root);
		TNODE *p = NULL;
		TNODE *cp = NULL;

		while (top) {
			p = peek(top);
			if (val == p->data) {
				clean_stack(&top); return p;
			}
			else if (cp == NULL) {
				if (p->left != NULL) {
					cp = NULL;
					push(&top, p->left);
				}
				else if (p->right != NULL) {
					cp =  NULL;
					push(&top, p->right);
				}
				else {
					cp = p;
					pop(&top);
				}
			}
			else if (cp != NULL) {
				if (cp == p->left && p->right != NULL){
					cp = NULL;
					push(&top, p->right);
				}
				else{
					cp = p;
					pop(&top);
				}
			}
		}
		return NULL;
}//iterative_df_search(root,'F'->data);

void display_tree(TNODE *root, int prelen) {
  if (root) {
    int i;
    for (i = 0; i < prelen; i++)
      printf("%c", ' ');
    printf("%s", "|___");
    printf("%c\n", root->data);
    display_tree(root->right, prelen + 4);
    display_tree(root->left, prelen + 4);
  }
}

// queue functions adapted and modified from a6q2
void enqueue(QNODE **frontp, QNODE **rearp, void *pdata) {
   QNODE *qnp = (QNODE*) malloc(sizeof(QNODE));
   if (qnp == NULL) return;
   else {
     qnp->pdata = pdata;
     qnp->next = NULL;

     if (*frontp == NULL) {
      *frontp = qnp;
      *rearp = qnp;
     } else {
      (*rearp)->next = qnp;
      *rearp = qnp;
    }
   }
}
void *dequeue(QNODE **frontp, QNODE **rearp) {
  void *tnp = NULL;
  if (*frontp) {
    QNODE *qnp = *frontp;
    tnp = qnp->pdata;
    if (*frontp == *rearp) {
      *frontp = NULL;
      *rearp = NULL;
    } else {
      *frontp = qnp->next;
    }
    free(qnp);
    return tnp;
  }
  return NULL;
}
void clean_queue(QNODE **frontp, QNODE **rearp) {
  QNODE *temp, *qnp = *frontp;
  while (qnp != NULL) {
  temp = *frontp;
  qnp = qnp->next;
  free(temp);
  }
}

// stack functions adapted and modified from a6q3
void push(SNODE **topp, void *pdata) {
  SNODE *snp = (SNODE*) malloc(sizeof(SNODE));
  snp->pdata = pdata;
  snp->next = NULL;
  if (*topp == NULL) {
    *topp = snp;
  } else {
    snp->next = *topp;
    *topp = snp;
  }
}
void pop(SNODE **topp) {
  if (*topp != NULL) {
      SNODE *snp = *topp;
    *topp = snp->next;
    free(snp);
  }
}
void *peek(SNODE *top) {
  if (top != NULL) {
       return top->pdata;
  }
  return NULL;
}
void clean_stack(SNODE **topp) {
    SNODE *temp, *snp = *topp;
  while (snp) {
    temp = snp;
    snp = snp->next;
    free(temp);
  }
  *topp = NULL;
}
