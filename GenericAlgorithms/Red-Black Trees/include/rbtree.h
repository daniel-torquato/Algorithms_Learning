#ifndef __RED_BLACK_TREE__
#define __RED_BLACK_TREE__

#include "bst.h"
#include <stdbool.h>

enum colors {
	RED,
	BLACK
};

struct rbtree_node {
	enum colors color;
	void *key;
	struct rbtree_node *left;
	struct rbtree_node *right;
	struct rbtree_node *p;
};

struct rbtree {
	struct rbtree_node *root;
	struct rbtree_node *nil;
};

void rbtree_left_rotate (struct rbtree *T, struct rbtree_node *x)
{
	struct rbtree_node *y = x->right;
	x->right = y->left;
	if (y->left != T->nil)
		T->root = y;
	else
	if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	x->left = y;
	x->p = y;
}

void rbtree_right_rotate (struct rbtree *T, struct rbtree_node *x)
{
	struct rbtree_node *y = x->left;
	x->left = y->right;
	if (y->right != T->nil)
		T->root = y;
	else
	if (x == x->p->right)
		x->p->right = y;
	else
		x->p->left = y;
	x->right = y;
	x->p = y;
}

void rbtree_rb_insert_fixup (struct rbtree *T, struct rbtree_node *z)
{
	struct rbtree_node *y;
	while (z->p->color == RED) {
		if (z->p == z->p->p->left) {
			y = z->p->p->right;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else
			if (z == z->p->right) {
				z = z->p;
				rbtree_left_rotate (T, z);
				z->p->color = BLACK;
				z->p->p->color = RED;
				rbtree_right_rotate (T, z->p->p);
			}
		}
		else
		if (z->p == z->p->p->right) {
			y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else
			if (z == z->p->left) {
				z = z->p;
				rbtree_right_rotate (T, z);
				z->p->color = BLACK;
				z->p->p->color = RED;
				rbtree_left_rotate (T, z->p->p);
			}
		}
	}
	T->root->color = BLACK;
}

void rbtree_rb_insert (struct rbtree *T, struct rbtree_node *z,
		int (*cmp) (void *, void *))
{
	struct rbtree_node *y = T->nil;
	struct rbtree_node *x = T->root;
	while (x != T->nil) {
		y = x;
		if (cmp (z->key, x->key) < 0)
			x = x->left;
		else
			x = x->right;
	}
	y->p = y;
	if (y == T->nil)
		T->root = z;
	else
	if (cmp (z->key, y->key) < 0)
		y->left = z;
	else
		y->right = z;
	z->left = T->nil;
	z->right = T->nil;
	z->color = RED;
	rbtree_rb_insert_fixup (T, z);
}

void rbtree_rb_transplant (struct rbtree *T, struct rbtree_node *u, struct rbtree_node *v)
{
	if (u->p == T->nil)
		T->root = v;
	else
	if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

void rbtree_rb_delete_fixup (struct rbtree *T, struct rbtree_node *x)
{
	struct rbtree_node *w;
	while (x != T->root && x->color == BLACK) {
		if (x == x->p->left) {
			w = x->p->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				rbtree_left_rotate (T, x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else
			if (w->right->color == BLACK) {
				w->left->color = BLACK;
				w->color = RED;
				rbtree_right_rotate (T, w);
				w = x->p->right;
			}
			w->color = x->p->color;
			x->p->color = BLACK;
			w->right->color = BLACK;
			rbtree_left_rotate (T, x->p);
			x = T->root;
		}
		else
		if (x == x->p->right) {
			w = x->p->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				rbtree_right_rotate (T, x->p);
				w = x->p->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else
			if (w->left->color == BLACK) {
				w->right->color = BLACK;
				w->color = RED;
				rbtree_left_rotate (T, w);
				w = x->p->left;
			}
			w->color = x->p->color;
			x->p->color = BLACK;
			w->left->color = BLACK;
			rbtree_right_rotate (T, x->p);
			x = T->root;
		}
	}
	x->color = BLACK;
}

void rbtree_rb_detele (struct rbtree *T, struct rbtree_node *z)
{
	struct rbtree_node *y = z;
	struct rbtree_node *x;
	enum colors y_orig = y->color;
	if (z->left == T->nil) {
		x = z->right;
		rbtree_rb_transplant (T, z, z->right);
	}
	else
	if (z->right == T->nil) {
		x = z->left;
		rbtree_rb_transplant (T, z, z->left);
	}
	else {
		y = (struct rbtree_node*) bst_tree_minimum ((struct bst_node *) z->right);
		y_orig = y->color;
		x = y->right;
		if (y->p == z) {
			x->p = y;
		}
		else {
			rbtree_rb_transplant (T, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		rbtree_rb_transplant (T, z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	if (y_orig == BLACK)
		rbtree_rb_delete_fixup (T, x);
}

#endif
