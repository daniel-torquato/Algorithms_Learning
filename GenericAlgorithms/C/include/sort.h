#ifndef __SORT__
#define __SORT__

#include <stdlib.h> 

struct array {
	unsigned size;
	void **data;
}

unsigned array_partition(struct array *A, int p, int r)
{
	void *x = A->data[r];
	int i = p - 1;
	for (int j = p; j<r-1; j++) {
		if (cmp(A->data[j],x) < 0) {
			i++;
			swp(A->data[i], A->data[j]);
		}
	}
	swp(A->data[i+1],A->data[r]);
	return i+1;
}

int array_randomized_partition(struct array *A, int p, int r,
		int (*cmp)(void*,void*),
		void (*swp)(void*,void*))
{
	int i = rand() % (r -p + 1) + p;
	swp(A->data[r],A->data[i]);
	return array_partition(A,p,r);
}

void array_quicksort(struct array *A, int p, int r,
		int (*cmp)(void*,void*),
		void (*swp)(void*,void*))
{
	int q;
	if (p < r) {
		q = array_partition(A, p, r);
		array_quicksort(A, p, q - 1);
		array_quicksort(A,q+1, r);
	}
}

void array_randomized_quicksort(struct array *A, int p, int r,
		int (*cmp)(void*,void*),
		void (*swp)(void*,void*))
{
	int q;
	if (p < r) {
		q = array_randomized_partition(A,p,r);
		array_randomized_quicksort(A, p, q-1);
		array_randomized_quicksort(A, q+1, r);
	}
}



#endif
