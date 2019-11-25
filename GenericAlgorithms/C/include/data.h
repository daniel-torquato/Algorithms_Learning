#ifndef __DATA__
#define __DATA__

#include <stdio.h>
#include <string.h>

enum data_type {
	INT,
	STRING,
	CHAR,
	FLOAT,
};

struct data {
	enum data_type type;
	void *ptr;
};

void data_init(void *D, enum data_type t, void *ptr)
{
	((struct data*) D)->type = t;
	((struct data*) D)->ptr = ptr;
}

void data_print(void *x) {
	switch (((struct data*) x)->type) {
		case (INT):
			printf("%d", *((int*) ((struct data*) x)->ptr));
			break;
		case (STRING):
			printf("%s", (char*) ((struct data *) x)->ptr);
			break;
		case (CHAR):
			printf("%c", *((char*) ((struct data *) x)->ptr));
			break;
		case (FLOAT):
			printf("%f", *((float*) ((struct data *) x)->ptr));
			break;
		default:
			printf("missing type\n");
	}
}

void data_copy(void *A, void *B)
{
	switch (((struct data*) A)->type) {
		case (INT):
			*((int*) ((struct data*) A)->ptr) = *((int*) ((struct data*) B)->ptr);
			break;
		case (STRING):

			strcmp((char*) ((struct data*) A)->ptr, (char*) ((struct data*) B)->ptr);
			break;
		case (CHAR):
			*((char*) ((struct data*) A)->ptr) = *((char*) ((struct data*) B)->ptr);
			break;
		case (FLOAT):
			*((float*) ((struct data*) A)->ptr) = *((float*) ((struct data*) B)->ptr);
			break;
		default:
			printf("missing type\n");
	}
}

void data_free(void *x)
{
	free(x);
}

void fake_free(void *x) {
}

#endif
