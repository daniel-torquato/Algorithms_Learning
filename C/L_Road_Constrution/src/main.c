#include <stdio.h>
#include <stdlib.h>

void alloc_array_int(int **array, int n)
{
	*array = (int*) malloc(n*sizeof(int));
}

void free_array_int(int *array)
{
	free(array);
}

void alloc_array_ptr_int(int ***array, int n)
{
	*array = (int**) malloc(n*sizeof(int*));
}

void free_array_ptr_int(int **array, int n)
{
	free(array);
}

void alloc_matrix_int(int ***matrix, int n, int m)
{
	int i;
	*matrix=(int**) malloc(n*sizeof(int*));
	for (int i = 0; i < n; i++) {
		(*matrix)[i] = malloc(m*sizeof(int));
	}
}

void free_matrix_int(int **matrix, int n)
{
	for (int i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);
}


void print_matrix_int(int **index, int n, int m)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", index[i][j]);
		}
		printf("\n");
	}
}


void print_array2(int **index, int n, int *sizes)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < sizes[i]; j++) {
			printf("%d ", index[i][j]);
		}
		printf("\n");
	}
}

void print_array(int *array, int n)
{
	for (int i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}


int assign_worker(int **can, int n, int k, int worker, int *city, int **ans)
{
	int ret=1;

#ifdef DEBUG
	printf("lvl=%d/%d\n", worker, k);
#endif
	if (worker == n) {
#ifdef DEBUG
		printf("end\n");
#endif
		return 0;
	}
	for (int j = 0; j < n && ret; j++) {
		if (can[worker][j] && !city[j]) {
			city[j]=worker+1;
			ans[worker][0]=j+1;
			ans[worker][1]=can[worker][j];
#ifdef DEBUG
			printf("set\n");
			print_array(city, n);
#endif
			ret=assign_worker(can, n, k, worker+1, city, ans);

			if (ret) {
#ifdef DEBUG
				printf("unset\n");
				print_array(city, n);
#endif
				city[j]=0;
				ans[worker][0]=0;
				ans[worker][1]=0;
			}
		}
	}
	return ret;
}

int find_worker(int *c, int k, int n)
{
	int ret=0;
	for (int i = 1; i <= k && !ret; i++) {
		if (c[i-1] == n)
			ret=i;
	}
	return ret;
}

int answer(int *a, int *m, int n, int **b, int *c, int k, int **ans)
{
	int flag=-1;
	int **can=NULL;
	alloc_matrix_int(&can, k, n);
	for (int i = 0; i < n && flag; i++) {
		for (int j = 0; j < m[i] && flag; j++) {
			flag = find_worker(c, k, b[i][j]);
			if (flag)
				can[flag-1][i]=a[i];
		}
	}

#ifdef DEBUG
	printf("flag=%d\n", flag);
#endif
	int *mask;
	if (flag) {
		alloc_array_int(&mask, n);
#ifdef DEBUG
		print_matrix_int(can, k, n);
#endif
		assign_worker(can, n, k, 0, mask, ans);
		free(mask);
	}
	free_matrix_int(can, k);
	return flag;
}

int main(int argc, const char *argv[])
{
	int n, k;
	scanf("%d", &n);
	scanf("%d", &k);

	int *a=NULL;
	int *m=NULL;
	int **b=NULL;
	int *c=NULL;
	int **ans=NULL;
	alloc_array_int(&a, n);
	alloc_array_int(&m, n);
	alloc_array_int(&c, k);
	alloc_array_ptr_int(&b, n);
	alloc_matrix_int(&ans, k, 2);
	for (int i = 0; i < n; i++) {
		scanf("%d", a+i);
		scanf("%d", m+i);
		alloc_array_int(b+i, m[i]);
		for (int j = 0; j < m[i]; j++) {
			scanf("%d", b[i]+j);
		}
	}
	for (int i = 0; i < k; i++) {
		scanf("%d", c+i);
	}
	if (answer(a, m, n, b, c, k, ans))
		print_matrix_int(ans, k, 2);
	else
		printf("-1\n");

#ifdef DEBUG
	print_array2(b, n, m);
#endif
	free(a);
	free(m);
	free(c);
	free_matrix_int(b, n);
	free_matrix_int(ans, n);
	return 0;
}
