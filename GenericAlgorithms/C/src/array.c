#include "array.h"
#include "data.h"

int main(int argc, char **argv)
{
	int a = 11;

	int array[] = {1, 2, 3, 4};

	struct array A;

	array_init((void*) &A, sizeof(array) / sizeof(int), sizeof(struct data));

	for (int i=0; i<sizeof(array) / sizeof(int); i++)
		data_init(A.data[i], INT, (void*) &array[i]);

	struct data tmp;
	data_init((void*) &tmp, INT, (void*) &a);

	data_copy(A.data[0], (void*) &tmp);
	//array_insert(A, 0, (void*) &tmp, data_copy);

	array_print ((void*) &A, data_print);

	array_free ((void*) &A, fake_free);

	return 0;
}

