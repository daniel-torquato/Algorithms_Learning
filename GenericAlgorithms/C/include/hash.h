#ifndef __HASH_TABLE__
#define __HASH_TABLE__

#include "linked_list.h"
#include "array.h"

struct htable {
	struct array *table;
	int (*map) (void *key);
};

static void htable_init(void *T, int size, int (*map)(void *))
{
	((struct htable*) T)->map = map;
	array_init((void*) ((struct htable*) T)->table, size, sizeof(struct dllist*));
}

static void htable_print(struct htable* T, void (*prt)(void *))
{
	void tmp_print(void *A) {
		dllist_print(A, prt);
	}
	array_print(T->table, tmp_print);
}

static void htable_free(void *T, void (*fre)(void *))
{
	void tmp_free(void *A) {
		dllist_free(A, fre);
	}
	array_free((void*) ((struct htable*) T)->table, tmp_free);
}

static void htable_insert(void *T, void *x)
{
	int idx = ((struct htable*) T)->map(x);
	void *tmp = (void*) ((struct htable*) T)->table->data[idx];
	dllist_insert(tmp, x);
}

static void *htable_search(void *T, void *k, int (*cmp)(void*,void*))
{
	int idx = ((struct htable*) T)->map(k);
	void *tmp = ((struct htable*) T)->table->data[idx];
	return dllist_search(tmp, k, cmp);
}

static void htable_delete(void *T, void *k)
{
	int idx = ((struct htable*) T)->map(k);
	void *tmp = ((struct htable*) T)->table->data[idx];
	dllist_delete(tmp, k);
}

#endif
