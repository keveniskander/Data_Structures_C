/*
--------------------------------------------------
Project: cp264a8q1
File:    avl.c
Author:  Keven Iskander
Version: 2019-03-15
--------------------------------------------------
*/


#include "avl.h"

// A utility functions

int max(int a, int b) {
	return (a > b) ? a : b;
}

int height(TNODE *np) {
// return the node's height value
	if (np == NULL)
		return 0;
	else
		return np->height;
}

int balance_factor(TNODE* np) {
// return the balance factor at this node
	if (np == NULL)
		return 0;
	return height(np->left) - height(np->right);

}

int is_avl(TNODE *root) {
// your implementation
	TNODE *node = root;
	int balance = 1;
	if (node == NULL || node->height == 1) {
		return 1;
	}
	if ((abs(height(node->left) - height(node->right)) > 1) && (node->left && node->right)) {

		balance = 0;

	} else {

		balance = is_avl(node->right) && is_avl(node->left);
	}

	return balance;
}

TNODE *rotate_right(TNODE *y) {
// your implementation
	TNODE *x = y->left;
	TNODE *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	// Return new root
	return x;
}

TNODE *rotate_left(TNODE *x) {
// your implementation
	TNODE *y = x->right;
	TNODE *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	//  Update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	// Return new root
	return y;
}
void insert(TNODE **rootp, char *name, float score)
{
	/* 1.  Perform the normal BST rotation */
	TNODE *np = (TNODE *) malloc(sizeof(TNODE));
	if (np == NULL)
		return;
	strcpy(np->data.name, name);
	np->data.score = score;
	np->height = 1;
	np->left = NULL;
	np->right = NULL;

	// 1. Perform the normal BST insertion
	if (*rootp == NULL) {
		*rootp = np;
		return;
	}

	TNODE *root = *rootp;
	if (strcmp(name, root->data.name) < 0)
		insert(&root->left, name, score);
	else if (strcmp(name, root->data.name) > 0)
		insert(&root->right, name, score);
	else
		return;
	/* 2. Update height of this ancestor node */

	(*rootp)->height = 1 + max(height((*rootp)->left), height((*rootp)->right));

	/* 3. Get the balance factor of this ancestor
	 node to check whether this node became
	 unbalanced */

	int bf = balance_factor(*rootp);


	if (bf == 2 && balance_factor((*rootp)->left) >= 0) {
		*rootp = rotate_right(*rootp);
	}

	if (bf == 2 && balance_factor((*rootp)->left) < 0) {
		(*rootp)->left = rotate_left((*rootp)->left);
		(*rootp) = rotate_right(*rootp);
	}

	if (bf == -2 && balance_factor((*rootp)->right) <= 0)
		(*rootp) = rotate_left(*rootp);


	if (bf == -2 && balance_factor((*rootp)->right) > 0) {
		(*rootp)->right = rotate_right((*rootp)->right);
		(*rootp) = rotate_left(*rootp);
	}
}

void delete(TNODE **rootp, char *name) {
	TNODE *root = *rootp;
	TNODE* np;

	if (root == NULL)
		return;

	if (strcmp(name, root->data.name) == 0) {
		if (root->left == NULL && root->right == NULL) {
			free(root);
			*rootp = NULL;
		} else if (root->left != NULL && root->right == NULL) {
			np = root->left;
			free(root);
			*rootp = np;
		} else if (root->left == NULL && root->right != NULL) {
			np = root->right;
			free(root);
			*rootp = np;
		} else if (root->left != NULL && root->right != NULL) {
			np = extract_smallest_node(&root->right);
			np->left = root->left;
			np->right = root->right;
			free(root);
			*rootp = np;
		}
	} else {
		if (strcmp(name, root->data.name) < 0) {
			delete(&root->left, name);
		} else {
			delete(&root->right, name);
		}
	}


	if (*rootp == NULL)
		return;




	(*rootp)->height = 1 + max(height((*rootp)->left), height((*rootp)->right));

	int bf = balance_factor((*rootp));



	if (bf == 2 && balance_factor((*rootp)->left) >= 0) {
		 *rootp = rotate_right((*rootp));
	}

	if (bf == 2 && balance_factor((*rootp)->left) < 0) {
		(*rootp)->left = rotate_left((*rootp)->left);
		(*rootp) = rotate_right((*rootp));
	}

	if (bf == -2 && balance_factor((*rootp)->right) <= 0)
		(*rootp) = rotate_left((*rootp));


	if (bf == -2 && balance_factor((*rootp)->right) > 0) {
		(*rootp)->right = rotate_right((*rootp)->right);
		(*rootp) = rotate_left((*rootp));
	}
}
// following functions are from bst.c of a7q2
TNODE *extract_smallest_node(TNODE **rootp) {
	TNODE *tnp = *rootp;
	TNODE *parent = NULL;
	if (tnp == NULL) {
		return NULL;
	} else {
		while (tnp->left) {
			parent = tnp;
			tnp = tnp->left;
		}
		if (parent == NULL)
			*rootp = tnp->right;
		else
			parent->left = tnp->right;
		tnp->left = NULL;
		tnp->right = NULL;
		return tnp;
	}
}


TNODE *search(TNODE *root, char *name) {
	TNODE *tp = root;
	while (tp) {
		if (strcmp(name, tp->data.name) == 0) {
			return tp;
		} else if (strcmp(name, tp->data.name) < 0)
			tp = tp->left;
		else
			tp = tp->right;
	}
	return NULL;
}

void clean_tree(TNODE **rootp) {
	if (*rootp) {
		TNODE *np = *rootp;
		if (np->left)
			clean_tree(&np->left);
		if (np->right)
			clean_tree(&np->right);
		free(np);
	}
	*rootp = NULL;
	;
}

void display_inorder(TNODE *root) {
	if (root) {
		if (root->left)
			display_inorder(root->left);
		printf("%-22s%3.1f\n", root->data.name, root->data.score);
		if (root->right)
			display_inorder(root->right);
	}
}

void display_tree(TNODE *root, int prelen) {
	if (root) {
		int i;
		for (i = 0; i < prelen; i++)
			printf("%c", ' ');
		printf("%s", "|___");
		printf("%s %3.1f %d\n", root->data.name, root->data.score,
				root->height);
		display_tree(root->right, prelen + 4);
		display_tree(root->left, prelen + 4);
	}
}
