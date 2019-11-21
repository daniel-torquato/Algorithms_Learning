#ifndef __AVL_TREE__
#define __AVL_TREE__

struct avl_tree {
	unsigned height;
	void *data;
	struct avl_tree *left;
	struct avl_tree *right;
};

void insertion (struct avl_tree *tree,
		int (*cmp)(void*, void*),
		void *data)
{
	struct avl_tree *tmp = tree;
	while (tmp) {
		if (cmp(tmp->data, data) > 0)
			tmp = tmp->right;
		else
		if (cmp(tmp->data, data) < 0)
			tmp = tmp->left;
		else
			break;
	}
}


#endif
