#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include <stdio.h>
#include <stdlib.h>

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

static void dllist_init(void *L, void *x)
{
	((struct dllist*) L)->head = (struct dllist_node*) malloc(sizeof(struct dllist_node));
	((struct dllist*) L)->head->key = x;
	((struct dllist*) L)->head->next = NULL;
	((struct dllist*) L)->head->prev = NULL;
}

static void dllist_free(void *L, void (*fre)(void *))
{
	void *node = (void *) ((struct dllist*) L)->head;
	void *tmp;
	while(node) {
		tmp = (void *) ((struct dllist_node*) node)->next;
		fre(((struct dllist_node*) node)->key);
		free(node);
		node = tmp;
	}
}

static void dllist_print(void *L, void (*prt)(void *))
{
	if (L == NULL)
		return;
	void *node = (void *) ((struct dllist*) L)->head;
	while(node) {
		prt(((struct dllist_node*) node)->key);
		printf("->");
		node = (void *) ((struct dllist_node*) node)->next;
	}

}

static void *dllist_search (void *L, void *k,
		int (*cmp) (void*, void*))
{
	void *x = ((struct dllist*) L)->head;
	while (x != NULL && cmp (((struct dllist_node *) x)->key, k)) {
		x = ((struct dllist_node*) x)->next;
	}
	return x;
}

static void dllist_insert (void *L, void *x)
{
	((struct dllist_node*) x)->next = ((struct dllist*) L)->head;
	if (((struct dllist*) L)->head != NULL) {
		((struct dllist*) L)->head->prev = (struct dllist_node*) x;
	}
	((struct dllist*) L)->head = (struct dllist_node*) x;
	((struct dllist_node*) x)->prev = NULL;
}

static void dllist_add(void *L, void *key)
{
	struct dllist_node* tmp = (struct dllist_node*) malloc(sizeof(struct dllist_node));
	tmp->key = key;
	dllist_insert(L, (void*) tmp);
}

void dllist_delete (void *L, void *x)
{
	if (((struct dllist_node *) x)->prev != NULL)
		((struct dllist_node*) x)->prev->next = ((struct dllist_node*) x)->next;
	else
		((struct dllist*) L)->head = ((struct dllist_node*) x)->next;
	if (((struct dllist_node*) x)->next != NULL)
		((struct dllist_node*) x)->next->prev = ((struct dllist_node*) x)->prev;
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


struct sllist_node {
	void *key;
	struct sllist_node *next;
};

struct sllist {
	struct sllist_node *head;
};

void sllist_delete_next(void *x) {
	struct sllist_node* tmp[2];
	if (((struct sllist_node*) x)->next != NULL) {
		tmp[0] = ((struct sllist_node*) x)->next;
		tmp[1] = tmp[0]->next;
		free(tmp[0]);
		((struct sllist_node*) x)->next = tmp[1];
	}
}

void *sllist_search(void *L, void *k,
		int (*cmp)(void*,void*))
{
	void *x = (void*) ((struct sllist*) L)->head;
	while (x != NULL && cmp(((struct sllist_node*) x)->key, k) != 0) {
		x = (void *) ((struct sllist_node *) x)->next;
	}
	return x;
}

void sllist_insert_before(void *L, void *x)
{
	((struct sllist_node *) x)->next = L;
	((struct sllist *) L)->head = (struct sllist_node *) x;
}

#endif
