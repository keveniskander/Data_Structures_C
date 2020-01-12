/*
--------------------------------------------------
Project: cp264a7q2
File:    bst.c
Author:  Keven Iskander
Version: 2019-03-08
--------------------------------------------------
*/

#include "bst.h"
#include <string.h>

TNODE *new_node(RECORD data) {
	TNODE *np = (TNODE *) malloc(sizeof(TNODE));
	if (np == NULL) return NULL;
	strcpy(np->data.name, data.name);
	np->data.score = data.score;
	np->left = NULL;
	np->right = NULL;
	return np;
}

TNODE* search(TNODE *root, char *name) {
	while (root) {
		if (name == root->data.name)
			return root;
		else if (name < root->data.name){
			root = root->left;
		}
		else {
			root = root->right;
		}
	}
	return NULL;
}

void insert(TNODE **rootp, char *name, float score) {
	RECORD data;
	strcpy(data.name, name);
	data.score = score;
	if (*rootp == NULL) {
		*rootp = new_node(data);
	}
	else {
		TNODE *p = *rootp;
		while (1) {
			if (data.name == p->data.name) {
				printf("\nThe same key value is found");
			}
			else if (data.name < p->data.name) {
				if (p->left == NULL) {
					p->left = new_node(data); break;
				}
				else p = p->left;
			}
			else {
				if (p->right == NULL) {
					p->right = new_node(data);
					break;
				}
				else p = p->right;
			}
		}
	}
}

void delete(TNODE **rootp, char *name) {
	TNODE *tnp, *parentp, *suc, *psuc, *ptr;
	if (*rootp == NULL) {
		printf("\nThe tree is empty ");
	}
	else
	{
		//find the node of the given value
		parentp = NULL;
		tnp = *rootp;
		while (tnp != NULL && name != tnp->data.name) {
			parentp = tnp;
			tnp = (name < tnp->data.name) ? tnp->left : tnp->right;
		}
		// value node not found
		if (tnp == NULL) {
			printf("\nThe value to be deleted is not present in the tree");
		}

		//tnp->data == val, node tnp will be deleted,
		if (tnp->left == NULL)
			ptr = tnp->right;
		else if (tnp->right == NULL)
			ptr = tnp->left;
		else {
			// find the smallest on right subtree
			psuc = tnp;
			suc = tnp->right;
			while (suc->left != NULL) {
				psuc = suc;
				suc = suc->left;
			}

			if (tnp == psuc) {
				suc->left = tnp->left;
			} else {
				psuc->left = suc->right;
				suc->left = tnp->left;
				suc->right = tnp->right;
			}
			ptr = suc;

		}
	}
}

TNODE *extract_smallest_node(TNODE **rootp) {
	TNODE *root = *rootp;
	if (root == NULL) {
		return NULL;
	}
	else if (root->left == NULL) {
		*rootp = root->right;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else {
		return extract_smallest_node(&root->left);
	}
}

void display_inorder(TNODE *root) {
  if (root) {
    display_inorder(root->left);
    printf("%s",root->data.name);
    printf("  %2.1f%\n",  root->data.score);
    display_inorder(root->right);
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
