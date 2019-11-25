#include "linked_list.h"
#include "data.h"

int main(int argc, char **argv)
{
	struct dllist L;

	int a = 10;
	char b = 'a';
	char test[]="rapidao";
	float d=0.001;
	struct data data_array[4];

	data_init((void*) &data_array[0], STRING, (void*) &test);
	data_init((void*) &data_array[1], INT, (void*) &a);
	data_init((void*) &data_array[2], CHAR, (void*) &b);
	data_init((void*) &data_array[3], FLOAT, (void*) &d);

	dllist_add((void*) &L, (void*) &data_array[3]);
	dllist_add((void*) &L, (void*) &data_array[0]);
	dllist_add((void*) &L, (void*) &data_array[1]);
	dllist_add((void*) &L, (void*) &data_array[2]);

	dllist_print((void*) &L, data_print);

	dllist_free((void*) &L, fake_free);

	//dllist_print((void*) &L, data_print);

	return 0;
}
