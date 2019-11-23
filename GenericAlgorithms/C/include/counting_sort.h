#ifndef __COUNTING_SORT__
#define __COUNTING_SORT__

struct array {
	void **data;
	unsigned length;
}

struct array *array_init(unsigned length, unsigned item_size)
{
	struct array *tmp = (struct array*) malloc(length*item_size);
	return tmp;
}

void array_counting_sort(struct array *A, struct array *B, int k,
		void (*inc)(void*),
		void (*dec)(void*),
		void (*sum)(void*,void*),
		void (*set)(void*),
		unsigned data_size)
{
	struct array *c = array_init(k, data_size);

	for (int i=0; i<A->length; i++)
		set (C->data[A->data[i]],0);

	for (int j=0; j<A->length; j++)
		inc (C->data[A->data[j]]);

	for (int i=0; i<k; i++)
		sum (C->data[i], C->data[i-1]);

	for (int j=A->length; j>=0; j--) {
		set (B->data[C->data[A->data]], A->data[j]);
		dec (C->data[A->data[j]]);
	}
}

void array_radix_sort(struct array *A, unsigned d)
{
	// that sort algorithms depends of data representation
	for (int i=0; i<d; i++) {
		// sort A on digit i
	}
}


#endif
