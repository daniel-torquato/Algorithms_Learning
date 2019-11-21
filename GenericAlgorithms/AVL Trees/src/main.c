#include <stdio.h>
#include "avl_tree.h"

int main ()
{
	struct avl_tree *tree;
	int eval (void *data) {
		return *((int *) data);
	}
	int cmp_int (void *left, void *right) {
		return eval(left) - eval(right);
	}
	return 0;
}
