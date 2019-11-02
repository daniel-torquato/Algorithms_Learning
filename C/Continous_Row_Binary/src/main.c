#include <stdio.h>
#include <stdlib.h>


int find_conex_element(int **grid, int n, int m, int i, int j, int *flag)
{
	if (grid[i][j]<1)
		return 0;

	grid[i][j]=-1;

	if (i<n-1 && grid[i+1][j]>0) {
		if (!*flag)
			*flag=1;
		find_conex_element(grid, n, m, i+1, j, flag);
	}

	if (j<m-1 && grid[i][j+1]>0) {
		if (!(*flag))
			*flag=1;
		find_conex_element(grid, n, m, i, j+1, flag);
	}

	if ((i>0 && grid[i-1][j])>0) {
		if (!(*flag)) {
			*flag=1;
		}
		find_conex_element(grid, n, m, i-1, j, flag);
	}

	if (j>0 && grid[i][j-1]>0) {
		if (!(*flag)) {
			*flag=1;
		}
		find_conex_element(grid, n, m, i, j-1, flag);
	}
}

int get_cont(int **grid, int n, int m)
{
	int ret=0, flag=0;
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<m; j++) {
			if (grid[i][j]>0) {
				ret++;
				find_conex_element(grid, n, m, i, j, &flag);
			}
			flag=0;
		}

	return ret;
}

void alloc_matrix (int ***matrix, int n, int m)
{
	*matrix=(int **) malloc(n*sizeof(int*));
	int i;
	for (i=0; i<n; i++) {
		(*matrix)[i]=(int *) malloc(m*sizeof(int));
	}
}

void free_matrix(int **matrix, int n, int m)
{
	int i;
	for (i=0; i<n; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

void print_matrix(int **matrix, int n, int m)
{
	int i, j;
	printf("\n");
	for (i=0; i<n; i++) {
		for (j=0; j<m; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int n, m;
	int i, j;
	scanf("%d", &n);
	scanf("%d", &m);
	int **grid;
	alloc_matrix(&grid, n, m);

	for (i=0; i<n; i++) {
		for (j=0; j<m; j++) {
			scanf("%d", grid[i]+j);
		}
	}

	printf("%d", get_cont(grid, n, m));
	free_matrix(grid, n, m);

	return 0;
}
