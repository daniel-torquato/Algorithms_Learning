#ifndef __STATISTIC__
#define __STATISTIC__

void *array_minimum(struct array *A, int (*cmp)(void*,void*))
{
	void *min = A->data[0];
	for (int i=1; i<A->length; i++) {
		if (cmp (min, A->data[i]) > 0)
			min = A->data[i];
	}
	return min;
}


#endif
