#ifndef __ARRAY__
#define __ARRAY__

#include <stdio.h>
#include <stdlib.h>

struct array {
	int length;
	void **data;
};

void array_init(void *A, int length, size_t item_size) {
	((struct array*) A)->data = (void **) malloc(length*sizeof(void*));
	((struct array*) A)->length = length;
	for (int i=0; i<length; i++) {
		((struct array*) A)->data[i] = (void*) malloc(item_size);
	}
}

void array_free(void *A, void (*fre)(void *)) {
	for (int i=0; i<((struct array*) A)->length; i++) {
		fre(((struct array*) A)->data[i]);
		free(((struct array*) A)->data[i]);
	}
	free(((struct array*) A)->data);
}

void array_print(void *A, void (*prt)(void *)) {
	for (int i=0; i<((struct array*) A)->length; i++) {
		prt(((struct array*) A)->data[i]);
		printf("\n");
	}
}

void array_insert(void *A, int k, void *val, void (*copy)(void *,void*))
{
	copy(((struct array*) A)->data[k], val);
}

#endif
