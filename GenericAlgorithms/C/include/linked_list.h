#ifndef __LINKED_LIST__
#define __LINKED_LIST__

struct dllist_node {
	void *key;
	struct dllist_node *next;
	struct dllist_node *prev;
};

struct dllist {
	struct dllist_node *head;
};

struct dllnil {
	struct dllist_node *nil;
};

struct dllist_node *dllist_list_search (struct dllist *L, void *k,
		int (*cmp) (void*, void*))
{
	struct dllist_node *x = L->head;
	while (x != NULL && cmp (x->key, k)) {
		x = x->next;
	}
	return x;
}

void dllist_list_insert (struct dllist *L, struct dllist_node *x)
{
	x->next = L->head;
	if (L->head != NULL) {
		L->head->prev = x;
	}
	L->head = x;
	x->prev = NULL;
}

void dllist_list_delete (struct dllist *L, struct dllist_node *x)
{
	if (x->prev != NULL)
		x->prev->next = x->next;
	else
		L->head = x->next;
	if (x->next != NULL)
		x->next->prev = x->prev;
}

struct dllist_node *dllnil_list_search (struct dllnil *L, void *key,
		int (*cmp) (void *, void*))
{
	struct dllist_node *x = L->nil->next;
	while (x != L->nil && cmp (x->key, key)) {
		x = x->next;
	}
	return x;
}

void dllnil_list_insert (struct dllnil *L, struct dllist_node *x)
{
	x->next = L->nil->next;
	L->nil->next->prev = x;
	L->nil->next = x;
	x->prev = L->nil;
}


#endif
