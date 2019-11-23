#ifndef __BUCKET__
#define __BUCKET__

#include "array.h"
#include "sllist.h"

// that sort depends of data type (as float or double)
void array_bucket_sort(struct array *A)
{
	unsigned n = A->length;
	struct array *B = array_init(A->length,sizeof(struct sllist*));
	// for i = 0 to n - 1
	// make B[i] an empty list
	for (int i=0; i<n; i++) {
		sllist_add(B+((int) n*A->data[i]),A->date[i]);
	}
	sllist_concatenate (B, n - 1);
}

#endif
