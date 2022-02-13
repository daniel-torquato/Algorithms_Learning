#ifndef __BINARY_SEARCH_TREE__
#define __BINARY_SEARCH_TREE__

/*
# Definition
	"Let x be a node in a binary search tree. If y is a node in the left subtree
	of x. then y.key <= x.key. If y is a node in the right subtree of x, then
	y.key >= x.key." by Cormen [1]

# Theorem
	If x is the root of an n-node subtree, then the call INODER_TREE_WALK(x)
	takes O(n) time.

12.2
	We can implemnt the dynamic-set operations SEARCH, MINIMUM, MAXIMUM,
	SUCESSOR, and PREDECESSOR so that each one runs in O(h) time on a binary
	search tree of height h.
*/

struct bst_node {
	void *key;
	struct bst_node *left;
	struct bst_node *right;
	struct bst_node *p;
};

struct bst {
	struct bst_node *root;
};

void bst_inorder_bst_walk (struct bst_node *bst, void (*print)(void *))
{
	if (bst) {
		bst_inorder_bst_walk (bst->left, print);
		print (bst->key);
		bst_inorder_bst_walk (bst->right, print);
	}
}

struct bst_node *bst_tree_search (struct bst_node *bst, void *key, int (*cmp)(void *, void*))
{
	if (bst || cmp(bst->key, key) == 0)
		return bst;
	if (cmp(bst->key, key) < 0)
		return bst_tree_search (bst->left, key, cmp);
	else
		return bst_tree_search (bst->right, key, cmp);
}

struct bst_node *bst_iterative_tree_search (struct bst_node *bst, void *key, int (*cmp) (void*, void*))
{
	while (bst && cmp(bst->key, key)) {
		if (cmp(key, bst->key) < 0)
			bst = bst->left;
		else
			bst = bst->right;
	}
	return bst;
}

struct bst_node *bst_tree_minimum (struct bst_node *bst)
{
	while (bst->left) {
		bst = bst->left;
	}

	return bst;
}

struct bst_node *bst_tree_maximum (struct bst_node *bst)
{
	while (bst->right) {
		bst = bst->right;
	}
	return bst;
}

struct bst_node *bst_tree_sucessor (struct bst_node *bst)
{
	struct bst_node *tmp;
	if (bst->right)
		return bst_tree_minimum (bst->right);
	tmp = bst->p;
	while (tmp && bst == tmp->right) {
		bst = tmp;
		tmp = tmp->p;
	}
	return tmp;
}

void bst_tree_insert (struct bst *T, struct bst_node *z, int cmp (void*, void*))
{
	struct bst_node *y = NULL;
	struct bst_node *x = T->root;

	while (x != NULL) {
		y = x;
		if (cmp (z->key, x->key) < 0)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y == NULL) {
		T->root = z;
	}
	else
	if (cmp(z->key, y->key) < 0)
		y->left = z;
	else
		y->right = z;
}

void bst_transplant (struct bst *T, struct bst_node *u, struct bst_node *v)
{
	if (u->p == NULL)
		T->root = v;
	else
	if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	if (v == NULL)
		v->p = u->p;
}

void bst_tree_delete (struct bst *T, struct bst_node *z)
{
	struct bst_node *y;
	if (z->left == NULL)
		bst_transplant (T, z, z->right);
	else
	if (z->right == NULL)
		bst_transplant (T, z, z->left);
	else {
		y = bst_tree_minimum (z->right);
		if (y->p != z) {
			bst_transplant (T, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		bst_transplant (T, z, y);
		y->left = z->left;
		y->left->p = y;
	}
}

#endif
