#include <stdio.h>
#include <stdlib.h>

int *alloc_array_int(int n)
{
	return (int *) malloc(n*sizeof(int));
}

int** alloc_array_ptr(int n)
{
	return (int**) malloc(n*sizeof(int*));
}

int** alloc_matrix_int(int n, int m)
{
	int i;
	int **matrix=alloc_array_ptr(n);
	for (int i = 0; i < n; i++)
		matrix[i] = alloc_array_int(m);
	return matrix;
}

void free_array(int **matrix, int n)
{
	for (int i = 0; i < n; i++)
		free(matrix[i]);
	free(matrix);
}

void print_array(int *array, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", array[i]);
	printf("\n");
}

void print_matrix_int(int **index, int n, int m)
{
	for (int i = 0; i < n; i++)
		print_array(index[i], m);
}

void print_array2(int **index, int n, int *sizes)
{
	for (int i = 0; i < n; i++)
		print_array(index[i], sizes[i]);
}


int assign_worker2city(int **can, int n, int k, int worker, int *city)
{
	int ret=1;

	if (worker == n)
		return 0;

	for (int j = 0; j < n && ret; j++) {
		if (can[worker][j] && !city[j]) {
			city[j]=worker+1;

			ret=assign_worker2city(can, n, k, worker+1, city);

			if (ret)
				city[j]=0;
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

int map_worker_to_city(int *a, int *m, int n, int k, int **b, int *c, int **can)
{
	int flag=-1;
	for (int i = 0; i < n && flag; i++) {
		for (int j = 0; j < m[i] && flag; j++) {
			flag = find_worker(c, k, b[i][j]);
			if (flag)
				can[flag-1][i]=a[i];
		}
	}
	return flag;
}

int answer(int *a, int *m, int n, int k, int **b, int *c, int **ans)
{
	int **can=alloc_matrix_int(k, n);

	int flag=map_worker_to_city(a, m, n, k, b, c, can);
#ifdef DEBUG
	printf("flag=%d\n", flag);
#endif
	int *city;
	if (flag) {
		city=alloc_array_int(n);
#ifdef DEBUG
		print_matrix_int(can, k, n);
#endif
		flag = !assign_worker2city(can, n, k, 0, city);
		for (int i = 0; i < n && flag; i++) {
			ans[city[i]-1][0]=i+1;
			ans[city[i]-1][1]=can[city[i]][i];
		}
		free(city);
	}
	free_array(can, k);
	return flag;
}

int main(int argc, const char *argv[])
{
	int n, k;
	scanf("%d", &n);
	scanf("%d", &k);

	int *a=alloc_array_int(n);
	int *m=alloc_array_int(n);
	int *c=alloc_array_int(k);
	int **b=alloc_array_ptr(n);
	int **ans=alloc_matrix_int(k, 2);

	for (int i = 0; i < n; i++) {
		scanf("%d", a+i);
		scanf("%d", m+i);
		b[i]=alloc_array_int(m[i]);
		for (int j = 0; j < m[i]; j++)
			scanf("%d", b[i]+j);
	}

	for (int i = 0; i < k; i++)
		scanf("%d", c+i);

	if (answer(a, m, n, k, b, c, ans))
		print_matrix_int(ans, k, 2);
	else
		printf("-1\n");

#ifdef DEBUG
	print_array2(b, n, m);
#endif
	free(a);
	free(m);
	free(c);
	free_array(b, n);
	free_array(ans, n);
	return 0;
}
