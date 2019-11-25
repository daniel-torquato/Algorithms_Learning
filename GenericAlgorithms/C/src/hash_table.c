#include <stdio.h>
#include "hash.h"
#include "data.h"

int main(int argc, char **argv)
{
	struct htable T;

	int map(void *x) {
		return *((int*) x) % 3;
	}
	htable_init((void*) &T, 3, map);

	int a = 10;

	htable_insert((void*) &T, (void*) &a);

	void int_print(void *v) {
		printf("%d", *((int *) v));
	}
	htable_free((void*) &T, fake_free);
	//free(a);
	return 0;
}
