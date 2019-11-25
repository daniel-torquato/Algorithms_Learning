#ifndef __DIRECT_ADDRESS_TABLE__
#define __DIRECT_ADDRESS_TABLE__

#include "array.h"
#include "linked_list.h"

struct datable {
	struct array *table;
}

void datable_init(void *T, int m)
{
	array_init((void*) ((struct datable*) T)->table, m, sizeof(struct slist*));
}

void *datable_search(void *T, int k)
{
	return ((struct datable) T)->table[k];
}

void datable_insert(void *T, void *x)
{
	((struct datable) T)->table[( x)->key] = x;
}

void datable_delete(void *T, void *x)
{
	((struct datable) T)->data[((struct datable_slot) x)->key] = NULL;
}

#endif
