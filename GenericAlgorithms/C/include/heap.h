#ifndef __HEAP__
#define __HEAP__

#include <errno.h>

struct aheap {
	unsigned heap_size;
	unsigned length;
	void **data;
};

unsigned aheap_parent(unsigned i)
{
	return (i/2);
}

unsigned aheap_left(unsigned i)
{
	return 2*i;
}

unsigned aheap_right(unsigned i)
{
	return 2*i+1;
}

void aheap_max_heapify(struct aheap *A, unsigned i,
		int (*cmp) (void *, void*),
		void (*swp) (void *, void *))
{
	int l = aheap_left(i);
	int r = aheap_right(i);
	int largest;

	if (l <= A->heap_size && cmp(A->data[l],  A->data[i]) < 0)
		largest = l;
	else
		largest = i;

	if (r <= A->heap_size && cmp (A->data[r], A->data[largest]) < 0)
		largest = r;

	if (largest != i) {
		swp (A->data[i], A->data[largest]);
		aheap_max_heapify(A, largest, cmp, swp);
	}
}

void aheap_build_max_heap(struct aheap *A, int (*cmp)(void*,void*),
		void (*swp)(void*,void*))
{
	A->heap_size = A->length;
	for (unsigned i=(A->length/2); i>=0; i--)
		aheap_max_heapify(A, i, cmp, swp);
}

void aheap_heapsort(struct aheap *A, int (*cmp)(void*, void*), 
		void (*swp)(void*,void*))
{
	aheap_build_max_heap(A, cmp, swp);
	for (unsigned i=A->length; i>=1; i--) {
		swp(A->data[0],A->data[i]);
		A->heap_size = A->heap_size - 1;
		aheap_max_heapify(A,1,cmp,swp);
	}

}

void *aheap_heap_maximum(struct aheap *A)
{
	return A->data[0];
}

void *aheap_heap_extract_max(struct aheap *A,
		int (*cmp)(void*,void*),
		void (*swp)(void*,void*))
{
	if (A->heap_size < 0)
		perror("heap underflow");
	void *max = A->data[0];
	A->data[0] = A->data[A->heap_size--];
	aheap_max_heapify(A, 1, cmp, swp);
	return max;
}

void aheap_heap_increase_key (struct aheap *A, int i, void *key,
		int (*cmp)(void*,void*),
		void (*swp)(void*,void*))
{
	if (cmp(key, A->data[i]) < 0)
		perror("new key is smaller than current key");
	A->data[i] = key;
	while (i>0 && cmp(A->data[aheap_parent(i)],A->data[i]) < 0) {
		swp(A->data[i],A->data[aheap_parent(i)]);
		i = aheap_parent(i);
	}
}

void aheap_max_heap_insert(struct aheap *A, void *key,
		int (*cmp)(void*,void*),
		void (*swp)(void*,void*),
		void set_min_val(void*))
{
	set_min_val(A->data[++A->heap_size]);
	aheap_heap_increase_key(A, A->heap_size, key, cmp, swp);
}

void aheap_build_max_heap_2(struct aheap *A,
		int (*cmp)(void*,void*),
		void (*swp)(void*,void*),
		void (*set_min_val)(void*))
{
	A->heap_size = 1;
	for (int i=1; i<A->length; i++)
		aheap_max_heap_insert(A, A->data[i], cmp, swp, set_min_val);
}

#endif
